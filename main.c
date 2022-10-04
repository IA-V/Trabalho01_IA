#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "agente_reativo_simples.h"
#include "agente_reativo_modelos.h"
#include "agente_objetivos.h"
#include "agente_utilidade.h"
#include "item.h"
#include "ambiente.h"

int main()
{
    int escolha;
    time_t t;
    srand((unsigned) time(&t));

    printf("Escolha o tipo de agente:\n1 - Reativo simples\n2 - Reativo baseado em modelos\n3 - Agente com objetivos\n4 - Agente baseado em utilidade\n");
    scanf("%d", &escolha);

    inicializar_ambiente(ambiente_virtual);
    inicializar_ambiente(ambiente);

    ambiente_virtual[0][0] = 'A'; // "A" representa o agente dentro do ambiente

    adiciona_itens_ambiente(ambiente);

    clock_t begin = 0;
    clock_t end = 0;

    switch(escolha)
    {
        case 1:
            begin = clock();
            iniciarRS();
            end = clock();
            break;
        case 2:
            begin = clock();
            iniciarRM();
            end = clock();
            break;
        case 3:
            begin = clock();
            iniciarBO();
            end = clock();
            break;
        case 4:
            begin = clock();
            iniciarAU();
            end = clock();
            break;
    }

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo de execucao = %.2lfs\n", time_spent);

    return 0;
}
