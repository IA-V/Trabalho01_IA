#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "agente_reativo_simples.h"
#include "item.h"

void exibe_ambiente(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas);

int main()
{
    time_t t;

    int linha, coluna;
    int *pos_atual;
    srand((unsigned) time(&t));

    int ambiente[TAMANHO_AMBIENTE][TAMANHO_AMBIENTE];

    ambiente[0][0] = 'A'; // "A" representa o agente dentro do ambiente

    for(int i = 0; i < 10; i++) // inicializacao do ambiente
    {
        linha = rand() % TAMANHO_AMBIENTE;
        coluna = rand() % TAMANHO_AMBIENTE;

        while(linha == 0 && coluna == 0) {
            linha = rand() % TAMANHO_AMBIENTE;
            coluna = rand() % TAMANHO_AMBIENTE;
        }

        if(i % 2 == 0) {
            ambiente[linha][coluna] = TIPO1;
        } else {
            ambiente[linha][coluna] = TIPO2;
        }
    }

    int qtd_linhas = sizeof(ambiente) / sizeof(ambiente[0]);
    int qtd_colunas = sizeof(ambiente[0]) / sizeof(ambiente[0][0]);

    exibe_ambiente(ambiente, qtd_linhas, qtd_colunas);

    pos_atual = sensor(ambiente, qtd_linhas, qtd_colunas);
    printf("%d\n", pos_atual);
    funcaoAgente(pos_atual);

    free(pos_atual);
    return 0;
}

void exibe_ambiente(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas)
{
    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(ambiente[i][j] == TIPO1)
            {
                printf("1");
            } else if(ambiente[i][j] == TIPO2){
                printf("2");
            } else if(ambiente[i][j] == 'A') {
                printf("A");
            } else {
                printf("*");
            }

        }
        printf("\n");
    }
}
