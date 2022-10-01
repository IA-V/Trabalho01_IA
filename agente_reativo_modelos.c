#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "agente_reativo_modelos.h"

typedef struct _ponto_
{
    int x;
    int y;
} Ponto;

typedef struct _reativo_modelos_
{
    int acao_anterior;
    Ponto *historico;
    Item *item;
} Reativo_Modelos;


Reativo_Modelos agente;
int pts = 0;

void iniciarRM()
{
    agente.item = (Item*)malloc(sizeof(Item));
    agente.item->tipoItem = SEM_ITEM;
    agente.acao_anterior = INICIAR;

    agente.historico = (Ponto*)malloc(sizeof(Ponto));
    agente.historico->x = 0;
    agente.historico->y = 0;

    int *pos_atual;
    int acao;

    do {
        pos_atual = sensorRM(ambiente_virtual, TAMANHO_AMBIENTE, TAMANHO_AMBIENTE);
        acao = funcaoAgenteRM(pos_atual, ambiente);
        atuadorRM(acao, ambiente, ambiente_virtual, pos_atual);
        exibir_ambiente(ambiente, ambiente_virtual, TAMANHO_AMBIENTE, TAMANHO_AMBIENTE);
    }while(pts < 150);

    printf("pts = %d\n", pts);

    free(pos_atual);
}

int *sensorRM(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas)
{
    int *pos_atual = (int *)malloc(2*sizeof(int)); // Armazena a linha e a coluna atual (respectivamente) do agente no ambiente

    for(int i = 0; i < TAMANHO_AMBIENTE; i++)
    {
        for(int j = 0; j < TAMANHO_AMBIENTE; j++)
        {
            if(ambiente[i][j] == 'A')
            {
                pos_atual[0] = i;
                pos_atual[1] = j;

                break;
            }
        }
    }
    return pos_atual;
}

int funcaoAgenteRM(int *pos, int ambiente[][TAMANHO_AMBIENTE])
{
    // Acao com base na pos
    int linha_atual = pos[0];
    int coluna_atual = pos[1];

    int acao;

    if(agente.item->tipoItem == SEM_ITEM)
    {
        switch(ambiente[linha_atual][coluna_atual])
        {
            case TIPO1:
            case TIPO2:
                acao = PEGAR;
                break;
            case SEM_ITEM:
                switch(agente.acao_anterior)
                {
                    case SOLTAR: // Movimentacao de retorno ao ponto anterior
                        if(coluna_atual < agente.historico->x)
                        {
                            acao = DIREITA;
                        } else if(linha_atual < agente.historico->y) {
                            acao = BAIXO;
                        } else {
                            agente.acao_anterior = INICIAR;
                        }
                        break;
                    default: // Movimentacao padrao
                        if(linha_atual % 2 == 0 && coluna_atual < TAMANHO_AMBIENTE-1)
                        {
                            acao = DIREITA;
                        } else if(linha_atual % 2 != 0 && coluna_atual > 0) {
                            acao = ESQUERDA;
                        } else if((linha_atual % 2 == 0 && coluna_atual == TAMANHO_AMBIENTE-1) || (linha_atual % 2 != 0 && coluna_atual == 0)) {
                            acao = BAIXO;
                        }
                }

                break;
        }

    } else { // Movimentacao de retorno ao ponto inicial
        if(linha_atual > 0)
        {
            acao = CIMA;
        } else if(coluna_atual > 0) {
            acao = ESQUERDA;
        } else {
            acao = SOLTAR;
        }
    }

    return acao;
}

int atuadorRM(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual)
{
    int linha_atual = pos_atual[0];
    int coluna_atual = pos_atual[1];

    int confirmacao = 1;
    switch(acao)
    {
        case CIMA:
            ambiente_virtual[linha_atual-1][coluna_atual] = 'A';
            ambiente_virtual[linha_atual][coluna_atual] = 0;
            break;
        case BAIXO:
            ambiente_virtual[linha_atual+1][coluna_atual] = 'A';
            ambiente_virtual[linha_atual][coluna_atual] = 0;
            break;
        case DIREITA:
            ambiente_virtual[linha_atual][coluna_atual+1] = 'A';
            ambiente_virtual[linha_atual][coluna_atual] = 0;
            break;
        case ESQUERDA:
            ambiente_virtual[linha_atual][coluna_atual-1] = 'A';
            ambiente_virtual[linha_atual][coluna_atual] = 0;
            break;
        case PEGAR:
            agente.item->tipoItem = ambiente[linha_atual][coluna_atual];
            agente.historico->y = linha_atual;
            agente.historico->x = coluna_atual;
            ambiente[linha_atual][coluna_atual] = SEM_ITEM;
            break;
        case SOLTAR:
            pts += agente.item->tipoItem;
            agente.item->tipoItem = SEM_ITEM;
            agente.acao_anterior = SOLTAR;
            break;
        case INICIAR:
        case PARAR:
            break;
        default:
            printf("Case default.\n");
            confirmacao = 0;
            break;
    }
    return confirmacao;
}
