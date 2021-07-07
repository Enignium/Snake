#ifndef CLASSIFICA_H
#define CLASSIFICA_H

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

struct posizione{
    int punteggio;
    char nome[15];
    struct posizione* next;
    struct posizione* prec;
};

typedef struct posizione* classifica;

int insclassifica(classifica *head, int punteggio, char nome[15]);

FILE* creafile();

void salvasulfile(FILE* classifica, int punteggio, char nome[20]);

void leggidafile(FILE* file, classifica* punteggi);

void stampaclass(classifica head);

#endif