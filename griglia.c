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


int insincoda1(nodo1 *head){    //funzione per creare una lista di liste (righe della matrice)
    nodo1 p=*head;
    nodo1 nuovonodo=(nodo1)malloc(sizeof(struct nodo1));    //alloco la memoria e creo il nodo
    nuovonodo->lista=NULL;
    if (*head==NULL){           //caso nel quale la lista sia vuota
        nuovonodo->next=NULL;
        nuovonodo->prec=NULL;
        *head=nuovonodo;
        return 1;
    }
    while(p->next!=NULL){   //caso in cui la lista non è vuota
        p=p->next;
    }
    nuovonodo->next=NULL;
    nuovonodo->prec=p;
    p->next=nuovonodo;
}

int insincoda2(nodo2 *head){    //funzione per creare una lista di caselle (colonne della matrice)
    nodo2 p=*head;
    nodo2 nuovonodo=(nodo2)malloc(sizeof(struct nodo2)); //alloco la memoria e creo il nodo
    if (*head==NULL){   //caso nel quale la lista sia vuota
        nuovonodo->next=NULL;
        nuovonodo->prec=NULL;
        *head=nuovonodo;
        return 1;
    }
    while(p->next!=NULL){   //caso in cui la lista non è vuota
        p=p->next;
    }
    nuovonodo->next=NULL;
    nuovonodo->prec=p;
    p->next=nuovonodo;
}

void creamatrice(nodo1 *head,int i,int j){  //funzione che permette la creazione della mappa e quindi la lista di liste
    int k;              //variabile da contatore
    int l;
    nodo1 p;
    for (k=0; k<i; k++){
        insincoda1(head);
        if(k==0) p=*head;
        if (k!=0) p=p->next;
        for (l=0; l<j; l++){
            insincoda2(&(p->lista));
        }
    }
}

void creamappa(nodo1 head){ //funzione che imposta le sprite, imposta gli indici delle caselle
    nodo2 k=head->lista;
    int i=0;
    int j=0;
    while(head!=NULL){
        while(k!=NULL){
           k->casella.img=' ';
           k->casella.i=i;      //imposta indice righe
           k->casella.j=j++;    //imnposta indice colonne
           if(k->prec == NULL || k -> next == NULL)
                k->casella.img='|'; // sprite muri laterali
            if(head->prec == NULL || head->next == NULL)
                k->casella.img='-'; //sprite muro superiore e inferiore
           k=k->next;
        }
    i++; //imposta indice righe   
    j=0;
    head=head->next;
    if(head!=NULL)
        k=head->lista;
    }    
}

nodo2 accessoij(nodo1 head, int i, int j){  //funzione che permette l'accesso in posizione ij e ritorna un puntatore alla posizione richiesta
    int m;
    int n;
    nodo2 k;
    for (m=0; m<i && head!=NULL; m++){
        head=head->next;
    }
    k=head->lista;
    for (n=0; n<j; n++) {
        k=k->next;
    }
    return k;
}

void stampa(nodo1 head){    //funzione che stampa la mappa
    printf("\033[1;36m");
    nodo2 i=head->lista;
    printf("\n");
    while(head!=NULL){
        printf("\t");
        while(i!=NULL){
            if(i->casella.img=='o')
            printf("\033[1;32m");
           printf("%c ", i->casella.img);
           if(i->casella.img=='o')
            printf("\033[1;36m");
           i=i->next;
        }
        printf("\n");
    head=head->next;
    if(head!=NULL)
        i=head->lista;
    }
    printf("\033[0m");
}

void aggiorna(nodo1 mappa){
    system("clear");
        printf("\n\n");
    printf("\033[1;33m");
    printf("      _____ _____ _____ _____ _____\n");
    printf("     |   __|   | |  _  |  |  |   __|\n");
    printf("     |__   | | | |     |    -|   __|\n");
    printf("     |_____|_|___|__|__|__|__|_____|\n");
    printf("\033[0m");
    stampa(mappa);  
}

int comparacoord(nodo2 posizionenuova, nodo2 posizionesecondo){
    if(posizionenuova->casella.i==posizionesecondo->casella.i && posizionenuova->casella.j==posizionesecondo->casella.j)
        return 1;
    else 
        return 0;
}

int check(nodo1 mappa, nodo2 posizione){
    if(posizione->casella.img=='@')
        return 2;
    if (posizione->casella.img!=' '){
        return 1;
    }
    else return 0;
}

int contarighe(nodo1 mappa){
    int a=0;
    while(mappa!=NULL){
        a+=1;
        mappa=mappa->next;
    }
    return a;
}

int contacolonne(nodo1 mappa){
    int b=0;
    nodo2 p=mappa->lista;
    while(p!=NULL){
        b+=1;
        p=p->next;
    }
    return b;    
}    

int checkcibo(nodo1 mappa){
    int i, j;
    int conto=0;
    nodo2 p=mappa->lista;
    while(mappa!=NULL){
        while(p!=NULL){
            if(p->casella.img=='@')
                conto++;
            p=p->next;
        }
        mappa=mappa->next;
        if(mappa!=NULL)
            p=mappa->lista;
    }
    if (conto>=2)
        return 1;
    else return 0;
}

void spawncibo(nodo1 mappa){
    int x;
    x=rand() % 10 ;
    if(x==1 && checkcibo(mappa)==0){
        int i, j;
        i=(rand()%(contarighe(mappa)-2))+1;
        j=(rand()%(contacolonne(mappa)-2))+1;
        if(accessoij(mappa,i,j)->casella.img!='o'){
            nodo2 cibo=accessoij(mappa, i, j);
            cibo->casella.img='@';
        }
    }
}