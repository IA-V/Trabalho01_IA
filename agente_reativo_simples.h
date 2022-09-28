#ifndef _AGENTE_REATIVO_SIMPLES_H_
#define _AGENTE_REATIVO_SIMPLES_H_

#include "item.h"
#include "acoes.h"

typedef struct reativo_simples
{
    Item item;
} Reativo_Simples;

int *sensor(int **ambiente); // recebe a matriz do ambiente e retorna vetor de 2 pos.: uma com a linha atual e outra com a coluna atual
int funcaoAgente(int *pos); // recebe um vetor com as coordenadas atuais e retorna um inteiro que representa a acao a ser tomada a seguir
int atuador(int acao); // recebe um inteiro que representa a acao a ser tomada e retorna a confirmacao (ou nao) da realizacao

/*typedef struct reativo_modelos
{
    Item item;
} Reativo_Modelos;

typedef struct com_objetivos
{

} Com_Objetivos;

typedef struct utilidade
{

} Utilidade;*/

//Funcoes

#endif
