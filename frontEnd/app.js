// Inicia com chave vazia se não houver no localStorage
let key = localStorage.getItem("encryptionKey") || "";

// Função para validar a chave
function validateKey(keyInput) {
    return new Promise((resolve, reject) => {
        if (keyInput === "") {
            reject("A chave não pode estar vazia. Por favor, insira uma chave.");
        }

        console.log("Requisição para validar chave: ", keyInput);

        fetch(`http://127.0.0.1:8080/api/validate-key`, {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            body: `key=${encodeURIComponent(keyInput)}`
        })
        .then(response => response.json())
        .then(data => {
            if (data.valid) {
                key = keyInput;
                localStorage.setItem("encryptionKey", key); 
                resolve("Chave válida.");
            } else {
                reject(data.error || "Chave inválida. Por favor, tente novamente.");
            }
        })
        .catch(error => reject("Erro ao validar a chave: " + error));
    });
}


function openModal() {
    const modal = document.getElementById("keyModal");
    if (modal) {
        modal.style.display = "block";  // Exibe o modal
    } else {
        console.error("Modal 'keyModal' não encontrado.");
    }
}

// Função para esconder o modal
function closeModal() {
    const modal = document.getElementById("keyModal");
    if (modal) {
        modal.style.display = "none";  // Esconde o modal
    } else {
        console.error("Modal 'keyModal' não encontrado.");
    }
}

// Função para criptografar o texto
function encryptText(text) {
    return new Promise((resolve, reject) => {
        if (!key.trim()) {
            alert("Nenhuma chave foi definida. Por favor, defina uma chave antes de prosseguir.");
            reject("Chave não definida.");
            return;
        }

        fetch(`http://127.0.0.1:8080/api/encrypt`, {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            body: `key=${encodeURIComponent(key)}&text=${encodeURIComponent(text)}`
        })
        .then(response => response.json())
        .then(data => {
            if (data.result) {
                resolve(data.result);
            } else {
                alert("Erro ao criptografar.");
                reject("Erro na criptografia.");
            }
        })
        .catch(error => {
            console.error("Erro ao criptografar o texto: ", error);
            alert("Erro ao criptografar.");
            reject(error);
        });
    });
}

// Função para descriptografar o texto
function decryptText(text) {
    return new Promise((resolve, reject) => {
        if (!key.trim()) {
            alert("Nenhuma chave foi definida. Por favor, defina uma chave antes de prosseguir.");
            reject("Chave não definida.");
            return;
        }

        fetch(`http://127.0.0.1:8080/api/decrypt`, {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            body: `key=${encodeURIComponent(key)}&text=${encodeURIComponent(text)}`
        })
        .then(response => response.json())
        .then(data => {
            if (data.result) {
                resolve(data.result);
            } else {
                alert("Erro ao descriptografar.");
                reject("Erro na descriptografia.");
            }
        })
        .catch(error => {
            console.error("Erro ao descriptografar o texto: ", error);
            alert("Erro ao descriptografar.");
            reject(error);
        });
    });
}

// Função de criptografar o texto a partir do input
function encryptInputText() {
    const text = document.getElementById("inputText").value;
    if (!key || !text) {
        alert("Chave ou texto não pode estar vazio.");
        return;
    }

    encryptText(text)
        .then(encryptedText => {
            document.getElementById("outputText").value = encryptedText;
        })
        .catch(error => {
            console.error("Erro ao criptografar:", error);
            alert("Erro ao criptografar.");
        });
}

// Função de descriptografar o texto a partir do input
function decryptInputText() {
    const text = document.getElementById("inputText").value;
    if (!key || !text) {
        alert("Chave ou texto não pode estar vazio.");
        return;
    }

    decryptText(text)
        .then(decryptedText => {
            document.getElementById("outputText").value = decryptedText;
        })
        .catch(error => {
            console.error("Erro ao descriptografar:", error);
            alert("Erro ao descriptografar.");
        });
}

// Função para atualizar a chave
function updateKey() {
    const newKey = document.getElementById("keyInput").value.trim();
    if (newKey) {
        validateKey(newKey)
            .then(() => {
                document.getElementById("keyInput").value = key; // Atualiza a chave no campo
                closeModal();  // Fecha o modal após a chave ser validada
            })
            .catch(error => {
                alert(error);
            });
    } else {
        alert("A chave não pode estar vazia.");
    }
}

// Função para verificar se o Enter foi pressionado
function handleEnterPress(event, callback) {
    if (event.key === "Enter") {
        event.preventDefault(); // Evita o comportamento padrão de adicionar uma nova linha (no caso do textarea)
        callback(); // Chama a função fornecida
    }
}

// Função para lidar com o modal da chave
function handleKeyInput(event) {
    handleEnterPress(event, () => {
        const newKey = document.getElementById("keyInput").value.trim();
        if (newKey) {
            updateKey();
        }
    });
}

// Função para habilitar a tecla Enter em campos de criptografia e descriptografiação
function enableEnterToSubmit() {
    const inputTextField = document.getElementById("inputText");
    const keyInputField = document.getElementById("keyInput");

    // Verifica se os campos existem antes de adicionar os eventos
    if (!inputTextField || !keyInputField) {
        console.error("Campos 'inputText' ou 'keyInput' não encontrados.");
        return;
    }

    // Criptografar ao pressionar Enter no campo de texto
    inputTextField.addEventListener("keydown", (event) => {
        handleEnterPress(event, encryptInputText);
    });

    // Descriptografar ao pressionar Enter no campo de texto
    inputTextField.addEventListener("keydown", (event) => {
        handleEnterPress(event, decryptInputText);
    });

    // Atualizar chave ao pressionar Enter no campo de chave
    keyInputField.addEventListener("keydown", (event) => {
        handleEnterPress(event, updateKey);
    });
}

// Verifica a chave ao acessar a página de criptografia
document.addEventListener("DOMContentLoaded", () => {
    if (!key) {
        openModal();  
    } else {
        document.getElementById("keyInput").value = key; // Exibe a chave atual
    }

    // Ativa a função de "Enter" para submissão
    enableEnterToSubmit();
});
