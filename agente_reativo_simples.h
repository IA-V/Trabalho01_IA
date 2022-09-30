#ifndef _AGENTE_REATIVO_SIMPLES_H_
#define _AGENTE_REATIVO_SIMPLES_H_

#include "item.h"
#include "acoes.h"
#include "ambiente.h"

typedef struct _reativo_simples_ Reativo_Simples;

int iniciarRS(); // aloca memoria para o agente e executa suas funcoes
int *sensorRS(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas); // recebe a matriz do ambiente e retorna vetor de 2 pos.: uma com a linha atual e outra com a coluna atual
int funcaoAgenteRS(int *pos, int ambiente[][TAMANHO_AMBIENTE]); // recebe um vetor com as coordenadas atuais e retorna um inteiro que representa a acao a ser tomada a seguir
int atuadorRS(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual); // recebe um inteiro que representa a acao a ser tomada e retorna a confirmacao (ou nao) da realizacao

#endif
