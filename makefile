CFLAGS = -g -Wall -Wextra
CC = gcc

# ARQUIVOS e OBJETOS sao variaveis
ARQUIVOS = conjunto.c auxiliar.c pessoa.c main.c
# $(ARQUIVOS:.c=.o) todo arquivo .c vira .o e é guardado no OBJETOS
OBJETOS = $(ARQUIVOS:.c=.o)

# Nome do executavel
EXECUTAVEL = main

all: $(EXECUTAVEL)

# $@ gera arquivo executavel, neste caso testa_conjunto
$(EXECUTAVEL): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@

# % é um curinga, %.o é qualquer arquivo .o e assim para %.c
# $< sao os arquivos do tipo "arquivo.c"
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJETOS) $(EXECUTAVEL)
