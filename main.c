#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "agente_reativo_simples.h"
#include "agente_reativo_modelos.h"
#include "item.h"
#include "ambiente.h"

int main()
{
    time_t t;

    srand((unsigned) time(&t));

    inicializar_ambiente(ambiente_virtual);
    inicializar_ambiente(ambiente);

    ambiente_virtual[0][0] = 'A'; // "A" representa o agente dentro do ambiente

    adiciona_itens_ambiente(ambiente);

    // iniciarRS();
    iniciarRM();
    return 0;
}
