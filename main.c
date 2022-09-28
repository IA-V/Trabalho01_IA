#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "agente_reativo_simples.h"
#include "item.h"

int main()
{
    time_t t;

    int linha, coluna;
    srand((unsigned) time(&t));

    int ambiente[20][20];

    for(int i = 0; i < 10; i++) // inicializacao do ambiente
    {
        linha = rand() % 20;
        coluna = rand() % 20;

        while(linha == 0 && coluna == 0) {
            linha = rand() % 20;
            coluna = rand() % 20;
        }

        if(i % 2 == 0) {
            ambiente[linha][coluna] = TIPO1;
        } else {
            ambiente[linha][coluna] = TIPO2;
        }
    }

    //
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(ambiente[i][j] == TIPO1)
            {
                printf("1");
            } else if(ambiente[i][j] == TIPO2){
                printf("2");
            } else {
                printf("*");
            }

        }
        printf("\n");
    }
    return 0;
}
