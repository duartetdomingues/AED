/******************************************************************************
 * (c) 2021 Adriana Monney e Matilde Neves
 * Última modificação: nov 2021-11-
 *
 * NOME
 *   funcoes_a.c
 *
 * DESCRIÇÃO
 *   Implementação das funções "a" e auxiliares às mesmas, chamadas no main.
 *
 * COMENTÁRIOS
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "funcoes_a_alt.h"
#include "sparse.h"


/******************************************************************************
* a1()
*
* Argumentos:	maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*				coluna - número da coluna da célula atual a analisar
*				celulas_nbrancas - número de células não brancas
* Retorno:	(int) - -1->célulapreta,0->célulabranca,1->célulacinzenta
* Side-Effects:	none
*
* Descrição:
*   Identifica o tipo de célula (preta,branca, ou cinzenta)
*****************************************************************************/
int a1(int** maze, int linha, int coluna,int celulas_nbrancas){
	
	return get(maze,linha-1,coluna-1,celulas_nbrancas);		/*conversão das coordenadas do maze para os indices de memória*/ 		
}


/******************************************************************************
* a2()
*
* Argumentos: maze - ponteiro para vetor que guarda o labirinto do ficheiro
*			   linha - número da linha da célula atual a analisar
*			   coluna - número da coluna da célula atual a analisar
*			   celulas_nbrancas - número de células não brancas
* Retorno: (int) - 1->TRUE, 0->FALSE
* Side-Effects: none
*
* Descrição:
*   Indicar se existe algum vizinho que seja célula branca
*****************************************************************************/
int a2(int** maze, int linha, int coluna, int max_linhas,int max_colunas,int celulas_nbrancas) {

	int i = 0;
	
	/*Inclui conversão das coordenadas do maze para os indices de memória */
	if (coluna<max_colunas)
		i = (get(maze,linha-1,coluna,celulas_nbrancas) == 0);
	if(coluna>1)
		i = i || (get(maze,linha-1,coluna - 2,celulas_nbrancas) == 0);
	if(linha>1)
		i = i || (get(maze,linha - 2,coluna-1,celulas_nbrancas) == 0);
	if(linha<max_linhas)
		i = i || (get(maze,linha,coluna-1,celulas_nbrancas) == 0);

	return i;
}


/******************************************************************************
* a3()
*
* Argumentos:	maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*				coluna - número da coluna da célula atual a analisar
*				celulas_nbrancas - número de células não brancas
* Retorno: (int) - 1->TRUE,0->FALSE
* Side-Effects: none
*
* Descrição:
*   Indica se existe algum vizinho que seja célula cinzenta
*****************************************************************************/
int a3(int** maze, int linha, int coluna,int max_linhas,int max_colunas,int celulas_nbrancas){

	int i=0;
	
	/*Inclui conversão*/
	if(coluna>1)
		i= (get(maze,linha-1,coluna-2,celulas_nbrancas)>0);
	if(coluna<max_colunas)
		i= i || (get(maze,linha-1,coluna,celulas_nbrancas)>0);
	if(linha>1)
		i= i || (get(maze,linha-2,coluna-1,celulas_nbrancas)>0);
	if(linha<max_linhas)
		i= i || (get(maze,linha,coluna-1,celulas_nbrancas)>0);
			
	return i;
}


/******************************************************************************
* a4()
*
* Argumentos:	maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*				coluna - número da coluna da célula atual a analisar
*				células_nbrancas - número de células não brancas
* Retorno:	(int) - 1->TRUE,0->FALSE
* Side-Effects:	none
*
* Descrição:
*   Indica se existe algum vizinho que seja célula preta
*****************************************************************************/
int a4(int** maze, int linha, int coluna,int max_linhas,int max_colunas,int celulas_nbrancas){

	int i=0;
	
	/*Inclui conversão*/
	if(coluna>1)
		i= (get(maze,linha-1,coluna-2,celulas_nbrancas)<0);
	if(coluna<max_colunas)
		i= i || (get(maze,linha-1,coluna,celulas_nbrancas)<0);
	if(linha>1)
		i= i || (get(maze,linha-2,coluna-1,celulas_nbrancas)<0);
	if(linha<max_linhas)
		i= i || (get(maze,linha,coluna-1,celulas_nbrancas)<0);
			
	return i;
}


