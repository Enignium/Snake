#ifndef SNAKE_H
#define SNAKE_H 

#include "griglia.h"
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <time.h>



struct pallino{
    nodo2 posizione;
    struct pallino* next;
    struct pallino* prec;
};

struct snake{ 
    struct pallino* head;
    struct pallino* tail;
};

typedef struct snake* snake;

int creasnake(snake *serpente);

int insincodasnake(snake serpente,nodo2 posizione);

int contanodi(snake serpente);

void spawnsnake(nodo1 mappa , snake serpente, int i, int j);

int up(nodo1 mappa, snake serpente);

int down(nodo1 mappa, snake serpente);

int right(nodo1 mappa, snake serpente);

int left(nodo1 mappa, snake serpente);

int sceglivel(int dimensioni);

void playermove(nodo1 mappa, snake serpente);

void segui(snake serpente,int cancella);

void aggiornatutto(nodo1 mappa, snake serpente);
#endif