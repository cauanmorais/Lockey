Projeto Lockey: Cifra de Vigenère em Web:

Objetivo do Projeto:

O projeto Lockey visa criar um sistema de criptografia e descriptografia baseado na cifra de Vigenère. O foco do projeto é permitir que os usuários criptografem e descriptografem mensagens diretamente de um site, usando uma chave definida. O backend em C interage com o frontend (HTML, CSS, JavaScript) para realizar as operações de criptografia, enquanto a comunicação entre o frontend e o backend é realizada via requisições HTTP.


Requisitos do Sistema:

1. Sistema Operacional:
O projeto foi desenvolvido para ser executado em ambientes Windows (testado com Windows 10).

2. Dependências:
Compilador C: Para compilar o código C, é necessário um compilador compatível, como MinGW ou Microsoft Visual Studio.

Bibliotecas Externas:
Mongoose: Biblioteca para gerenciamento de requisições HTTP.
cJSON: Biblioteca para manipulação de JSON no C (incluída no projeto).
Winsock2: Biblioteca para gerenciamento de sockets no Windows.

3. Tecnologias Utilizadas:
Frontend: HTML, CSS, JavaScript.
Backend: Linguagem C, com uso das bibliotecas Mongoose e cJSON.

Estrutura de Arquivos:

O projeto está estruturado da seguinte forma:


Lockey/
│
├── backend/
│   ├── makefile            # Arquivo para compilar o backend
│   ├── mongoose.c          # Implementação do servidor Mongoose
│   ├── mongoose.h          # Definições do Mongoose
│   ├── server.c            # Código principal do servidor
│   └── cJSON.c, cJSON.h     # Biblioteca para manipulação de JSON
│
├── frontend/
│   ├── index.html          # Página inicial com opções de criptografia/descriptografia
│   ├── criptografia.html   # Página de criptografia
│   ├── descriptografia.html# Página de descriptografia
│   ├── app.js              # Código JavaScript que controla a interação com o backend
│   └── style.css           # Estilos para o frontend
│
├── .env                    # Arquivo de configuração com variáveis de ambiente
├── package-lock.json       # Dependências do Node.js
├── package.json            # Configuração do projeto Node.js
└── README.md               # Documentação do projeto

Como Instalar e Configurar o Projeto:

Passo 1: Baixar o Projeto:
Baixe ou clone o repositório do projeto Lockey para seu computador. Se estiver usando o Git, execute o comando:


git clone https://github.com/cauanmorais/Lockey.git

Passo 2: Instalar as Dependências:
As dependências necessárias para o backend estão incluídas nas pastas backend (Mongoose, cJSON). Não é necessário instalar dependências adicionais, pois as bibliotecas estão contidas no projeto.

Passo 3: Compilar o Backend:

No diretório backend, execute o comando make para compilar os arquivos C. O arquivo makefile está configurado para gerar o executável server.exe:


cd backend
make
Passo 4: Configurar as Variáveis de Ambiente
No arquivo .env (diretório raiz do projeto), defina a variável de ambiente com a porta que o servidor HTTP irá rodar. Exemplo:


PORT=8080
Passo 5: Iniciar o Servidor Backend
No diretório backend, execute o servidor com o comando:


./server.exe
Isso iniciará o servidor na porta definida (por padrão, 8080). O servidor estará escutando requisições HTTP para as rotas de criptografia e descriptografia.

Como Usar o Projeto:

1. Acessar o Frontend
Abra o arquivo index.html no seu navegador ou execute um servidor local (como o servidor HTTP do Python ou do Node.js) para servir os arquivos.

Página principal (index.html): O usuário pode escolher entre as opções de criptografia ou descriptografia.

2. Validar a Chave.

Antes de realizar a criptografia ou a descriptografação, o usuário deve validar a chave inserida. A chave deve ser composta apenas por letras (a-z, A-Z).
A página de criptografia (criptografia.html) ou de descriptografação (descriptografia.html) permite que o usuário insira o texto a ser processado e a chave.

3. Criptografar ou Descriptografar.

O frontend envia os dados para o backend através de requisições HTTP, onde o backend processa o texto utilizando a cifra de Vigenère e retorna o resultado para o frontend.

Testes Manuais e Automatizados

1. Testes Manuais.

Testar a Criptografia
Vá para a página criptografia.html e insira um texto e uma chave válida. O sistema criptografará o texto e exibirá o resultado.
Testar a Descriptografia
Após criptografar o texto, você pode copiá-lo para a página descriptografia.html e usar a mesma chave para descriptografar o texto.
Testar a Validação da Chave
A chave deve ser validada antes de qualquer operação de criptografia ou descriptografiação. Isso é feito automaticamente quando o usuário insere a chave nas páginas de criptografia/descriptografação.

2. Testes Automatizados.

Para realizar testes automatizados, você pode usar ferramentas como Postman ou cURL para simular requisições HTTP aos endpoints do servidor.

Exemplos de Requisições:
POST /api/validate-key: Valida a chave de criptografia:


curl -X POST http://localhost:8080/api/validate-key -d "key=KEY"
POST /api/encrypt: Realiza a criptografia:


curl -X POST http://localhost:8080/api/encrypt -d "text=HELLO&key=KEY"
POST /api/decrypt: Realiza a descriptografia:


curl -X POST http://localhost:8080/api/decrypt -d "text=RIJVS&key=KEY"
