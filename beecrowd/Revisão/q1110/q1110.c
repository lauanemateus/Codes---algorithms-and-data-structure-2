#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    struct Node *prox;
    int x;
} Node;

typedef struct TipoLista{
    Node *first, *last;
    int size;
} TipoLista;

void crialista(TipoLista *Lista){
    Lista->first = NULL;
    Lista->last = NULL;
    Lista->size=0;
}

void push_last(TipoLista *Lista, int x){
    Node *new = (Node*)malloc(sizeof(Node));
    new->x = x;
    new->prox = NULL;
    Lista->size++;
    if(Lista->size==1){
        Lista->first = (Node*)malloc(sizeof(Node));
        Lista->first->prox = new;
        Lista->last = new;
        return;
    }
    Lista->last->prox =  new;
    Lista->last = new;
}

void push_first(TipoLista *Lista, int x){
    if(Lista->size==0){
        push_last(Lista, x);
        return;
    }
    Node *new = (Node*)malloc(sizeof(Node));
    new->x=x;
    new->prox = Lista->first->prox;
    Lista->first->prox = new;
    Lista->size++;
}

void pop_first(TipoLista *Lista){
    if(Lista->size==0) return;
    Node *aux = Lista->first;
    Lista->first = Lista->first->prox;
    free(aux);
    Lista->size--;
}

void pop_last(TipoLista *Lista){
    if(Lista->size==0) return;
    int i;
    Node *aux=Lista->first;
    for(i=0; i<Lista->size-1; i++){
        aux=aux->prox;
    }
    Lista->last = aux;
    free(aux->prox);
    Lista->size--;

}

void destroi_pilha(TipoLista *Lista){
    if(Lista->size==0) return;
    Node *aux = Lista->first, *at=aux;
    int i;
    for(i=0; i<Lista->size; i++){
        aux=aux->prox;
        free(at);
        at=aux;
    }
    Lista->size=0;
}

int main(){
    TipoLista Lista, Discards;
    crialista(&Lista);
    crialista(&Discards);
    Node *aux;
    int x,i;
    while(scanf("%d", &x), x){
        for(i=x; i>=1; i--) push_last(&Lista, i);
        while(Lista.size>2){
            push_last(&Discards, Lista.last->x);
            pop_last(&Lista);
            x = Lista.last->x;
            pop_last(&Lista);
            push_first(&Lista, x);
        }
        push_last(&Discards, Lista.last->x);
        pop_last(&Lista);
        printf("Discarded cards: ");
        if(Discards.size !=0){
            aux = Discards.first;
            for(i=0; i<Discards.size; i++){
                aux = aux->prox;
                printf("%d", aux->x);
                if(i==Discards.size-1) printf("\n");
                else printf(", ");
            }
        }
        /*aux = Lista.first;
        for(i=0; i<Lista.size; i++){
            aux = aux->prox;
            printf("%d", aux->x);
            printf(", ");
        }*/
        printf("Remaining card: %d\n", Lista.first->prox->x);
        destroi_pilha(&Lista), destroi_pilha(&Discards);
    }
    return 0;
}
