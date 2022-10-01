#ifndef _AGENTE_OBJETIVOS_H_
#define _AGENTE_OBJETIVOS_H_

#include "item.h"
#include "acoes.h"
#include "ambiente.h"

// ESTADOS DO AGENTE
#define RECON -1
#define COLETAR -2
#define CASA -3

typedef struct _ponto_ Ponto;
typedef struct _agente_objetivos_ Agente_Objetivos;

void iniciarBO(); // aloca memoria para o agente e executa suas funcoes
int *sensorBO(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas); // recebe a matriz do ambiente e retorna vetor de 2 pos.: uma com a linha atual e outra com a coluna atual
int reconhecer(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual); // varre o ambiente para obter a localizacao dos itens
int coletar(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual); // faz a coleta dos itens com base nas localizacoes obtidas
void realocar_mem();
void alocar_mem();
int funcaoAgenteBO(int *pos, int ambiente[][TAMANHO_AMBIENTE]); // recebe um vetor com as coordenadas atuais e retorna um inteiro que representa a acao a ser tomada a seguir
int atuadorBO(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual); // recebe um inteiro que representa a acao a ser tomada e retorna a confirmacao (ou nao) da realizacao

#endif