/******************************************************************************
* a5()
*
* Argumentos:	maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*				coluna - número da coluna da célula atual a analisar
*				celulas_nbrancas - número de células não brancas
* Retorno:	(int) - 1->TRUE,0->FALSE
* Side-Effects: none
*
* Descrição:
*	Indica ,se for célula cinzenta, se pode ser quebrada.
*****************************************************************************/
int a5(int** maze, int linha, int coluna,int max_linhas, int max_colunas,int celulas_nbrancas){
	
	int i=0;

	if (get(maze,linha-1,coluna-1,celulas_nbrancas)>0){
		if(coluna>1)
			i= (get(maze,linha-1,coluna-2,celulas_nbrancas)==0);		/*e quebravel nas 4 direcoes*/
		if(coluna<max_colunas)
			i= i && (get(maze,linha-1,coluna,celulas_nbrancas)==0);
		if(linha>1)
			i= i && (get(maze,linha-2,coluna-1,celulas_nbrancas)==0);
		if(linha<max_linhas)
		i= i && (get(maze,linha,coluna-1,celulas_nbrancas)==0);
		return i;
	}
	else
		return -1;
	
}


/******************************************************************************
* a6()
*
* Argumentos:	maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*				coluna - número da coluna da célula atual a analisar
*				max_linhas - número máximo de linhas do labrinto
*				max_colunas - número máximo de colunas do labirinto
* Retorno: (int) - ...
* Side-Effects: none
*
* Descrição:
*	Indica ,se as células forem brancas, se pertencem à mesma sala
*****************************************************************************/
int a6(int** maze,int linha,int coluna,int max_linhas, int max_colunas,int q_x,int q_y,int celulas_nbrancas){

	int i, j, teste_x, teste_y;
	int count_etiquetas=1;
	int* equivalencias=(int*)calloc((max_linhas*max_colunas)/4,sizeof(int));	/*No pior dos casos existirão M*N/4 casas separadas por paredes*/
	int acima = 0;
	int a_esquerda = 0;
	
	/*Alocacao da matriz*/
	int** maze_etiquetas = criar_maze(max_linhas, max_colunas);
	
	for (i = 0;i < celulas_nbrancas;i++) {
		teste_x = maze[i][0];
		teste_y = maze[i][1];
		if ((linha != teste_x) && (q_x != teste_x) && (coluna != teste_y) && (q_y != teste_y))
			maze_etiquetas[teste_x][teste_y] = -1;
		else {
			libertar_maze(maze_etiquetas, max_linhas, max_colunas);

			free(equivalencias);
			return 0;
		}
	}

	i=0;
	j=0;
	while(maze_etiquetas[i][j]!=0){		/*Encontrar a primeira célula branca*/
		if (j<max_colunas)
			j++;
		else if(i<max_linhas){
			i++;
			j=0;
		}
		else
			break;
	}

	equivalencias[1] = 1;
	if (i < max_linhas) {
		maze_etiquetas[i][j] = count_etiquetas;

		for (i = 0;i < max_linhas;i++) {
			for (j = 0;j < max_colunas;j++) {
				if (maze_etiquetas[i][j]== 0) {
					if (i > 0)
						acima = maze_etiquetas[i - 1][j];
					if (j > 0)
						a_esquerda = maze_etiquetas[i][j - 1];
					if ((i > 0) && (acima != -1)) {
						etiqueta(maze_etiquetas, i, j, i - 1, j, &count_etiquetas);
						if (equivalencias[count_etiquetas] == 0)
							equivalencias[count_etiquetas] = count_etiquetas;
					}
					if ((j > 0) && (a_esquerda != -1)) {
						etiqueta(maze_etiquetas, i, j, i, j - 1, &count_etiquetas);
						if (equivalencias[count_etiquetas] == 0)
							equivalencias[count_etiquetas] = count_etiquetas;

					}

					if ((i > 0) && (acima != -1) && (j > 0) && (a_esquerda != -1) && (maze_etiquetas[i][j-1] != maze_etiquetas[i-1][j])) {
						if (maze_etiquetas[i][j - 1] < maze_etiquetas[i - 1][j])
							equivalencias[maze_etiquetas[i - 1][j]] = equivalencias[maze_etiquetas[i][j - 1]];
						else
							equivalencias[maze_etiquetas[i][j - 1]] = equivalencias[maze_etiquetas[i - 1][j]];
					}
					if (((i == 0) || (acima == -1)) && ((j == 0) || (a_esquerda == -1))) {
						if (maze_etiquetas[i][j] == 0) {
							count_etiquetas++;
							maze_etiquetas[i][j] = count_etiquetas;
							equivalencias[count_etiquetas] = count_etiquetas;
						}
					}
				}
			}
		}

		for (i = 0;i < max_linhas;i++) {
			for (j = 0;j < max_colunas;j++) {
				if (maze_etiquetas[i][j] != -1)
					maze_etiquetas[i][j] = equivalencias[maze_etiquetas[i][j]];
			}
		}

		i = (maze_etiquetas[linha - 1][coluna - 1] == maze_etiquetas[q_x - 1][q_y - 1]);
	}
	else 
		i = 0;
	
	libertar_maze(maze_etiquetas,max_linhas,max_colunas);

	free(equivalencias);

	return i;
}


