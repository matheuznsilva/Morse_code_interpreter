# Nome do executável
EXEC = morse

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos fonte
SRCS = main.c ArvoreBinaria.c funcoes.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(EXEC)

# Linkagem
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar arquivos .c para .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Limpar arquivos objetos e executável
clean:
	rm -f $(OBJS) $(EXEC)
