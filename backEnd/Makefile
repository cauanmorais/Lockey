CC = gcc
CFLAGS = -lm -lws2_32 -mconsole  # Usando -mconsole para indicar que é um aplicativo de console
SOURCES = server.c mongoose.c
OUTPUT = servidor

# Compila o código e gera o executável
all:
	$(CC) $(SOURCES) -o $(OUTPUT) $(CFLAGS)

# Limpa o arquivo gerado
clean:
	del $(OUTPUT).exe