/******************************************************************************
* etiqueta()
*
* Argumentos:	maze_etiquetas - 
*			p_x - 
*			p_y - 
*			q_x - 
*			q_y - 
*			etiqueta - 
* Retorno:	(void)
* Side-Effects: none
*
* Descrição:
*	...
*****************************************************************************/
void etiqueta(int** maze_etiquetas,int p_x,int p_y, int q_x, int q_y,int* etiqueta){		

	int origem=maze_etiquetas[q_x][q_y];
	if(origem==0){
		(*etiqueta)++;
		maze_etiquetas[q_x][q_y]=(*etiqueta);	
	}
	maze_etiquetas[p_x][p_y]=maze_etiquetas[q_x][q_y];	
}	
	      	
/******************************************************************************
* criar_maze()
*
* Argumentos:	max_linhas - número máximo de linhas do labirinto
*				max_colunas - número máximo de colunas do labirinto
*
* Retorno: (int**) -> maze
* Side-Effects: none
*
* Descrição: 
*	Aloca o espaço para o labirinto.
*****************************************************************************/
int** criar_maze(int max_linhas, int max_colunas) {

	int i = 0;

	/*Alocacao da matriz*/
	int** maze = (int**)calloc(max_linhas, sizeof(int*));
	if (maze == NULL) {
		exit(0);
	}

	for (i = 0;i < max_linhas;i++) {
		maze[i] = (int*)calloc(max_colunas, sizeof(int));
		if (maze[i] == NULL) {
			exit(0);
		}
	}

	return maze;
}
    
/******************************************************************************
* libertar_maze()
*
* Argumentos:	maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				max_linhas - número máximo de linahs do labirinto
*				max_colunas - número máximo de colunas do labirinto
*
* Retorno:	(void)
* Side-Effects: none
*
* Descrição:	
*	Liberta o espaço alocado para o labirinto
*****************************************************************************/
void libertar_maze(int** maze,int max_linhas, int max_colunas) {

	int i = 0;
	
	/*libertar cada linha da matriz*/
	for (i = 0;i < max_linhas;i++)
		if (maze[i]!=NULL)
			free(maze[i]);
	if (maze!=NULL)
		free(maze);
}
     
   
 