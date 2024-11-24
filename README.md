
 ## **Descrição:**

O projeto Lockey é uma aplicação web de criptografia e descriptografiação baseada na cifra de Vigenère. O sistema é composto por um backend em C e um frontend em HTML, CSS e JavaScript. O backend utiliza a biblioteca Mongoose para gerenciar requisições HTTP e serve arquivos estáticos do diretório frontend.

##

### **1. Sistema Operacional:**
O projeto foi desenvolvido para ser executado em **Windows** (testado com **Windows 10**).

## **2. Dependências:**

#### **Backend (C):**

- **Compilador C:** É necessário um compilador compatível, como **MinGW** ou **Microsoft Visual Studio**.

- **GCC:** O **GCC** (GNU Compiler Collection) é um compilador amplamente utilizado para **C/C++**. Se você optar pelo **MinGW** (um GCC para Windows), basta garantir que ele esteja instalado corretamente. Com o **MinGW**, você pode usar o comando `gcc` para compilar o **backend**.

- **Mongoose:** Biblioteca para gerenciamento de requisições HTTP (já incluída no projeto).

- **cJSON:** Biblioteca para manipulação de **JSON** no **C** (já incluída no projeto).

- **Winsock2:** Biblioteca para gerenciamento de **sockets** no **Windows** (também incluída no projeto).

#### **Frontend:**
O projeto foi desenvolvido para ser executado em **Windows** (testado com **Windows 10**)
- **Node.js:** Necessário para instalar as dependências do **Node** no diretório **frontend**.
  - Baixar **Node.js:** Acesse [nodejs.org](https://nodejs.org) e baixe a versão recomendada para o seu sistema operacional (**Windows**). Após a instalação, o **npm** (Node Package Manager) será instalado junto com o **Node.js**.

## **3. Tecnologias Utilizadas:**
- **Frontend:** **HTML**, **CSS**, **JavaScript**.
- **Backend:** Linguagem **C**, com uso das bibliotecas **Mongoose** e **cJSON**.

## **Fluxo de Instalação e Execução:**

### **Passo 1: Baixar o Projeto.**
```bash

#### Via Git:
Clone o repositório para seu diretório local.

git clone https://github.com/cauanmorais/lockey.git

Via ZIP: Baixe o arquivo ZIP do repositório e extraia-o em um diretório de sua escolha.

Passo 2: Instalar Dependências do Node.js:

Abra o diretório lockey no VS Code ou no terminal. Acesse o diretório frontend e instale as dependências do Node.js.

cd frontend
npm install

Passo 3: Compilar o Backend em C:

Instalar o MinGW (GCC para Windows):

Caso você ainda não tenha o MinGW ou o GCC instalado, faça o download em https://sourceforge.net/projects/gcc-win64/ e siga as instruções para instalação. O GCC é o compilador utilizado para compilar o código C do backend.

O GCC será o compilador utilizado para compilar o código C do backend.

Caso esteja utilizando MinGW, o comando para compilar será gcc.

Compilando o Servidor:

Acesse o diretório backend do projeto. Compile o servidor utilizando o Makefile ou GCC.

Usando o make:

make 

Usando o mingw32-make (versão do Make para o MinGW)

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

Passo 5: Testar a Aplicação:

Acesse os arquivos HTML diretamente no navegador.

Para testar a aplicação, você pode abrir os arquivos HTML diretamente no navegador. O servidor já está configurado para servir os arquivos do diretório frontend, mas não é necessário acessar através de um servidor. Basta abrir o arquivo desejado diretamente.

Navegue até o diretório onde o projeto foi salvo em seu computador. Esse diretório pode variar dependendo de onde você escolheu armazenar o projeto, por exemplo: C:\Projetos\Lockey\frontEnd ou D:\Meus Projetos\Lockey\frontEnd.

Dentro da pasta frontend, localize o arquivo index.html (ou qualquer outro arquivo HTML que queira testar).
Clique com o botão direito sobre o arquivo index.html e selecione a opção "Abrir com" e escolha o navegador de sua preferência.
O navegador abrirá o arquivo diretamente, e você poderá interagir com a aplicação de criptografia e descriptografiação.

Passo 6: Parar o Servidor:

Para interromper o servidor, pressione CTRL+C no terminal onde o servidor está rodando.

Funcionalidade de Criptografia e Descriptografia:

## Testar o Sistema

### Testar a Validação da Chave
A chave deve ser validada antes de qualquer operação de criptografia ou descriptografação. Isso é feito automaticamente quando o usuário insere a chave nas páginas de criptografia/descriptografação.

Exemplos de chaves válidas:
1. **chave**: `segredo`
2. **chave**: `criptografia`
3. **chave**: `vigenere`

---

### Testar a Criptografia
Vá para a página **criptografia.html** e insira um texto e uma chave válida. O sistema criptografará o texto e exibirá o resultado.

Exemplos:
- **Texto Original**: `Este é um teste de criptografia.`  
  **Chave**: `segredo`  
  **Texto Criptografado**: `wwzv é yp hwwzv hh qjmvksjfsjor.`

- **Texto Original**: `Bem-vindo ao Lockey!`  
  **Chave**: `vigenere`  
  **Texto Criptografado**: `wms-zvrus vw rspovc!`

- **Texto Original**: `A cifra de Vigenere é segura.`  
  **Chave**: `criptografia`  
  **Texto Criptografado**: `C tquko jv Vnoepvzt é lsmlrf.`

---

### Testar a Descriptografia
Após criptografar o texto, você pode copiá-lo para a página **descriptografia.html** e usar a mesma chave para descriptografar o texto.

Exemplos:
- **Texto Criptografado**: `wwzv é yp hwwzv hh qjmvksjfsjor.`  
  **Chave**: `segredo`  
  **Texto Descriptografado**: `Este é um teste de criptografia.`

- **Texto Criptografado**: `wms-zvrus vw rspovc!`  
  **Chave**: `vigenere`  
  **Texto Descriptografado**: `Bem-vindo ao Lockey!`

- **Texto Criptografado**: `c tquko jv vnoepvzt é lsmlrf.`  
  **Chave**: `criptografia`  
  **Texto Descriptografado**: `A cifra de Vigenere é segura.`

---

### Observações Importantes
1. Certifique-se de usar chaves válidas compostas apenas por letras (sem números ou caracteres especiais).
2. A chave deve ter pelo menos um caractere e pode ter letras maiúsculas ou minúsculas.
3. Caracteres que não sejam letras no texto (como espaços, números ou pontuação) permanecem inalterados durante a criptografia e descriptografia.

---
```

## Contribuições:

Se você deseja contribuir para o projeto, clone o repositório e faça suas alterações. Em seguida, envie um pull request com suas melhorias.

## Licença:

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para mais detalhes.
