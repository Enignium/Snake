#include "classifica.h"
#include "griglia.h"
#include "snake.h"
//funzioni gioco

void istruzioni(){
    printf("\e[1;1H\e[2J");
        printf("\n\n");
    printf("\033[1;33m");
    printf("      _____ _____ _____ _____ _____\n");
    printf("     |   __|   | |  _  |  |  |   __|\n");
    printf("     |__   | | | |     |    -|   __|\n");
    printf("     |_____|_|___|__|__|__|__|_____|\n");
    printf("\033[0m");
    printf("\n\n     \e[1;37m'\e[0;37m\e[1;31mW\e[0;37m\e[1;37m'\e[0;37m \e[1;37mper muoverti in alto\e[0;37m\n     \e[1;37m'\e[0;37m\e[1;31mA\e[0;37m\e[1;37m'\e[0;37m \e[1;37mper muoverti a sinistra\e[0;37m\n     \e[1;37m'\e[0;37m\e[1;31mS\e[0;37m\e[1;37m'\e[0;37m \e[1;37mper muoverti in basso\e[0;37m\n     \e[1;37m'\e[0;37m\e[1;31mD\e[0;37m\e[1;37m'\e[0;37m \e[1;37mper muoverti a destra\e[0;37m\n\n\n \e[1;37mPrendendo il\e[0;37m \e[1;31mcibo\e[0;37m \e[1;37mcresci, crescendo aumenta la\e[0;37m \e[1;31mvelocità\e[0;37m\e[1;37m.\e[0;37m\n");
    while ( getchar() != '\n' );
    getchar();
}


void freemap(nodo1 head){
   struct nodo2* colonne=head->lista;
   struct nodo1* i;
   struct nodo2* j;
    while(head!=NULL){
        while(colonne!=NULL){
            j=colonne;
            colonne=colonne->next;
            free(j);
        }
        i=head;
        head=head->next;
        if(head!=NULL)
            colonne=head->lista;
        free(i);
    }
}

void freesnake(snake serpente){
    struct pallino* testa=serpente->head;
    struct pallino* i;
    while (serpente->head!=NULL){
        i=serpente->head;
        serpente->head=serpente->head->next;
        free(i);
    }
    if (serpente->head==NULL) free(serpente->head);
    free(serpente);
}

int gioco(FILE* punti, classifica *punteggi){
    system("clear");
    srand(time(NULL));
    char nome[15];
    nodo1 mappa=NULL;
    creamatrice(&mappa, 11, 13);
    creamappa(mappa);
    snake serpente=NULL;
    creasnake(&serpente);
    spawnsnake(mappa, serpente, 7,3);
        printf("\n\n");
    printf("\033[1;33m");
    printf("      _____ _____ _____ _____ _____\n");
    printf("     |   __|   | |  _  |  |  |   __|\n");
    printf("     |__   | | | |     |    -|   __|\n");
    printf("     |_____|_|___|__|__|__|__|_____|\n");
    printf("\033[0m");
    stampa(mappa);
    playermove(mappa, serpente);
    printf("\n\t        \e[1;31mSEI MORTO\n\e[0;37m\n \e[1;37mInserisci il tuo nome per tornare al menu\e[0;37m\n");
    scanf("%s",nome);
    salvasulfile(punti,contanodi(serpente),nome);
    insclassifica(punteggi,contanodi(serpente),nome);
    freemap(mappa);
    freesnake(serpente);
   
    system("clear");
    return 0;
}

void menu(){
    FILE* punti=creafile();
    classifica punteggi=NULL;
    leggidafile(punti,&punteggi);
    int scelta=0;
    while(scelta!=4){
        system("clear");
            printf("\n\n");
    printf("\033[1;33m");
    printf("      _____ _____ _____ _____ _____\n");
    printf("     |   __|   | |  _  |  |  |   __|\n");
    printf("     |__   | | | |     |    -|   __|\n");
    printf("     |_____|_|___|__|__|__|__|_____|\n");
    printf("\033[0m");
        printf("\n\n\n\t\t 1. \e[1;37mGioca\e[0;37m \n\t\t 2. \e[1;37mClassifica\e[0;37m\n\t\t 3. \e[1;37mComandi\e[0;37m\n\t\t 4. \e[1;37mEsci\e[0;37m\n");
        scanf("%d", &scelta);
        switch(scelta){
            case 1: gioco(punti, &punteggi); break;
            case 2: stampaclass(punteggi); break;
            case 3: istruzioni(); break;
            case 4: break;
        }
    }
}

int main()
{
    menu();
}













