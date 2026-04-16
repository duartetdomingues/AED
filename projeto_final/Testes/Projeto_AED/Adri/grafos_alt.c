#include <stdio.h>
#include <stdlib.h>

#include "funcoes_a.h"	
#include "LinkedList.h"
#include "Filas_Prioridade.h"
#include "grafos.h"


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
int determinar_salas(int** maze, int** maze_etiquetas, int max_linhas, int max_colunas, int celulas_nbrancas) {

	int i=0, j = 0,k=0,h;
	int count_etiquetas = 0;

	int t = 0, x = 0;
	int* id = (int*)calloc(max_colunas, sizeof(int));
	int* sz = (int*)calloc(max_colunas, sizeof(int));


	for (i = 0;i < celulas_nbrancas;i++) {
		maze_etiquetas[maze[i][0]][maze[i][1]] = -1;
	}

	i = 0;
	j = 0;
	while (maze_etiquetas[i][j] != 0) {		/*Encontrar a primeira célula branca*/
		if (j < max_colunas)
			j++;
		else if (i < max_linhas) {
			i++;
			j = 0;
		}
		else
			break;
	}

	for (k = 0;k < (max_colunas - 2);k++) {
		
		for (i = 0; i < (max_linhas - 1); i++) {
			if (id[i] == 0)
			{
				id[i] = i; sz[i] = 1;
			}
		}

		
		for(h = 0; h < (max_linhas - 2); h++) {
			for (i = maze_etiquetas[h][k]; i != id[i]; i = id[i]);
			for (j = maze_etiquetas[h+1][k]; j != id[j]; j = id[j]);
			if (i == j) continue;
			if (sz[i] < sz[j]) {
				id[i] = j;
				sz[j] += sz[i];
				t = j;
				count_etiquetas++;
			}
			else {
				id[j] = i;
				sz[i] += sz[j];
				t = i;
				count_etiquetas++;
			}
			for (i = maze_etiquetas[i][k]; i != id[i]; i = x) {
				x = id[i];
				id[i] = t; 
			}
			for (j = maze_etiquetas[i+1][k]; j != id[j]; j = x) {
				x = id[j];
				id[j] = t;
			}
		}

		
		for (h = 0; h < (max_linhas - 2); h++) {

			for (i = maze_etiquetas[h][k]; i != id[i]; i = id[i]);
			for (j = maze_etiquetas[h][k+1]; j != id[j]; j = id[j]);
			if (i == j) continue;
			if (sz[i] < sz[j]) {
				id[i] = j;
				sz[j] += sz[i];
				t = j;
				count_etiquetas++;
			}
			else {
				id[j] = i;
				sz[i] += sz[j];
				t = i;
				count_etiquetas++;
			}
			for (i = maze_etiquetas[i][k]; i != id[i]; i = x) {
				x = id[i];
				id[i] = t;
			}
			for (j = maze_etiquetas[i][k+1]; j != id[j]; j = x) {
				x = id[j];
				id[j] = t;
			}

		}
	}
	
	/*
	for (i = 0; i < (max_linhas-1); i++) { //fazer linha a linha e etiquetar linha a linha em vez de fazer td de uma vez
		for(j=0;j<(max_colunas-1);j++){
			
			id[i][j] = i; 
			
			sz[i][j] = 1;
			
		}
	}
	
	 for (i = 0; i < max_linhas-1; i++) {
		for(j=0;j<max_colunas-1;j++){
			if(j<max_colunas){
				for (i = maze_etiquetas[i][j]; i != id[i][j]; i = id[i][j]);

				for (j = maze_etiquetas[i][j+1]; j != id[i][j+1]; j = id[i][j+1]);

				if (i == j) continue;

				if (sz[i][j] < sz[i][j+1]) {
					id[i][j] = j; 
					sz[i][j+1] += sz[i][j]; 
					t = j;
					count_etiquetas++;
				}
				else {
					id[i][j+1] = i; 
					sz[i][j] += sz[i][j+1]; 
					t = i;
					count_etiquetas++;
				}
				for (i = maze_etiquetas[i][j]; i != id[i][j]; i = x) { 
					x = id[i][j]; 
					id[i][j] = t;
				}
				for (j = maze_etiquetas[i][j+1]; j != id[i][j+1]; j = x) { 
					x = id[i][j+1];
					id[i][j+1] = t;
				}
			}
			
			if(i<max_linhas){
				for (i = maze_etiquetas[i][j]; i != id[i][j]; i = id[i][j]);

				for (j = maze_etiquetas[i+1][j]; j != id[i][j+1]; j = id[i][j+1]);

				if (i == j) continue;

				if (sz[i][j] < sz[i][j+1]) {
					id[i][j] = j; 
					sz[i][j+1] += sz[i][j]; 
					t = j;
					count_etiquetas++;
				}
				else {
					id[i][j+1] = i; 
					sz[i][j] += sz[i][j+1]; 
					t = i;
					count_etiquetas++;

				}
				for (i = maze_etiquetas[i][j]; i != id[i][j]; i = x) {
					x = id[i][j];
					id[i][j] = t;
				}
				for (j = maze_etiquetas[i][j+1]; j != id[i][j+1]; j = x) {
					x = id[i][j+1];
					id[i][j+1] = t;
				}
			}
		}
	}*/
	 printf("cont_etiquetas=%d\n", count_etiquetas);
	 return count_etiquetas;

}

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
grafo* determinar_grafo(int** maze_etiquetas,int** lista_nbrancas, int max_linhas, int max_colunas,int celulas_nbrancas,int salas) {

	int linha = 0;
	int coluna = 0;
	int sala_inicial = 0;
	int sala_final = 0;
	int i = 0;
	grafo* grafo_salas = NULL;
	
	for (i = 0;i < celulas_nbrancas;i++) {
		if (lista_nbrancas[i][2] != -1) {
			linha = lista_nbrancas[i][0];
			coluna = lista_nbrancas[i][1];
			if ((linha != 0) && (linha != max_linhas - 1))	/*não pode estar no max_linhas?*/ {
				sala_inicial = maze_etiquetas[linha - 1][coluna];
				sala_final = maze_etiquetas[linha + 1][coluna];
				if ((sala_inicial != 0) && (sala_final != 0) && (sala_inicial != sala_final)) {
					if (!Inserir_grafo(grafo_salas, sala_inicial, sala_final, lista_nbrancas[i],salas)) {
						
						return NULL;
					}
					
				}
			}
			if ((coluna != 0) && (coluna != max_linhas - 1)) {
				sala_inicial = maze_etiquetas[linha][coluna - 1];
				sala_final = maze_etiquetas[linha][coluna + 1];
				if ((sala_inicial != 0) && (sala_final != 0) && (sala_inicial != sala_final)) {	/*Inclui restricao de duas paredes seguidas serem nao quebraveis*/
					
					if (!Inserir_grafo(grafo_salas, sala_inicial, sala_final, lista_nbrancas[i],salas)) {
						
						return NULL;
					}
				}
				
			}
			
		}
		
	}
	
	return grafo_salas;
}


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
grafo* Criar_grafo(int numero_salas) {

	grafo* g = (grafo*)calloc(1, sizeof(grafo));

	if (g != NULL) {
		g->numero_sala = numero_salas;
		printf("%d\n", numero_salas);
		g->lista = (LinkedList**)calloc(numero_salas, sizeof(LinkedList*));	
	}
	return g;
}

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
void Liberta_grafo(grafo* g) {

	free(g->lista);
	free(g);
}


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
int Comparar_Adjacencias(Item a, Item b) {

	if (((adjacencia*)a)->vertice_ligado < ((adjacencia*)b)->vertice_ligado)
		return -1;
	if (((adjacencia*)a)->vertice_ligado > ((adjacencia*)b)->vertice_ligado)
		return 1;
	
	return 0;
}


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
int Inserir_grafo(grafo* grafo_salas,int sala_inicial, int sala_final,int* dados,int numero_salas) {

	int sala_menor = 0;
	adjacencia* adj_aux = NULL;

	if (sala_inicial > sala_final) {
		sala_menor = sala_final;	/*Posso usar a função trocar aqui?*/
		sala_final = sala_inicial;
		sala_inicial = sala_menor;
	}

	if (grafo_salas == NULL)
		grafo_salas = Criar_grafo(numero_salas);

	
	adj_aux=procurar(grafo_salas, sala_inicial, sala_final);

	if ((adj_aux) == NULL) {
		adj_aux = (adjacencia*)calloc(1, sizeof(adjacencia));
		if (adj_aux == NULL)
			return 0;

		adj_aux->vertice_ligado = sala_final;
		adj_aux->dados = dados;
		grafo_salas->lista[sala_inicial]=insertSortedLinkedList(grafo_salas->lista[sala_inicial], (Item)adj_aux, &Comparar_Adjacencias, NULL);
	}
	else {
		if (adj_aux->dados[2] > dados[2])
			adj_aux->dados = dados;
	}
	return 1;		
}


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
adjacencia* procurar(grafo* g, int vertice_inicial, int vertice_final) {

	int vertice_menor = 0;
	Item aux_1 = NULL;

	if (g == NULL)
		return NULL;
	
	if (vertice_inicial > vertice_final) {
		vertice_menor = vertice_final;		
		vertice_final = vertice_inicial;
		vertice_inicial = vertice_menor;
	}
	
	
	aux_1=g->lista[vertice_inicial];

	while ((aux_1 = (adjacencia*)getNextNodeLinkedList(aux_1)) != NULL) {
		if (((adjacencia*)aux_1)->vertice_ligado == vertice_final) {
			return (adjacencia*)aux_1;
		}
	}
	return NULL;
}

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
int Comparar_Inteiros(Item a, Item b) {
	
	return ((*((int*)a)) > (* ((int*)b)));
}



