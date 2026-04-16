 /******************************************************************************
 * (c) 2021 Adriana Mooney e Matilde Neves
 * Última modificação: nov 2021-11-
 *
 * NOME
 *   main.c
 *
 * DESCRIÇÃO
 *   
 *
 * COMENTÁRIOS
 *   
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes_a.h"
#include "grafos.h"
#include "LinkedList.h"


/******************************************************************************************
* nome_output()
*
* Argumentos: nome_input, extensao_Out
* Retorna: nome do ficheiro de saída
* Side-Effects: none
*
* Descrição: Cria o nome do ficheiro de saída a partir do de entrada, alterando a extensão
*******************************************************************************************/
char* nome_output(char* nome_input, char* extensao_Out) {

    char* nome = NULL;
    int tamanho = strlen(nome_input);
    int tam_extensao_In = 0;
    int index =(int) (strrchr(nome_input, '.') - nome_input);

    if ((strcmp(&nome_input[index], ".in") != 0) && (strcmp(&nome_input[index], ".in1") != 0))
        return NULL;

    tam_extensao_In = strlen(&nome_input[index]);
    nome = (char*)malloc((tamanho + strlen(extensao_Out) - tam_extensao_In+1) * sizeof(char));
    strcpy(nome, nome_input);
    strcpy(nome + index , extensao_Out);
    
    return nome;
}

/******************************************************************************
* ajuda()
*
* Argumentos: nome_programa - nome do executável
* Retorna: (void)
* Side-Effects: none
*
* Descrição: -message function when arguments are missing-
*****************************************************************************/
void ajuda(char* nome_programa)
{
    /*printf("Help : %s [filename] [argumentos]\n", nomeProg);*/
    exit(0);
}


/******************************************************************************
* main ()
*
* Argumentos: argc - número de argumentos no terminal
*             argv - -table of pointers for string arguments-
* Retorno: tipo int
* Side-Effects: none
*
* Descrição: Programa principal
*****************************************************************************/

