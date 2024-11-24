CC = gcc
CFLAGS = -lm -lws2_32 -mthreads
SOURCES = server.c mongoose.c cJSON.c
OUTPUT = server

# Compila o código e gera o executável
all:
	$(CC) $(SOURCES) -o $(OUTPUT) $(CFLAGS)

# Limpa os arquivos gerados
clean:
	del $(OUTPUT).exe
