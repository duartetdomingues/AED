/******************************************************************************
 * (c) 2021-2022 Adriana Monney e Matilde Neves
 * Última modificação:
 *
 * NOME:
 *  Filas_Prioridade.h
 *
 * DESCRIÇÃO:
 *  Funções elementares de manipulação de filas de prioridade, baseadas nos slides das 
    aulas teóricas.
 *
 * COMENTÁRIOS:
 *  
 *  Data type list:
 *    Linked list node: LinkedList
 *
 *  Function list:
 *    A) Initialization & Termination
 *        initLinkedList
 *        freeLinkedList
 *
 *    B) Properties
 *        lengthLinkedList
 *
 *    C) Navigation
 *        getNextNodeLinkedList
 *
 *    D) Lookup
 *        getItemLinkedList
 *
 *    E) Insertion - simple at head, sorted
 *       insertUnsortedLinkedList
 *       insertSortedLinkedList
 *
 *  Dependências:
 *    stdio.h
 *    stdlib.h
 *    defs.h
 *
 *****************************************************************************/

#ifndef FILAS_PRIORIDADE
#define FILAS_PRIORIDADE

/* Header file for the definition of the Item type */
#include "defs.h"
#include "LinkedList.h"


/******************************************************************************
 * Filas_Prioridade_Inicializar()
 *
 * Argumentos:  tamanho - tamanho da fila
 *
 * Retorno: (void)

 * Side-Effects: none
 *
 * Descrição: Cria e inicializa uma fila de prioridades
 *
 *****************************************************************************/
void Filas_Prioridade_Inicializar(unsigned tamanho, int(* funcao_less)(Item A, Item B));



/******************************************************************************
 * Filas_Prioridade_Inserir()
 *
 * Argumentos:  a - elemento a inserir na fila de prioridades
 *
 * Retorno: (void)

 * Side-Effects: none
 *
 * Descrição: Insere um elemento na fila de prioridades
 *
 *****************************************************************************/
void Filas_Prioridade_Inserir(Item a);



/******************************************************************************
 * Filas_Prioridade_Apagar_Min()
 *
 * Argumentos:  nenhum
 *
 * Retorno: (Item) - fila sem o elemento 

 * Side-Effects: none
 *
 * Descrição: Elimina elemento com menor prioridade
 *
 *****************************************************************************/
Item Filas_Prioridade_Apagar_Min();



/******************************************************************************
 * Trocar()
 *
 * Argumentos: a e b - elementos a trocar
 *
 * Retorno: (void)

 * Side-Effects: none
 *
 * Descrição: Troca o elemento a com o elemento b
 *
 *****************************************************************************/
void Trocar(Item a, Item b);



/******************************************************************************
 * Filas_Prioridade_Diminuir_Prioridade()
 *
 * Argumentos:  lista_prioridades - vetor dos elementos por ordem de prioridades
                indice - um indice...
                N - ...
 *
 * Retorno: (void) 

 * Side-Effects: none
 *
 * Descrição:   Altera a ordem da fila de prioridades, diminuindo a prioridade 
                do elemento cujo o indice é fornecido
 *
 *****************************************************************************/
void Filas_Prioridade_Diminuir_Prioridade(Item lista_prioridades[], int indice, int N);


/******************************************************************************
 * Filas_Prioridade_Aumentar_Prioridade()
 *
 * Argumentos:  lista_prioridades - vetor dos elementos por ordem de prioridades
 *              indice - um indice...
 *
 * Retorno: (void)
 *
 * Side-Effects: none
 *
 * Descrição:   Altera a ordem da fila de prioridades, aumentando a prioridade
 *              do elemento cujo o indice é fornecido
 *
 *****************************************************************************/
void Filas_Prioridade_Aumentar_Prioridade(Item lista_prioridades[], int indice);

/******************************************************************************
 * Filas_Prioridade_Tamanho()
 *
 * Argumentos:  Nenhum
 *
 * Retorno: (int) - 1->fila não vazia,0->fila vazia
 *
 * Side-Effects: none
 *
 * Descrição:  Verifica se a fila tem elementos ou não
 *
 *****************************************************************************/
int Filas_Prioridade_Tamanho();
#endif
