#ifndef _AGENTE_UTILIDADE_H_
#define _AGENTE_UTILIDADE_H_

#include "item.h"
#include "acoes.h"
#include "ambiente.h"

// ESTADOS DO AGENTE
#define RECON -1
#define COLETAR -2
#define CASA -3

typedef struct _ponto_ Ponto;
typedef struct _agente_utilidade_ Agente_Utilidade;

void iniciarAU(); // aloca memoria para o agente e executa suas funcoes
int *sensorAU(int ambiente[][TAMANHO_AMBIENTE], int linhas, int colunas); // recebe a matriz do ambiente e retorna vetor de 2 pos.: uma com a linha atual e outra com a coluna atual
int reconhecerAU(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual); // varre o ambiente para obter a localizacao dos itens
int coletarAU(int ambiente[][TAMANHO_AMBIENTE], int linha_atual, int coluna_atual); // faz a coleta dos itens com base nas localizacoes obtidas
void vetorizarAU(Ponto *primeiro_ponto); // AH EEEHHHH
void alocar_mem_historico();
void remover_item_fila(int linha, int coluna);
float calc_pontuacaoAU(); // pontos / distancia
int funcaoAgenteAU(int *pos, int ambiente[][TAMANHO_AMBIENTE]); // recebe um vetor com as coordenadas atuais e retorna um inteiro que representa a acao a ser tomada a seguir
int atuadorAU(int acao, int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int *pos_atual); // recebe um inteiro que representa a acao a ser tomada e retorna a confirmacao (ou nao) da realizacao

void select_sort_pontos(); // Ordena o vetor gerado por vetorizar()

#endif
