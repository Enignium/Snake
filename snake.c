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

int creasnake(snake *serpente){
    snake nuovosnake=(snake)malloc(sizeof(struct snake));
    nuovosnake->head=NULL;
    nuovosnake->tail=NULL;
    *serpente=nuovosnake;
    return 1;
}

int insincodasnake(snake serpente,nodo2 posizione){
    struct pallino* nuovocorpo=(struct pallino*)malloc(sizeof(struct pallino));
    nuovocorpo->posizione=posizione;
    nuovocorpo->posizione->casella.img='o';
    if (serpente->head==NULL){
        nuovocorpo->next=NULL;
        serpente->head=nuovocorpo;
        serpente->tail=nuovocorpo;
        return 1;
    }
    nuovocorpo->next=NULL;
    nuovocorpo->prec=serpente->tail;
    serpente->tail->next=nuovocorpo;
    serpente->tail=nuovocorpo;
    return 1;
}

int contanodi(snake serpente){
    struct pallino* p=serpente->head;
    int a=0;
    while(p!=NULL){
        a++;
        p=p->next;
    }
    return a;
}

void spawnsnake(nodo1 mappa , snake serpente, int i, int j){
    insincodasnake(serpente,accessoij(mappa,i,j));
}

void aggiornatutto(nodo1 mappa, snake serpente);

// movimento snake
void segui(snake serpente,int cancella);

int up(nodo1 mappa, snake serpente){
    int a=0;
    if(serpente->head->next!=NULL)
        if(comparacoord(accessoij(mappa,serpente->head->posizione->casella.i-1, serpente->head->posizione->casella.j), serpente->head->next->posizione)==1){
            return 1;
        }
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i-1,serpente->head->posizione->casella.j))==1)
        return 0;
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i-1,serpente->head->posizione->casella.j))==2){
        insincodasnake(serpente, accessoij(mappa, serpente->tail->posizione->casella.i, serpente->tail->posizione->casella.j));
        a=2;
    }
    if(serpente->head->next!=NULL)
        segui(serpente,a);
    else
        serpente->head->posizione->casella.img=' ';
    serpente->head->posizione=accessoij(mappa,serpente->head->posizione->casella.i-1,serpente->head->posizione->casella.j);
    serpente->head->posizione->casella.img='o';
    aggiornatutto(mappa,serpente);
    return 1;
}

int down(nodo1 mappa, snake serpente){
    int a=0;
    if(serpente->head->next!=NULL)
        if(comparacoord(accessoij(mappa,serpente->head->posizione->casella.i+1,serpente->head->posizione->casella.j),serpente->head->next->posizione)==1){
            return 1;      
    }
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i+1,serpente->head->posizione->casella.j))==1)
        return 0;
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i+1,serpente->head->posizione->casella.j))==2){
        insincodasnake(serpente, accessoij(mappa, serpente->tail->posizione->casella.i, serpente->tail->posizione->casella.j));
        a=2; 
    }
    if(serpente->head->next!=NULL)
        segui(serpente,a);
    else
        serpente->head->posizione->casella.img=' ';
    serpente->head->posizione=accessoij(mappa,serpente->head->posizione->casella.i+1,serpente->head->posizione->casella.j);
    serpente->head->posizione->casella.img='o';
    aggiornatutto(mappa,serpente);
    return 1;
}

int right(nodo1 mappa, snake serpente){
    int a=0;
    if(serpente->head->next!=NULL)
        if(comparacoord(accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j+1),serpente->head->next->posizione)==1){
            return 1;      
    }
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j+1))==1)
        return 0;
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j+1))==2){
        insincodasnake(serpente, accessoij(mappa, serpente->tail->posizione->casella.i, serpente->tail->posizione->casella.j));
        a=2;
    }
    if(serpente->head->next!=NULL)
        segui(serpente,a);
    else
        serpente->head->posizione->casella.img=' ';
    serpente->head->posizione=accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j+1);
    serpente->head->posizione->casella.img='o';
    aggiornatutto(mappa,serpente);
    return 1;
}

int left(nodo1 mappa, snake serpente){
    int a=0;
    if(serpente->head->next!=NULL)
        if(comparacoord(accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j-1),serpente->head->next->posizione)==1){
            return 1;      
    }
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j-1))==1)
        return 0;
    if (check(mappa, accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j-1))==2){
        insincodasnake(serpente, accessoij(mappa, serpente->tail->posizione->casella.i, serpente->tail->posizione->casella.j));    
        a=2;
    }
    if(serpente->head->next!=NULL)
        segui(serpente,a);
    else
        serpente->head->posizione->casella.img=' ';
    serpente->head->posizione=accessoij(mappa,serpente->head->posizione->casella.i,serpente->head->posizione->casella.j-1);
    serpente->head->posizione->casella.img='o';
    aggiornatutto(mappa,serpente);
    return 1;
     
}

int sceglivel(int dimensioni){
    int vel;
    if (dimensioni>0 && dimensioni<=5)
        vel=700;
     if (dimensioni>5 && dimensioni<=8)
        vel=600;
    if (dimensioni>8 && dimensioni<=10)
        vel=500;
    if (dimensioni>10 && dimensioni<=20)
        vel=450;
    if (dimensioni>20)
        vel=400;
    return vel;
    
}

// movimento da tastiera snake

void playermove(nodo1 mappa, snake serpente){
    char scelta;
    char salvaval;
    int vivo=1;
    struct pollfd mypoll = {0, POLLIN}; //Definisco su mypoll quale file deve essere controllato, nel mio caso ciò che introduco da tastiera, e che evento controllare, cioè se è presente un dato da leggere
    while ( getchar() != '\n' );
    printf(" \n\e[1;37mPremi per iniziare\e[0;37m\n");
    scanf("%c",&scelta);
    if(scelta!= 'a' && scelta!= 'A' && scelta != 'w' && scelta != 'W' && scelta !='s' && scelta != 'S' && scelta != 'd' && scelta != 'D')
        scelta='D';
    while(vivo==1){
        spawncibo(mappa);
        fflush(stdout);
        salvaval=scelta;    
        if(poll(&mypoll,1,sceglivel(contanodi(serpente))))
            scanf("%c",&scelta);
        switch(scelta){
            case 'w':vivo=up(mappa, serpente);break;
            case 'W':vivo=up(mappa, serpente);break;
            case 's':vivo=down(mappa, serpente);break;
            case 'S':vivo=down(mappa, serpente);break;
            case 'a':vivo=left(mappa, serpente);break;
            case 'A':vivo=left(mappa, serpente);break;
            case 'd':vivo=right(mappa, serpente);break;
            case 'D':vivo=right(mappa, serpente);break;
            default: scelta=salvaval;
        }
    }
}

void segui(snake serpente,int cancella){
    struct pallino* p=serpente->tail;
    if(serpente->head->next!=NULL){
        if(cancella!=2)
            p->posizione->casella.img=' ';
        while(p!=serpente->head){
            p->posizione=p->prec->posizione;
            p=p->prec;
        }
    }
}

void aggiornatutto(nodo1 mappa, snake serpente){
    aggiorna(mappa);
    printf("\n\t\e[1;37mPunti: %d\e[0;37m\n", contanodi(serpente));
}