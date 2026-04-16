/******************************************************************************
 * (c) 2021 Adriana Monney e Matilde Neves
 * Última modificação: nov 2021-11-
 *
 * NOME
 *   sparse.c
 *
 * DESCRIÇÃO
 *   Implementação de funções para tornar o código mais eficiente.
 *
 * COMENTÁRIOS
 *
 ******************************************************************************/


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
int get(int** matriz, int x, int y,int n_linhas) {
    int linha = 0;

    while ((linha<n_linhas)&&((matriz[linha][0]!=x)||(matriz[linha][1]!=y))) /*Guarda-se as coordenadas numa matriz e o respetivo custo.*/
        linha++;
    if (linha < n_linhas)
        return matriz[linha][2];
    else 
        return 0;
}
