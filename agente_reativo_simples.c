#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "agente_reativo_simples.h"

int *sensor(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas)
{
    int *pos_atual = malloc(2*sizeof(int*)); // Armazena a linha e a coluna atual (respectivamente) do agente no ambiente

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(ambiente[i][j] == 'A')
            {
                pos_atual[0] = i;
                pos_atual[1] = j;

                break;
            }
        }
    }
    // printf("%d\n", pos_atual[0]);
    return pos_atual;
}

int funcaoAgente(int *pos)
{
    // Acao com base na pos
    printf("%d\n", pos[1]);
    return 1;
}

int atuador(int acao)
{
    return 1;
}
