# Adriana Mooney e Matilde Neves, última modificação nov 2021-11-
#
# To compile prog:
#    make
# To run tests:
#    make t
#

CC=gcc
CFLAGS=-g -Wall -ansi -pedantic

roap: main.o funcoes_a.o Filas_Prioridade.o grafos_alt.o LinkedList.o sparse.o
	$(CC) $(CFLAGS) -o roap main.o funcoes_a.o Filas_Prioridade.o grafos_alt.o LinkedList.o sparse.o

main.o: main.c funcoes_a.h grafos.h LinkedList.h
	$(CC) -c $(CFLAGS) main.c funcoes_a.h grafos.h LinkedList.h

funcoes_a.o: funcoes_a.c funcoes_a.h
	$(CC) -c $(CFLAGS) funcoes_a.c

Filas_Prioridade.o: Filas_Prioridade.c Filas_Prioridade.h
	$(CC) -c $(CFLAGS) Filas_Prioridade.c

grafos.o: grafos_alt.c grafos.h
	$(CC) -c $(CFLAGS) grafos_alt.c

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) -c $(CFLAGS) LinkedList.c

sparse.o: sparse.c sparse.h
	$(CC) -c $(CFLAGS) sparse.c

clean::
	rm -f *.o core a.out roap *~



FILES_1= $(shell ls Testes/1_submissao/Testes_A1/*.in1)
FILES_2= $(shell ls Testes/1_submissao/Testes_A2/*.in1)
FILES_3= $(shell ls Testes/1_submissao/Testes_A3/*.in1)
FILES_4= $(shell ls Testes/1_submissao/Testes_A4/*.in1)
FILES_5= $(shell ls Testes/1_submissao/Testes_A5/*.in1)
FILES_6= $(shell ls Testes/1_submissao/Testes_A6/*.in1)
FILES_7= $(shell ls Testes/1_submissao/Saladas/*.in1)
FILES_8= $(shell ls Testes/1_submissao/Sizeable/*.in1)

FILES_1A= $(shell ls Testes/Ultimate_Testes_1/*.in1)

FILES_A= $(shell ls Testes/2_submissao/Bilhar_Pequeno/*.in)
FILES_B= $(shell ls Testes/2_submissao/Chess_Party/*.in)
FILES_C= $(shell ls Testes/2_submissao/Enunciado/*.in)
FILES_D= $(shell ls Testes/2_submissao/Small/*.in)


VALG = valgrind --leak-check=full

t1:
	for F in ${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4} ${FILES_5} ${FILES_6} ${FILES_7} ${FILES_8}; do  ./roap -s $$F ; done;

tv1:
	for F in ${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4} ${FILES_5} ${FILES_6} ${FILES_7} ${FILES_8}; do ${VALG} ./roap -s $${F} ; done;

tt1:
	for F in ${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4} ${FILES_5} ${FILES_6} ${FILES_7} ${FILES_8}; do  time ./roap -s $${F} ; done;

t1_1:
	for F in ${FILES_1A}; do  ./roap -s $$F ; done;

tv1_1:
	for F in ${FILES_1A}; do ${VALG} ./roap -s $${F} ; done;

tt1_1:
	for F in ${FILES_1A};do  time ./roap -s $${F} ; done;

t2:
	for F in ${FILES_A} ${FILES_B} ${FILES_C} ${FILES_D}; do  ./roap -s $$F ; done;

tv2:
	for F in ${FILES_A} ${FILES_B} ${FILES_C} ${FILES_D}; do ${VALG} ./roap -s $${F} ; done;

tt2:
	for F in ${FILES_A} ${FILES_B} ${FILES_C} ${FILES_D}; do  time ./roap -s $${F} ; done;