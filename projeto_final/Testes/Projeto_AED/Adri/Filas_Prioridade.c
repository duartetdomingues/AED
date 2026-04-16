#include <stdio.h>
#include <stdlib.h>

#include "defs.h"


#include "Filas_Prioridade.h"

static int(* lessPri)(Item A, Item B);
static Item* fila;
static int posicao_livre;
static int tamanho_fila;


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
void Filas_Prioridade_Inicializar(unsigned tamanho,int(* funcao_less)(Item A,Item B)) {
	
	fila = (Item*)malloc(tamanho * sizeof(Item));
	if (fila == NULL)
		exit(0);
    lessPri = funcao_less;
	tamanho_fila = tamanho;
	posicao_livre = 0;
}


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
void Filas_Prioridade_Inserir(Item a) {

	if ((posicao_livre + 1) < tamanho_fila) {
		fila[posicao_livre] = a;
		Filas_Prioridade_Aumentar_Prioridade(fila, posicao_livre);
		posicao_livre++;
	}
	else
		exit(0);
}


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
Item Filas_Prioridade_Apagar_Min() {

	int indice = 0;
	int indice_min = 0;

	for(indice=1, indice_min=0;indice<posicao_livre;indice++)
		if (fila[indice] < fila[indice_min]) {
			indice_min = indice;
		}
    Trocar(fila[indice_min], fila[posicao_livre - 1]);
  
	return (fila[--posicao_livre]);
}


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
void Trocar(Item a, Item b) {

	Item aux;

	aux = a;
	a = b;
	b = aux;
}


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
void Filas_Prioridade_Diminuir_Prioridade(Item lista_prioridades[], int indice, int N) {
	
	int indice_no_descendente; /* índice de um nó descendente */

	while (2 * indice < N - 1) { /* enquanto não chegar às folhas */
		indice_no_descendente = 2 * indice + 1;
		/* Selecciona o maior descendente. */
		/* Nota: se índice_no_descendente é N-1, então só há um descendente */ 
		if (indice_no_descendente < (N - 1) && (*lessPri)(lista_prioridades[indice_no_descendente], lista_prioridades[indice_no_descendente + 1])) 
			indice_no_descendente++;
		if (!(*lessPri)(lista_prioridades[indice_no_descendente], lista_prioridades[indice_no_descendente])) 
			break; /* condição acervo satisfeita */
		Trocar(lista_prioridades[indice], lista_prioridades[indice_no_descendente]);
		
		/* continua a descer a árvore */
		indice = indice_no_descendente;
	}
}

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
void Filas_Prioridade_Aumentar_Prioridade(Item lista_prioridades[], int indice)
{
	while (indice > 0 && (*lessPri)(lista_prioridades[(indice - 1) / 2], lista_prioridades[indice])) {
		Trocar(lista_prioridades[indice], lista_prioridades[(indice - 1) / 2]);
		indice = (indice - 1) / 2;
	}
}


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
int Filas_Prioridade_Tamanho() {

	if (tamanho_fila == 0)
		return 0;
	else
		return 1;
}