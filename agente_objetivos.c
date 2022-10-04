#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "agente_objetivos.h"

typedef struct _ponto_
{
    int x;
    int y;
    struct _ponto_ *proximo;
} Ponto;

typedef struct _agente_objetivos_
{
    int estado;
    int acao_anterior;
    Ponto *historico;
    Item *item;
} Agente_Objetivos;

Agente_Objetivos agente;
Ponto *atual, *primeiro;
int pts;

void iniciarBO()
{
    agente.item = (Item*)malloc(sizeof(Item));
    agente.item->tipoItem = SEM_ITEM;
    agente.acao_anterior = INICIAR;

    agente.historico = (Ponto*)malloc(sizeof(Ponto));
    // agente.historico[0] = (Ponto*)malloc(sizeof(Ponto));
    primeiro = agente.historico;
    atual = agente.historico;
    agente.historico->proximo = NULL;
    /*agente.historico[0]->x = 0;
    agente.historico[0]->y = 0;*/

    // printf("%d\n", agente.historico[0]->x);

    agente.estado = RECON;
    // (Ponto*)realloc(historico, (sizeof(historico)/sizeof(historico[0]) + 1) * sizeof(Ponto))
    // printf("%d\n", sizeof(agente.historico)/sizeof(agente.historico[0]));

    int *pos_atual;
    int acao;

    do {
        pos_atual = sensorBO(ambiente_virtual, TAMANHO_AMBIENTE, TAMANHO_AMBIENTE);
        acao = funcaoAgenteBO(pos_atual, ambiente);
        atuadorBO(acao, ambiente, ambiente_virtual, pos_atual);
        exibir_ambiente(ambiente, ambiente_virtual, TAMANHO_AMBIENTE, TAMANHO_AMBIENTE);
        // printar_historico();
    }while(pts < 150);

    // printar_historico();
    printf("pts = %d\n", pts);

    // free(pos_atual);
}

void printar_historico()
{
    Ponto *aux = primeiro;
    int i = 1;
    printf("\tHISTORICO DE ITENS:\n");
    while(aux != NULL)
    {
        printf("Ponto %d: X = %d, Y = %d\n", i, aux->x, aux->y);
        aux = aux->proximo;
        i++;
    }
}

int *sensorBO(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas)
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

void alocar_mem()
{
    agente.historico->proximo = (Ponto*)malloc(sizeof(Ponto));
}

int reconhecer(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual)
{
    int acao;
    int indice = 0;
    switch(ambiente[linha_atual][coluna_atual])
    {
        case TIPO1:
        case TIPO2:
            agente.historico->x = coluna_atual;
            agente.historico->y = linha_atual;
            if(agente.historico->proximo == NULL)
            {
                alocar_mem();
            }
            agente.historico = agente.historico->proximo;
            agente.historico->proximo = NULL;
        case SEM_ITEM: // Movimentacao padrao
            if(linha_atual % 2 == 0 && coluna_atual < TAMANHO_AMBIENTE-1)
            {
                acao = DIREITA;
            } else if(linha_atual % 2 != 0 && coluna_atual > 0) {
                acao = ESQUERDA;
            } else if(linha_atual == 19 && coluna_atual == 0){
                agente.estado = CASA;
                acao = CIMA;
            } else if((linha_atual % 2 == 0 && coluna_atual == TAMANHO_AMBIENTE-1) || (linha_atual % 2 != 0 && coluna_atual == 0)) {
                acao = BAIXO;
            }
            break;
    }

    return acao;
}

int coletar(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual)
{
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
                if(coluna_atual < atual->x)
                {
                    acao = DIREITA;
                } else if(linha_atual < atual->y)
                {
                    acao = BAIXO;
                } else {
                    acao = PEGAR;
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

int funcaoAgenteBO(int *pos, int ambiente[][TAMANHO_AMBIENTE])
{
    // Acao com base na pos
    int linha_atual = pos[0];
    int coluna_atual = pos[1];

    int acao;

    switch(agente.estado)
    {
        case RECON:
            acao = reconhecer(ambiente, linha_atual, coluna_atual);
            break;
        case COLETAR:
            acao = coletar(ambiente, linha_atual, coluna_atual);
            break;
        case CASA:
            if(linha_atual > 0)
            {
                acao = CIMA;
            } else if(coluna_atual > 0) {
                acao = ESQUERDA;
            } else {
                acao = INICIAR;
                agente.estado = COLETAR;
                atual = primeiro;
            }
            break;
    }

    return acao;
}

int atuadorBO(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual)
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
            /*atual->y = linha_atual;
            atual->x = coluna_atual;*/
            atual = atual->proximo;
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
            printf("Acao == %d\n", acao);
            confirmacao = 0;
            break;
    }
    return confirmacao;
}
