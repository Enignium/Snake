#ifndef GRIGLIA_H
#define GRIGLIA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct casella{                 //casella che compone la matrice
    char img;
    int i, j; //indice di riga e colonna
    
};

struct nodo1{
    struct nodo2* lista; //puntatore al primo elemento della seconda lista
    struct nodo1* next;  //puntatore alla seconda lista
    struct nodo1* prec;  //puntatore alla lista precedente
};

typedef struct nodo1* nodo1;

struct nodo2{
    struct casella casella; //puntatore al primo elemento della seconda lista
    struct nodo2* next; //puntatore al secondo nodo della lista
    struct nodo2* prec; //puntatore al nodo precedente della lista
};

typedef struct nodo2* nodo2;

int insincoda1(nodo1 *head);

int insincoda2(nodo2 *head);

void creamatrice(nodo1 *head,int i,int j);

void creamappa(nodo1 head);

nodo2 accessoij(nodo1 head, int i, int j);

void stampa(nodo1 head);

void aggiorna(nodo1 mappa);

int comparacoord(nodo2 posizionenuova, nodo2 posizionesecondo);

int check(nodo1 mappa, nodo2 posizione);

int contarighe(nodo1 mappa);

int contacolonne(nodo1 mappa);

int checkcibo(nodo1 mappa);

void spawncibo(nodo1 mappa);
