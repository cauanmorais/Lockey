#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <winsock2.h>
#include "cJSON.h"
#include "mongoose.h"

#pragma comment(lib, "ws2_32.lib")
#define MAX_TEXT_SIZE 1024
#define MAX_KEY_SIZE 128

// Estrutura para manter a chave temporária
struct session {
    char chave[MAX_KEY_SIZE];
};

// Configurações do servidor
static const char *s_http_port = "8080"; 
static struct mg_http_serve_opts s_http_server_opts; 

// Funções de criptografia e descriptografia
void criptografar(char *textoOriginal, char *chave, char *textoCifrado) {
    int tamTexto = strlen(textoOriginal);
    int tamChave = strlen(chave);
    int indiceChave = 0; // Índice para avançar na chave

    for (int i = 0; i < tamTexto; i++) {
        if (isalpha(textoOriginal[i])) { // Apenas caracteres alfabéticos usam a chave
            char chaveAtual = tolower(chave[indiceChave % tamChave]) - 'a';
            if (isupper(textoOriginal[i])) {
                textoCifrado[i] = ((textoOriginal[i] - 'A' + chaveAtual) % 26) + 'A';
            } else {
                textoCifrado[i] = ((textoOriginal[i] - 'a' + chaveAtual) % 26) + 'a';
            }
            indiceChave++; // Avança a chave apenas aqui
        } else {
            textoCifrado[i] = textoOriginal[i]; // Mantém caracteres inalterados
        }
    }
    textoCifrado[tamTexto] = '\0';
}

void descriptografar(char *textoCifrado, char *chave, char *textoOriginal) {
    int tamTexto = strlen(textoCifrado);
    int tamChave = strlen(chave);
    int indiceChave = 0; 

    for (int i = 0; i < tamTexto; i++) {
        if (isalpha(textoCifrado[i])) { 
            char chaveAtual = tolower(chave[indiceChave % tamChave]) - 'a';
            if (isupper(textoCifrado[i])) {
                textoOriginal[i] = ((textoCifrado[i] - 'A' - chaveAtual + 26) % 26) + 'A';
            } else {
                textoOriginal[i] = ((textoCifrado[i] - 'a' - chaveAtual + 26) % 26) + 'a';
            }
            indiceChave++; 
        } else {
            textoOriginal[i] = textoCifrado[i]; 
        }
    }
    textoOriginal[tamTexto] = '\0';
}

// Handler para requisições HTTP
static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;

        static struct session s;  // Manter a chave entre requisições
        char texto[MAX_TEXT_SIZE], chave[MAX_KEY_SIZE], resultado[MAX_TEXT_SIZE];

        mg_http_get_var(&hm->body, "text", texto, sizeof(texto));
        mg_http_get_var(&hm->body, "key", chave, sizeof(chave));

        // Cabeçalhos CORS
        const char *cors_headers = "Access-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: GET, POST, OPTIONS\r\nAccess-Control-Allow-Headers: Content-Type\r\n";

        if (mg_match(hm->uri, mg_str("/api/validate-key"), NULL)) {
            if (chave[0] != '\0') {
                int chaveValida = 1;
                for (int i = 0; i < strlen(chave); i++) {
                    if (!isalpha(chave[i])) {
                        chaveValida = 0;
                        break;
                    }
                }

                cJSON *json_response = cJSON_CreateObject();
                if (chaveValida) {
                    strncpy(s.chave, chave, sizeof(s.chave));
                    cJSON_AddBoolToObject(json_response, "valid", 1);
                } else {
                    cJSON_AddBoolToObject(json_response, "valid", 0);
                    cJSON_AddStringToObject(json_response, "error", "Chave inválida. Apenas caracteres alfabéticos são permitidos.");
                }
                char *json_string = cJSON_Print(json_response);
                mg_http_reply(c, 200, cors_headers, "%s", json_string);
                free(json_string);
                cJSON_Delete(json_response);
            } else {
                cJSON *json_response = cJSON_CreateObject();
                cJSON_AddBoolToObject(json_response, "valid", 0);
                cJSON_AddStringToObject(json_response, "error", "Chave vazia não é permitida.");
                char *json_string = cJSON_Print(json_response);
                mg_http_reply(c, 400, cors_headers, "%s", json_string);
                free(json_string);
                cJSON_Delete(json_response);
            }
            return;
        }

        if (mg_match(hm->uri, mg_str("/api/encrypt"), NULL)) {
            if (s.chave[0] == '\0') {
                cJSON *json_response = cJSON_CreateObject();
                cJSON_AddStringToObject(json_response, "error", "Chave não fornecida");
                char *json_string = cJSON_Print(json_response);
                mg_http_reply(c, 400, cors_headers, "%s", json_string);
                free(json_string);
                cJSON_Delete(json_response);
                return;
            }
            criptografar(texto, s.chave, resultado);
            cJSON *json_response = cJSON_CreateObject();
            cJSON_AddStringToObject(json_response, "result", resultado);
            char *json_string = cJSON_Print(json_response);
            mg_http_reply(c, 200, cors_headers, "%s", json_string);
            free(json_string);
            cJSON_Delete(json_response);

        } else if (mg_match(hm->uri, mg_str("/api/decrypt"), NULL)) {
            if (s.chave[0] == '\0') {
                cJSON *json_response = cJSON_CreateObject();
                cJSON_AddStringToObject(json_response, "error", "Chave não fornecida");
                char *json_string = cJSON_Print(json_response);
                mg_http_reply(c, 400, cors_headers, "%s", json_string);
                free(json_string);
                cJSON_Delete(json_response);
                return;
            }
            descriptografar(texto, s.chave, resultado);
            cJSON *json_response = cJSON_CreateObject();
            cJSON_AddStringToObject(json_response, "result", resultado);
            char *json_string = cJSON_Print(json_response);
            mg_http_reply(c, 200, cors_headers, "%s", json_string);
            free(json_string);
            cJSON_Delete(json_response);
        } else {
            mg_http_reply(c, 404, cors_headers, "Not Found\n");
        }
    }
}

// Função principal
int main(void) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Falha na inicialização do Winsock\n");
        return 1;
    }

    struct mg_mgr mgr;
    struct mg_connection *c;

    mg_mgr_init(&mgr);

    // Configuração do diretório de arquivos estáticos
    char web_dir[512];
    snprintf(web_dir, sizeof(web_dir), "../frontEnd");

    s_http_server_opts.root_dir = web_dir;  

    printf("Servidor rodando em http://127.0.0.1:%s\n", s_http_port);
    printf("Servindo arquivos do diretório: %s\n", web_dir);

    c = mg_http_listen(&mgr, "http://127.0.0.1:8080", fn, NULL);
    if (c == NULL) {
        printf("Erro ao inicializar o servidor\n");
        return 1;
    }

    for (;;) mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
    WSACleanup();
    return 0;
}
