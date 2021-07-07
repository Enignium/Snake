struct posizione{
    int punteggio;
    char nome[15];
    struct posizione* next;
    struct posizione* prec;
};

typedef struct posizione* classifica;

int insclassifica(classifica *head, int punteggio, char nome[15]){
    classifica nuovogiocatore=(classifica)malloc(sizeof(struct posizione));
    nuovogiocatore->punteggio=punteggio;
    strcpy(nuovogiocatore->nome, nome);
    classifica p=*head;
    if (*head==NULL){
        nuovogiocatore->next=NULL;
        nuovogiocatore->prec=NULL;
        *head=nuovogiocatore;
        return 1;
    }
    while (p->next!=NULL && nuovogiocatore->punteggio<=p->punteggio)
        p=p->next;
    if(p==*head && nuovogiocatore->punteggio>=punteggio){
        nuovogiocatore->next=p;
        p->prec=nuovogiocatore;
        nuovogiocatore->prec=NULL;
        *head=nuovogiocatore;
        return 0;
    }
    if(p==*head && nuovogiocatore->punteggio<=p->punteggio){
        p->next=nuovogiocatore;
        nuovogiocatore->prec=p;
        nuovogiocatore->next=NULL;
        return 0;
    }
    if(p->next==NULL && nuovogiocatore->punteggio<=p->punteggio){
    nuovogiocatore->next=NULL;
    nuovogiocatore->prec=p;
    p->next=nuovogiocatore;
    return 0;
    }
    nuovogiocatore->next=p;
    nuovogiocatore->prec=p->prec;
    p->prec->next=nuovogiocatore;
    p->prec=nuovogiocatore;
}

FILE* creafile(){
    FILE* classifica=fopen("punteggi", "a+");
    return classifica;
}

void salvasulfile(FILE* classifica, int punteggio, char nome[20]){
    fprintf(classifica, "%s %d\n", nome, punteggio);
}

void leggidafile(FILE* file, classifica* punteggi){
    int punti;
    char nome[15];
    int vuoto=0;
    fseek(file, 0, SEEK_END); // goto end of file
    if (ftell(file) == 0)
    {
        vuoto=1; //1 sta per vuoto
    }
    fseek(file, 0, SEEK_SET); //siamo all'inizio
    if(vuoto!=1){
        while(!feof(file)){
            fscanf(file,"%s %d\n",nome,&punti);
            insclassifica(punteggi,punti,nome);
        }
    }
}

void stampaclass(classifica head){
    int i=1;
    printf("\e[1;1H\e[2J");
    printf("\033[1;33m");
    printf("\n\n         ________                _ _____            ");
    printf("\n        / ____/ /___ ___________(_) __(_)________ _ ");
    printf("\n       / /   / / __ `/ ___/ ___/ / /_/ / ___/ __ `/ ");
    printf("\n      / /___/ / /_/ (__  |__  ) / __/ / /__/ /_/ /  ");
    printf("\n      \\____/_/\\__,_/____/____/_/_/ /_/\\___/\\__,_/   \n\n\n\n\n");
    printf("\033[1;37m");
    if(head==NULL){
        printf("\e[1;37mLa classifica è vuota\e[0;37m");
    }
    while(head!=NULL){
    printf("\t\e[1;37m(%d).  %s ha totalizzato %d punti\e[0;37m\n",i++, head->nome, head->punteggio);
    head=head->next;
    }
    while ( getchar() != '\n' );
    getchar();
    
}
