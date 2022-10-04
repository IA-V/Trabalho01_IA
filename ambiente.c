#include "ambiente.h"
#include "item.h"

void inicializar_ambiente(int ambiente[][TAMANHO_AMBIENTE])
{
    for(int i = 0; i < TAMANHO_AMBIENTE; i++)
    {
        for(int j = 0; j < TAMANHO_AMBIENTE; j++)
        {
            ambiente[i][j] = 0;
        }
    }
}

void exibir_ambiente(int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int linhas, int colunas)
{
    system("cls");
    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(ambiente[i][j] == TIPO1)
            {
                printf("1");
            } else if(ambiente[i][j] == TIPO2){
                printf("2");
            } else if(ambiente_virtual[i][j] == 'A') {
                printf("A");
            } else {
                printf("*");
            }

        }
        printf("\n");
    }
}

void adiciona_itens_ambiente(int ambiente[][TAMANHO_AMBIENTE])
{
    int linha;
    int coluna;

    for(int i = 0; i < 10; i++)
    {
        linha = rand() % TAMANHO_AMBIENTE;
        coluna = rand() % TAMANHO_AMBIENTE;

        while((linha == 0 && coluna == 0) || ambiente[linha][coluna] != 0) {
            linha = rand() % TAMANHO_AMBIENTE;
            coluna = rand() % TAMANHO_AMBIENTE;
        }

        if(i % 2 == 0) {
            ambiente[linha][coluna] = TIPO1;
        } else {
            ambiente[linha][coluna] = TIPO2;
        }
    }
}
