/******************************************************************************
 * (c) 2021-2022 Adriana Monney e Matilde Neves 
 * Última modificação: 
 *
 * NOME
 *   grafos.h
 *
 * DESCRIÇÃO
 *   Funções que manipulam grafos, e auxiliares para o algoritmo de Dijsktra
 *
 * COMENTÁRIOs
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

#ifndef GRAFOS
#define GRAFOS

 /* Header file for the definition of the Item type */
#include "defs.h"
#include "LinkedList.h"


/*
 *  Data type: LinkedList
 *
 *  Description: Node of a linked list
 */
typedef struct Grafo {
    int numero_sala;
    int aresta;
    LinkedList** lista;
}grafo;


/*
 *  Data type: LinkedList
 *
 *  Description: Node of a linked list
 */
typedef struct Adjacencia {
    int vertice_ligado;
    int* dados;				/*Inclui o x, y e o custo*/
}adjacencia;


/******************************************************************************
 * determinar_salas()
 *
 * Argumentos: maze - ponteiro para vetor que guarda o labirinto do ficheiro
 *			   maze_etiquetas - ...
               max_linhas - número máximo de linhas do labrinto
               max_colunas - número máximo de colunas do labirinto
               celulas_nbrancas - número de células não brancas
 * Retorno: (int) -> número de salas
 * Side-Effects: none
 *
 * Descrição:
 *
 *****************************************************************************/
int determinar_salas(int** maze, int** maze_etiquetas, int max_linhas, int max_colunas, int celulas_nbrancas);


/******************************************************************************
 * determinar_grafo()
 *
 * Argumentos: maze_etiquetas -
 *			   lista_nbrancas -
               max_linhas - número máximo de linhas do labrinto
               max_colunas - número máximo de colunas do labirinto
               celulas_nbrancas - número de células não brancas
 * Retorno: (grafo*) -> grafo, onde os vértices representam as salas, e as arestas
           que os ligam, têm como custo a célula cinzenta de menor custo que 
           delimita as duas salas 
 * Side-Effects: none
 *
 * Descrição:
 *
 *****************************************************************************/
grafo* determinar_grafo(int** maze_etiquetas, int** lista_nbrancas, int max_linhas, int max_colunas, int celulas_nbrancas,int salas);


/******************************************************************************
 * Criar_grafo()
 *
 * Argumentos: numero_salas - número de salas

 * Retorno: (grafo*) ->

 * Side-Effects: none
 *
 * Descrição:
 *
 *****************************************************************************/
grafo* Criar_grafo(int numero_salas);


/******************************************************************************
 * Liberta_grafo()
 *
 * Argumentos: g - grafo

 * Retorno: (void)

 * Side-Effects: none
 *
 * Descrição: Liberta a memória alocada para o grafo g.
 *
 *****************************************************************************/
void Liberta_grafo(grafo* g);


/******************************************************************************
 * Comparar_Adjacencias()
 *
 * Argumentos: a -
               b -

 * Retorno: (int) - -1->....,1->.....

 * Side-Effects: none
 *
 * Descrição: ...
 *
 *****************************************************************************/
int Comparar_Adjacencias(Item a, Item b);


/******************************************************************************
 * Inserir_grafo()
 *
 * Argumentos: grafo_salas -
               sala_inicial -
               sala_final - 
               *dados - 
               numero_salas - número de salas

 * Retorno: (int) - 1 se correu tudo bem

 * Side-Effects: none
 *
 * Descrição: ...
 *
 *****************************************************************************/
int Inserir_grafo(grafo* grafo_salas, int sala_inicial, int sala_final, int* dados, int numero_salas);


/******************************************************************************
 * procurar()
 *
 * Argumentos: g -
               vertice_inicial -
               vertice_final -

 * Retorno: (adjacencia*) - 

 * Side-Effects: none
 *
 * Descrição: ...
 *
 *****************************************************************************/
adjacencia* procurar(grafo* g, int vertice_inicial, int vertice_final);


/******************************************************************************
 * Caminho_Mais_Curto()
 *
 * Argumentos: g - grafo principal
               no_inicial - nó inicial para cálculo do caminho mais curto
               no_final - nó final para cálculo do caminho mais curto
               anteriores - vetor dos nós no caminho entre o nó inicial e
 * o nó final
               custos - vetor dos custos respetivos aos nós no caminho
 * entre o nó inicial e o nó final

 * Retorno: (void)

 * Side-Effects: none
 *
 * Descrição: Aplicação do algoritmo de Dijkstra , com base no código
              disponibilizado nos slides da UC.
 *
 *****************************************************************************/
int Comparar_Inteiros(Item a, Item b); 


/******************************************************************************
 * Caminho_Mais_Curto()
 *
 * Argumentos: g - grafo principal
               no_inicial - nó inicial para cálculo do caminho mais curto
               no_final - nó final para cálculo do caminho mais curto
               anteriores - vetor dos nós no caminho entre o nó inicial e
 * o nó final
               custos - vetor dos custos respetivos aos nós no caminho
 * entre o nó inicial e o nó final

 * Retorno: (void)

 * Side-Effects: none
 *
 * Descrição: Aplicação do algoritmo de Dijkstra , com base no código
              disponibilizado nos slides da UC.
 *
 *****************************************************************************/
void Caminho_Mais_Curto(grafo* g, int no_inicial, int anteriores[], int custos[]);


/******************************************************************************
 * Resolver_Labirinto()
 *
 * Argumentos:  lista_nbrancas -  
 *              celulas_nbrancas - 
 *              max_linhas - 
 *              max_colunas - 
 *              caminho_mais_curto - 
 *              l_partida - 
 *              c_partida - 
 *              l_chegada - 
 *              c_chegada - 
 *              
 * Retorno: (int)

 * Side-Effects: none
 *
 * Descrição:   Resolução do problema principal, manipulando as funções 
 *              implementadas
 *
 *****************************************************************************/
int Resolver_Labirinto(int** lista_nbrancas, int celulas_nbrancas, int max_linhas, int max_colunas, LinkedList** caminho_mais_curto,
                       int l_chegada, int c_chegada);


/******************************************************************************
 * Resolver_Labirinto()
 *
 * Argumentos:  lista_nbrancas -
 *              celulas_nbrancas -
 *              max_linhas -
 *              max_colunas -
 *              caminho_mais_curto -
 *              l_partida -
 *              c_partida -
 *              l_chegada -
 *              c_chegada -
 *
 * Retorno: (int)

 * Side-Effects: none
 *
 * Descrição:   Resolução do problema principal, manipulando as funções
 *              implementadas
 *
 *****************************************************************************/
void Liberta_dados(Item a);

#endif
