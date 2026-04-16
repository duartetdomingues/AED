/******************************************************************************
 * (c) 2021 Adriana Mooney e Matilde Neves
 * Última modificação: nov 2021-11-
 *
 * NOME
 *   funcoes_a.h
 *
 * DESCRIÇÃO
 *   Declaração das funções "a", e auxiliares às mesmas.
 *
 * COMENTÁRIOS
 *
 ******************************************************************************/
#ifndef _FUNCOESA_H
#define _FUNCOESA_H


/******************************************************************************
* a1()
*
* Argumentos:   maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*               coluna - número da coluna da célula atual a analisar
*               celulas_nbrancas - número de células não brancas
* Retorno:  (int) - -1->célulapreta,0->célulabranca,1->célulacinzenta
* Side-Effects: none
*
* Descrição:
*   Identifica o tipo de célula (preta,branca, ou cinzenta)
*****************************************************************************/
int a1(int** maze, int linha, int coluna,int celulas_nbrancas);


/******************************************************************************
* a2()
*
* Argumentos:   maze - ponteiro para vetor que guarda o labirinto do ficheiro
*			    linha - número da linha da célula atual a analisar
*               coluna - número da coluna da célula atual a analisar
*               celulas_nbrancas - número de células não brancas
* Retorno:  (int) - 1->TRUE, 0->FALSE
* Side-Effects: none
*
* Descrição:
*   Indica se existe algum vizinho que seja célula branca
*****************************************************************************/
int a2(int** maze, int linha, int coluna, int max_linhas, int max_colunas,int celulas_nbrancas);


/******************************************************************************
* a3()
*
* Argumentos:   maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*               coluna - número da coluna da célula atual a analisar
*               celulas_nbrancas - número de células não brancas
* Retorno:  (int) - 1->TRUE,0->FALSE
* Side-Effects: none
*
* Descrição:
*   Indica se existe algum vizinho que seja célula cinzenta
*****************************************************************************/
int a3(int** maze, int linha, int coluna, int max_linhas, int max_colunas,int celulas_nbrancas);



/******************************************************************************
* a4()
*
* Argumentos:   maze - ponteiro para vetor que guarda o labirinto do ficheiro
*				linha - número da linha da célula atual a analisar
*               coluna - número da coluna da célula atual a analisar
*               células_nbrancas - número de células não brancas
* Retorno:  (int) - 1->TRUE,0->FALSE
* Side-Effects: none
*
* Descrição:
*   Indica se existe algum vizinho que seja célula preta
*****************************************************************************/
int a4(int** maze, int linha, int coluna, int max_linhas, int max_colunas,int celulas_nbrancas);


/******************************************************************************
* a5()
*
* Argumentos:   maze - ponteiro para vetor que guarda o labirinto do ficheiro
*			    linha - número da linha da célula atual a analisar
*               coluna - número da coluna da célula atual a analisar
*               celulas_nbrancas - número de células não brancas
* Retorno: (int) - 1->TRUE,0->FALSE
* Side-Effects: none
*
* Descrição:
*   Indica se for célula cinzenta, se pode ser quebrada.
*****************************************************************************/
int a5(int** maze, int linha, int coluna, int max_linhas, int max_colunas,int celulas_nbrancas);


/******************************************************************************
* a6()
*
* Argumentos:   maze - ponteiro para vetor que guarda o labirinto do ficheiro
*			    linha - número da linha da célula atual a analisar
*               coluna - número da coluna da célula atual a analisar
*               max_linhas - número máximo de linhas do labrinto
*               max_colunas - número máximo de colunas do labirinto
* Retorno:
* Side-Effects: none
*
* Descrição:
*	Indica ,se as células forem brancas, se pertencem à mesma sala
*****************************************************************************/
int a6(int** maze, int linha, int coluna, int max_linhas, int max_colunas,int q_x, int q_y,int celulas_nbrancas);


/******************************************************************************
* etiqueta()
*
* Argumentos:  maze_etiquetas -
*              p_x -
*              p_y -
*              q_x -
*              q_y -
*              etiqueta -
* Retorno: (void)
* Side-Effects: none
*
* Descrição:
*	...
*****************************************************************************/
void etiqueta(int** maze_etiquetas, int p_x, int p_y, int q_x, int q_y, int* etiqueta);


/******************************************************************************
* criar_maze()
*
* Argumentos:   max_linhas - número máximo de linhas do labirinto
*               max_colunas - número máximo de colunas do labirinto
*
* Retorno: (int**) -> maze
* Side-Effects: none
*
* Descrição: Aloca o espaço para o labirinto.
*
*****************************************************************************/
int** criar_maze(int max_linhas, int max_colunas);


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
void libertar_maze(int** maze, int max_linhas, int max_colunas);


#endif