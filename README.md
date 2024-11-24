# **Projeto Lockey**

## **Descrição**
O projeto **Lockey** é uma aplicação web de criptografia e descriptografiação baseada na cifra de **Vigenère**. O sistema é composto por um **backend** em **C** e um **frontend** em **HTML**, **CSS** e **JavaScript**. O **backend** utiliza a biblioteca **Mongoose** para gerenciar requisições HTTP e serve arquivos estáticos do diretório **frontend**.

## **Requisitos do Sistema**

### **1. Sistema Operacional:**
O projeto foi desenvolvido para ser executado em **Windows** (testado com **Windows 10**).

### **2. Dependências:**

#### **Backend (C):**

- **Compilador C:** É necessário um compilador compatível, como **MinGW** ou **Microsoft Visual Studio**.

- **GCC:** O **GCC** (GNU Compiler Collection) é um compilador amplamente utilizado para **C/C++**. Se você optar pelo **MinGW** (um GCC para Windows), basta garantir que ele esteja instalado corretamente. Com o **MinGW**, você pode usar o comando `gcc` para compilar o **backend**.

- **Mongoose:** Biblioteca para gerenciamento de requisições HTTP (já incluída no projeto).

- **cJSON:** Biblioteca para manipulação de **JSON** no **C** (já incluída no projeto).

- **Winsock2:** Biblioteca para gerenciamento de **sockets** no **Windows** (também incluída no projeto).

#### **Frontend:**
- **HTML, CSS, JavaScript** (já incluídos no projeto).

#### **Backend (Node.js):**
- **Node.js:** Necessário para instalar as dependências do **Node** no diretório **frontend**.
  - Baixar **Node.js:** Acesse [nodejs.org](https://nodejs.org) e baixe a versão recomendada para o seu sistema operacional (**Windows**). Após a instalação, o **npm** (Node Package Manager) será instalado junto com o **Node.js**.

### **3. Tecnologias Utilizadas:**
- **Frontend:** **HTML**, **CSS**, **JavaScript**.
- **Backend:** Linguagem **C**, com uso das bibliotecas **Mongoose** e **cJSON**.

## **Fluxo de Instalação e Execução:**

### **Passo 1: Baixar o Projeto.**
```bash

#### Via Git:
Clone o repositório para seu diretório local.

git clone https://github.com/seuusuario/lockey.git
Via ZIP:
Baixe o arquivo ZIP do repositório e extraia-o em um diretório de sua escolha.

Passo 2: Instalar Dependências do Node.js:

Abra o diretório lockey no VS Code ou no terminal. Acesse o diretório frontend e instale as dependências do Node.js.

cd frontend
npm install

Passo 3: Compilar o Backend em C:

Instalar o MinGW (GCC para Windows):
Caso você ainda não tenha o MinGW ou o GCC instalado, faça o download em https://sourceforge.net/projects/gcc-win64/ e siga as instruções para instalação. O GCC é o compilador utilizado para compilar o código C do backend.

Caso esteja utilizando MinGW, o comando para compilar será gcc.

Compilando o Servidor:
Acesse o diretório backend do projeto. Compile o servidor utilizando o Makefile ou GCC.

Usando o make:

make

Usando o mingw32-make (versão do Make para o MinGW):
mingw32-make

Ou use o gcc diretamente:
gcc server.c mongoose.c cJSON.c -o server -lm -lws2_32 -mthreads

Passo 4: Iniciar o Servidor:
Após compilar o servidor, inicie-o com o comando:

./server.exe

O servidor será iniciado e estará disponível em http://127.0.0.1:8080.

Mensagem de Sucesso:
Você verá uma mensagem no terminal informando que o servidor está rodando e servindo arquivos estáticos do diretório frontend:

Servidor rodando em http://127.0.0.1:8080
Servindo arquivos do diretório: ../frontEnd
Passo 5: Testar a Aplicação
Acesse os arquivos HTML diretamente no navegador.

Para testar a aplicação, você pode abrir os arquivos HTML diretamente no navegador. O servidor já está configurado para servir os arquivos do diretório frontend, mas não é necessário acessar através de um servidor. Basta abrir o arquivo desejado diretamente.

Navegue até o diretório onde o projeto foi salvo em seu computador. Esse diretório pode variar dependendo de onde você escolheu armazenar o projeto, por exemplo: C:\Projetos\Lockey\frontEnd ou D:\Meus Projetos\Lockey\frontEnd.
Dentro da pasta frontend, localize o arquivo index.html (ou qualquer outro arquivo HTML que queira testar).
Clique com o botão direito sobre o arquivo index.html e selecione a opção "Abrir com" e escolha o navegador de sua preferência.
O navegador abrirá o arquivo diretamente, e você poderá interagir com a aplicação de criptografia e descriptografiação.
Passo 6: Parar o Servidor
Para interromper o servidor, pressione CTRL+C no terminal onde o servidor está rodando.

Contribuições:

Se você deseja contribuir para o projeto, clone o repositório e faça suas alterações. Em seguida, envie um pull request com suas melhorias.

Licença:

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para mais detalhes.

Explicações Adicionais:

Como compilar com o make ou mingw32-make:

Use o make ou mingw32-make para compilar o backend. Se não tiver o make instalado, você pode usar o mingw32-make, que é uma versão adaptada do Make para o MinGW no Windows.

Funcionalidade de Criptografia e Descriptografia:

1. Validar a Chave:

Antes de realizar a criptografia ou a descriptografiação, o usuário deve validar a chave inserida. A chave deve ser composta apenas por letras (a-z, A-Z).

A página de criptografia (criptografia.html) ou de descriptografia (descriptografia.html) permite que o usuário insira o texto a ser processado e a chave.

2. Criptografar ou Descriptografar:

O frontend envia os dados para o backend através de requisições HTTP, onde o backend processa o texto utilizando a cifra de Vigenère e retorna o resultado para o frontend.

Testes Manuais e Automatizados:

1. Testes Manuais:

Testar a Criptografia: Vá para a página criptografia.html e insira um texto e uma chave válida. O sistema criptografará o texto e exibirá o resultado.

Testar a Descriptografação: Após criptografar o texto, você pode copiá-lo para a página descriptografacao.html e usar a mesma chave para descriptografar o texto.

Testar a Validação da Chave: A chave deve ser validada antes de qualquer operação de criptografia ou descriptografiação. Isso é feito automaticamente quando o usuário insere a chave nas páginas de criptografia/descriptografação.

2. Testes Automatizados:

Para realizar testes automatizados, você pode usar ferramentas como Postman ou cURL para simular requisições HTTP aos endpoints do servidor.

Exemplos de Requisições:
POST /api/validate-key: Valida a chave de criptografia:

curl -X POST http://localhost:8080/api/validate-key -d "key=KEY"
POST /api/encrypt: Realiza a criptografia:

curl -X POST http://localhost:8080/api/encrypt -d "text=HELLO&key=KEY"
POST /api/decrypt: Realiza a descriptografação:

curl -X POST http://localhost:8080/api/decrypt -d "text=YOURENCRYPTEDTEXT&key=KEY"