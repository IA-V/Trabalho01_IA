OBJS	= agente_objetivos.o agente_reativo_modelos.o agente_reativo_simples.o agente_utilidade.o ambiente.o main.o
SOURCE	= agente_objetivos.c agente_reativo_modelos.c agente_reativo_simples.c agente_utilidade.c ambiente.c main.c
HEADER	= acoes.h agente_objetivos.h agente_reativo_modelos.h agente_reativo_simples.h agente_utilidade.h ambiente.h item.h
OUT	= agente
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

agente_objetivos.o: agente_objetivos.c
	$(CC) $(FLAGS) agente_objetivos.c 

agente_reativo_modelos.o: agente_reativo_modelos.c
	$(CC) $(FLAGS) agente_reativo_modelos.c 

agente_reativo_simples.o: agente_reativo_simples.c
	$(CC) $(FLAGS) agente_reativo_simples.c 

agente_utilidade.o: agente_utilidade.c
	$(CC) $(FLAGS) agente_utilidade.c 

ambiente.o: ambiente.c
	$(CC) $(FLAGS) ambiente.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 


clean:
	rm -f $(OBJS) $(OUT)
