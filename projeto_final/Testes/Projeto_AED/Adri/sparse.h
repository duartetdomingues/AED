/******************************************************************************
 * (c) 2021 Adriana Mooney e Matilde Neves
 * Última modificação: out 2021-10-20
 *
 * NOME
 *   sparse.h
 *
 * DESCRIÇÃO
 *   Declaração de funções para tornar o código mais eficiente.
 *
 * COMENTÁRIOS
 *
 ******************************************************************************/
#ifndef _SPARSE_H
#define _SPARSE_H

/******************************************************************************
* get()
*
* Argumentos:   matriz - ponteiro para vetor que guarda o labirinto do ficheiro
*			    x - coordenada x
*               y - coordenada y
*               n_linhas - número de linhas
*
* Retorno: (int) - o custo da célula requerida, ou 0;
* Side-Effects: none
*
* Descrição:
*   Identifica o custo de uma célula
*****************************************************************************/
int get(int** matriz, int x, int y, int n_linhas);
#endif