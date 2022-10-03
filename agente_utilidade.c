#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#include "agente_utilidade.h"

typedef struct _ponto_
{
    int x;
    int y;
    float pontuacao;
    struct _ponto_ *proximo;
} Ponto;

typedef struct _agente_utilidade_
{
    int estado;
    int acao_anterior;
    Ponto *historico;
    Item *item;
} Agente_Utilidade;

int tamanho_historico = 0;
int indice_fila_pontos = 0;

Agente_Utilidade agente;
Ponto *atual, *primeiro;
Ponto **fila_pontos;
int pts = 0;

void iniciarAU()
{
    agente.item = (Item*)malloc(sizeof(Item));
    agente.item->tipoItem = SEM_ITEM;
    agente.acao_anterior = INICIAR;

    agente.historico = (Ponto*)malloc(sizeof(Ponto));
    primeiro = agente.historico;
    agente.historico->proximo = NULL;

    agente.estado = RECON;

    int *pos_atual;
    int acao;

    do {
        pos_atual = sensorAU(ambiente_virtual, TAMANHO_AMBIENTE, TAMANHO_AMBIENTE);
        acao = funcaoAgenteAU(pos_atual, ambiente);
        atuadorAU(acao, ambiente, ambiente_virtual, pos_atual);
        exibir_ambiente(ambiente, ambiente_virtual, TAMANHO_AMBIENTE, TAMANHO_AMBIENTE);
        atual = primeiro;
        while(atual->proximo != NULL)
        {
            printf("Ponto do historico: X = %d, Y = %d, pts = %.2f\n", atual->x, atual->y, atual->pontuacao);
            atual = atual->proximo;
        }
        // printf("pts = %d\n", pts);
        /*printf("tamanho do historico = %d\n", tamanho_historico);
        printf("indice da fila = %d\n", indice_fila_pontos);*/
    }while(pts < 150);
    while(atual->proximo != NULL)
    {
        printf("Ponto do historico: X = %d, Y = %d, pts = %.2f\n", atual->x, atual->y, atual->pontuacao);
        atual = atual->proximo;
    }
    printf("pts = %d\n", pts);

    free(agente.item);
    free(agente.historico);
    free(fila_pontos);
}

int *sensorAU(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas)
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

void alocar_mem_historico()
{
    agente.historico->proximo = (Ponto*)malloc(sizeof(Ponto));

    /*Ponto *aux = agente.historico;
    while(aux != NULL)
    {
        aux = aux->proximo;
    }
    agente.historico->proximo = (Ponto*)malloc(sizeof(Ponto));
    agente.historico->proximo->proximo = NULL;*/
}

float calc_pontuacaoAU(int x, int y, int tipo_item)
{
    float dist_pontos = sqrt(pow(x-0, 2) + pow(y-0, 2));
    float pontuacao = tipo_item / dist_pontos;

    return pontuacao;
}

void select_sort_pontos()
{
   for(int i = 0; i < tamanho_historico-1; i++) {
      int maior = i;
      for(int j = i + 1; j < tamanho_historico; j++) {
         if (fila_pontos[j]->pontuacao > fila_pontos[maior]->pontuacao) maior = j;
      }
      Ponto *aux = fila_pontos[i];
      fila_pontos[i] = fila_pontos[maior];
      fila_pontos[maior] = aux;
   }
}

void vetorizarAU(Ponto *primeiro_ponto) // Cria um vetor de mesmo tamanho que o historico com os pontos descobertos (sem ser lista encadeada)
{
    Ponto *ponto_atual = primeiro_ponto;
    fila_pontos = (Ponto **)malloc(tamanho_historico * sizeof(Ponto *));

    int indice = 0;

    while(ponto_atual->proximo != NULL)
    {
        fila_pontos[indice] = ponto_atual;
        ponto_atual = ponto_atual->proximo;
        indice++;
    }
}

int reconhecerAU(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual)
{
    int acao;
    int indice = 0;
    switch(ambiente[linha_atual][coluna_atual])
    {
        case TIPO1:
        case TIPO2:
            agente.historico->x = coluna_atual;
            agente.historico->y = linha_atual;
            agente.historico->pontuacao = calc_pontuacaoAU(coluna_atual, linha_atual, ambiente[linha_atual][coluna_atual]);
            if(agente.historico->proximo == NULL)
            {
                alocar_mem_historico();
            }
            agente.historico = agente.historico->proximo;
            agente.historico->proximo = NULL;
            tamanho_historico++;
        case SEM_ITEM: // Movimentacao padrao
            if(linha_atual % 2 == 0 && coluna_atual < TAMANHO_AMBIENTE-1)
            {
                acao = DIREITA;
            } else if(linha_atual % 2 != 0 && coluna_atual > 0) {
                acao = ESQUERDA;
            } else if(linha_atual == 19 && coluna_atual == 0){
                vetorizarAU(primeiro);
                select_sort_pontos();
                agente.estado = CASA;
                acao = CIMA;
            } else if((linha_atual % 2 == 0 && coluna_atual == TAMANHO_AMBIENTE-1) || (linha_atual % 2 != 0 && coluna_atual == 0)) {
                acao = BAIXO;
            }
            break;
    }

    return acao;
}

int coletarAU(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual)
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
                if(coluna_atual < fila_pontos[indice_fila_pontos]->x)
                {
                    acao = DIREITA;
                } else if(linha_atual < fila_pontos[indice_fila_pontos]->y)
                {
                    acao = BAIXO;
                } else {
                    acao = SOLTAR;
                    printf("AGENTE -> X = %d, Y = %d\n", fila_pontos[indice_fila_pontos]->x, fila_pontos[indice_fila_pontos]->y);
                    while(primeiro->proximo != NULL)
                    {
                        printf("Ponto do historico: X = %d, Y = %d, pts = %.2f\n", primeiro->x, primeiro->y, primeiro->pontuacao);
                        primeiro = primeiro->proximo;
                    }
                    printf("\n");
                    /*for(int i = 0; i < tamanho_historico; i++)
                    {
                        printf("Ponto %d: X = %d, Y = %d, pts = %.2f\n", i, fila_pontos[i]->x, fila_pontos[i]->y, fila_pontos[i]->pontuacao);
                    }*/
                    system("pause");
                    // pts = 150;
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

int funcaoAgenteAU(int *pos, int ambiente[][TAMANHO_AMBIENTE])
{
    // Acao com base na pos
    int linha_atual = pos[0];
    int coluna_atual = pos[1];

    int acao;

    switch(agente.estado)
    {
        case RECON:
            acao = reconhecerAU(ambiente, linha_atual, coluna_atual);
            break;
        case COLETAR:
            acao = coletarAU(ambiente, linha_atual, coluna_atual);
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
                indice_fila_pontos = 0;
            }
            break;
    }

    return acao;
}

int atuadorAU(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual)
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
            fila_pontos[indice_fila_pontos]->y = linha_atual;
            fila_pontos[indice_fila_pontos]->x = coluna_atual;
            ambiente[linha_atual][coluna_atual] = SEM_ITEM;
            indice_fila_pontos++;
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