int main(int argc, char* argv[]) {

    FILE* ficheiro_In=NULL, * ficheiro_Out=NULL;
    char extensao_Out[] = ".sol3";
    char* nome_ficheiro_In=NULL, * nome_ficheiro_Out=NULL;
    int max_linhas = 0, max_colunas = 0;
    int linha_chegada = 0, coluna_chegada=0;
    int celulas_nbrancas = 0;
    int linha = 0, coluna = 0, tipo_celula = 0;
    int** maze=NULL;       
    char funcao[3]="";
    int linha_a6 = 1 ,coluna_a6 = 1;
    int i = 0;
    int custo = 0;
    LinkedList* caminho_mais_curto = NULL;
    LinkedList* percorre_lista = NULL;
    int* dados = NULL;

    if (argc < 2)
        ajuda(argv[0]);
    
    if (strcmp(argv[1], "-s") == 0) {
        nome_ficheiro_In = argv[2];
        nome_ficheiro_Out = nome_output(nome_ficheiro_In, extensao_Out);
        if (nome_ficheiro_Out == NULL)
            exit(0);
            /*printf("Memory allocation for nomeFicheiroOut in main");*/
    }
    else {
        
        nome_ficheiro_In = argv[1];
        strcpy(extensao_Out,".sol4");
        nome_ficheiro_Out = nome_output(nome_ficheiro_In, extensao_Out);
        if (nome_ficheiro_Out == NULL) 
            /*printf("Memory allocation for nomeFicheiroOut in main");*/
            exit(0);
            
    }
    
    /*Abrir fcheiro de entrada */
    ficheiro_In = fopen(nome_ficheiro_In, "r");
    if (ficheiro_In == NULL) {
        /*printf("ERROR cannot read input file %s\n", nome_ficheiro_In);*/
        exit(0);
    }
    
    /* Abrir ficheiro output*/
    ficheiro_Out = fopen(nome_ficheiro_Out, "w");
    free(nome_ficheiro_Out);
    if (ficheiro_Out == NULL) {
        /*printf("ERROR cannot write output file %s\n", nome_ficheiro_Out);*/
        fclose(ficheiro_In);        
        exit(0);
    }
    
    while (!feof(ficheiro_In)) {
        /* Ler ficheiro_In */
       
        while (!feof(ficheiro_In) && (fscanf(ficheiro_In, "%d %d", &max_linhas, &max_colunas) != 2));
        if (feof(ficheiro_In))
        {
            fclose(ficheiro_In);
            fclose(ficheiro_Out);
            exit(0);
        }
        if (strcmp(argv[1], "-s") == 0) {
            if (fscanf(ficheiro_In, "%d %d %2s", &linha_chegada, &coluna_chegada, funcao) != 3) {
                /*printf("ERROR cannot read input file  %s\n", nome_ficheiro_In);*/
                fclose(ficheiro_In);
                fclose(ficheiro_Out);
                exit(0);
            }
            if (strcmp(funcao, "A6") == 0) {
                if (fscanf(ficheiro_In, "%d %d", &linha_a6, &coluna_a6) != 2) {
                    /*printf("ERROR cannot read input file  %s\n", nome_ficheiro_In);*/
                    fclose(ficheiro_In);
                    fclose(ficheiro_Out);
                    exit(0);
                }
            }
        }
        else {
            if (fscanf(ficheiro_In, "%d %d", &linha_chegada, &coluna_chegada) != 2) {
                /*printf("ERROR cannot read input file  %s\n", nome_ficheiro_In);*/
                fclose(ficheiro_In);
                fclose(ficheiro_Out);
                exit(0);
            }
        }
        if (fscanf(ficheiro_In, "%d\n", &celulas_nbrancas) != 1) {
            /*printf("ERROR cannot read input file 12%s\n", nome_ficheiro_In);*/
            fclose(ficheiro_In);
            fclose(ficheiro_Out);
            exit(0);
        }
        
        if ((linha_chegada < 1) || (linha_chegada > max_linhas) || (coluna_chegada < 1) || (coluna_chegada > max_colunas)
            || (linha_a6 < 1) || (linha_a6 > max_linhas) || (coluna_a6 < 1) || (coluna_a6 > max_colunas))
        {
            if (strcmp(argv[1], "-s") == 0)
                fprintf(ficheiro_Out, "-2\n\n");
            else
                fprintf(ficheiro_Out, "-1\n\n");        /*Verificar*/
        }

        maze = criar_maze(celulas_nbrancas,3);
        for (i = 0;i < celulas_nbrancas;i++) {
            if (fscanf(ficheiro_In, "%d %d %d\n", &linha, &coluna, &tipo_celula) != 3)
                /*erro*/
                exit(0);
            maze[i][0] = linha - 1;
            maze[i][1] = coluna - 1;
            maze[i][2]= tipo_celula;
        }
        if (strcmp(argv[1], "-s")==0) {
            if (strcmp(funcao, "A1") == 0) {
                fprintf(ficheiro_Out, "%d\n", a1(maze, linha_chegada, coluna_chegada, celulas_nbrancas));
            }
            else if (strcmp(funcao, "A2") == 0) {
                fprintf(ficheiro_Out, "%d\n", a2(maze, linha_chegada, coluna_chegada, max_linhas, max_colunas, celulas_nbrancas));
            }
            else if (strcmp(funcao, "A3") == 0) {
                fprintf(ficheiro_Out, "%d\n", a3(maze, linha_chegada, coluna_chegada, max_linhas, max_colunas, celulas_nbrancas));
            }
            else if (strcmp(funcao, "A4") == 0) {
                fprintf(ficheiro_Out, "%d\n", a4(maze, linha_chegada, coluna_chegada, max_linhas, max_colunas, celulas_nbrancas));
            }
            else if (strcmp(funcao, "A5") == 0) {
                fprintf(ficheiro_Out, "%d\n", a5(maze, linha_chegada, coluna_chegada, max_linhas, max_colunas, celulas_nbrancas));
            }
            else if (strcmp(funcao, "A6") == 0) {
                fprintf(ficheiro_Out, "%d\n", a6(maze, linha_chegada, coluna_chegada, max_linhas, max_colunas, linha_a6, coluna_a6, celulas_nbrancas));
            }
        }
        else {
            /* 2º_submissão*/
            custo = Resolver_Labirinto(maze, celulas_nbrancas,max_linhas,max_colunas,&caminho_mais_curto,linha_chegada,coluna_chegada);
            /*Percorre a lista para imprimir os resultados*/
            fprintf(ficheiro_Out, "%d\n", custo);
            if (custo > 0) {
                fprintf(ficheiro_Out, "%d\n", lengthLinkedList(caminho_mais_curto));
                for (percorre_lista = caminho_mais_curto;percorre_lista != NULL;percorre_lista = getNextNodeLinkedList(percorre_lista)) {
                    dados = (int*)getItemLinkedList(percorre_lista);
                    fprintf(ficheiro_Out, "%d %d %d\n", dados[0], dados[1], dados[2]);
                }
            } 
        }
        fprintf(ficheiro_Out, "\n");
        freeLinkedList(caminho_mais_curto, &Liberta_dados);
        libertar_maze(maze,celulas_nbrancas,3);
    }


    /*Fechar ficheiros */
    if (fclose(ficheiro_In) != 0) {
        /*printf("ERROR cannot close input file %s\n", nome_ficheiro_In);*/
        exit(0);
    }

    if (fclose(ficheiro_Out) != 0) {
        /*printf("ERROR cannot close output file %s\n", nome_ficheiro_Out);*/
        exit(0);
    }

    exit(0);
}