#make file example

CC = gcc #compiler
# flags para compilar
CFLAGS= -Wall -std=c99 -O3 -g -O0
TARGET= roap
# gerar variáveis com listas ficheiros de cada tipo para usar nas várias regras
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
HEADERS=$(wildcard *.h)
PDFS=$(wildcard *.pdf)
all: 
	$(CC)$(CFLAGS) main2.c variants.c stack.c projeto_f2_copy.c LinkedList.c dijkstras2.c roap2.h LinkedList.h -o roap

# para criar um tar.gz com todos os ficheiros, dar o comando "make tgz"
tgz: $(TARGET).tar.gz