#define P (custos[v] + ((adjacencia*)t)->dados[2])
#define maxWT 999999999


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
void Caminho_Mais_Curto(grafo* g, int no_inicial, int anteriores[], int custos[])
{
	int v=0, w=0;
	LinkedList* t=NULL;

	int* indices=(int*)calloc(g->numero_sala, sizeof(int)); 
	Filas_Prioridade_Inicializar(g->numero_sala,&Comparar_Inteiros);
	for (v = 0; v < g->numero_sala; v++)
	{
		anteriores[v] = -1;
		custos[v] = maxWT;
		indices[v] = v; 
		Filas_Prioridade_Inserir((Item)&indices[v]); 
	}
	custos[no_inicial] = 0;
	Filas_Prioridade_Diminuir_Prioridade((Item)custos,no_inicial, g->numero_sala); 
	while (Filas_Prioridade_Tamanho())
		if (custos[v = *((int*)Filas_Prioridade_Apagar_Min())] != maxWT)
			for (t = g->lista[v]; t != NULL; t = getNextNodeLinkedList(t))
				if (custos[w = ((adjacencia*)t)->vertice_ligado] > P)
				{
					custos[w] = P;
					Filas_Prioridade_Diminuir_Prioridade((Item)custos,w, g->numero_sala); 
					anteriores[w] = v;
				}

	free(indices);
}


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
int Resolver_Labirinto(int** lista_nbrancas,int celulas_nbrancas,int max_linhas,int max_colunas,LinkedList** caminho_mais_curto,
					   int l_chegada, int c_chegada) {

	grafo* g;
	int salas = 0;
	int* anteriores = NULL;
	int* custos = NULL;
	int etiqueta = 0;
	int anterior = 0;
	LinkedList* fila=NULL;
	adjacencia* aux;
	int somacustos = 0;

	int** maze_etiquetas = criar_maze(max_linhas, max_colunas);

	if (maze_etiquetas == NULL)		/*Proteger para custos n ficar igual a -1*/
		return -1;

	if ((salas = determinar_salas(lista_nbrancas, maze_etiquetas, max_linhas, max_colunas,celulas_nbrancas)) == 0)
		return -1;
	
	if ((fila = initLinkedList()) != NULL)		/*Atenção à condição*/
		return -1;
	
	/* Se sala de partida = sala de chegada, return 0   */
	/* if (maze_etiquetas[0][0] == maze_etiquetas[l_chegada][c_chegada])
		return 0; */
	

	g=determinar_grafo(maze_etiquetas,lista_nbrancas, max_linhas, max_colunas, celulas_nbrancas,salas);
	anteriores = (int*)calloc(g->numero_sala, sizeof(int));
	custos = (int*)calloc(g->numero_sala, sizeof(int));

	Caminho_Mais_Curto(g,maze_etiquetas[0][0],anteriores,custos);
	
	etiqueta = maze_etiquetas[l_chegada][c_chegada];  /*etiquetas vai ser = à sala de chegada*/
	somacustos = custos[etiqueta]; /*O vetor custos acumula os custos ate à sala final*/
	while (etiqueta != maze_etiquetas[0][0]) { /*enqt n estivermos na sala de partida*/
		anterior = anteriores[etiqueta]; /*guarda o indice da sala anterior para onde queremos andar a seguir*/
		/*Meter numa fila as coordenadas da celula quebrada*/
		aux = procurar(g, anterior, etiqueta);
		fila = insertUnsortedLinkedList(fila, (Item)aux->dados);
		/*vamos andar para sala anterior*/
		etiqueta = anterior;
	}
	Liberta_grafo(g);
	free(custos);
	free(anteriores);

	libertar_maze(maze_etiquetas, max_linhas, max_colunas);
	*caminho_mais_curto = fila; /*Lista de coordenadas com paredes quebradas*/
	printf("%d\n",somacustos);
	return somacustos;
}


void Liberta_dados(Item a) {
	
}