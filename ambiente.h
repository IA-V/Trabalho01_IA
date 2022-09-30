#ifndef _AMBIENTE_
#define _AMBIENTE_

#define TAMANHO_AMBIENTE 20

int ambiente[TAMANHO_AMBIENTE][TAMANHO_AMBIENTE];
int ambiente_virtual[TAMANHO_AMBIENTE][TAMANHO_AMBIENTE];

void inicializar_ambiente(int ambiente[][TAMANHO_AMBIENTE]);
void exibir_ambiente(int ambiente[][TAMANHO_AMBIENTE], int ambiente_virtual[][TAMANHO_AMBIENTE], int linhas, int colunas);
void adiciona_itens_ambiente(int ambiente[][TAMANHO_AMBIENTE]);

#endif
