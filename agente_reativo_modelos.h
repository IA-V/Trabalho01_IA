#ifndef _AGENTE_REATIVO_MODELOS_H_
#define _AGENTE_REATIVO_MODELOS_H_

#include "item.h"
#include "acoes.h"
#include "ambiente.h"

typedef struct _ponto_ Ponto;
typedef struct _reativo_modelos_ Reativo_Modelos;

void iniciarRM(); // aloca memoria para o agente e executa suas funcoes
int *sensorRM(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas); // recebe a matriz do ambiente e retorna vetor de 2 pos.: uma com a linha atual e outra com a coluna atual
int funcaoAgenteRM(int *pos, int ambiente[][TAMANHO_AMBIENTE]); // recebe um vetor com as coordenadas atuais e retorna um inteiro que representa a acao a ser tomada a seguir
int atuadorRM(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual); // recebe um inteiro que representa a acao a ser tomada e retorna a confirmacao (ou nao) da realizacao

#endif
