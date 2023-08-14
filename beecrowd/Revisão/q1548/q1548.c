#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    struct Node *prox;
    int x, nota;
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

void destroi(TipoLista *Lista){
    if(Lista->size==0) return;
    Node *at = Lista->first->prox, *aux=at;
    int i;
    for(i=0; i<Lista->size; i++){
        aux=at->prox;
        free(at);
        at=aux;
    }
    Lista->size=0;
}

void imprime(TipoLista *Lista){
    Node *aux = Lista->first;
    int i;
    for(i=0; i<Lista->size; i++){
        aux = aux->prox;
        printf("%d\n", aux->x);
        //printf(", ");
    }
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

int busca(TipoLista *Lista, int x){
    int i;
    Node *aux=Lista->first;
    for(i=0; i<Lista->size; i++){
        aux=aux->prox;
        if(aux->x==x) return 1;
    }
    return 0;
}

void push_anywhere(TipoLista *Lista, int x, int pos){ // pos é a posição a ser adicionada de 1 a Lista.size+1
    if(pos==1){
        push_first(Lista, x);
        return;
    }
    if(pos==Lista->size+1){
        push_last(Lista, x);
        return;
    }
    int i;
    Node *aux = Lista->first, *new = (Node*)malloc(sizeof(Node));
    new->x=x;
    for(i=0; i<pos-1; i++){
        aux=aux->prox;
    }
    new->prox = aux->prox;
    aux->prox = new;
    Lista->size++;
}

void adiciona_ordenado(TipoLista *Lista, int x){
    Node *aux=Lista->first;
    int j;
    for(j=0; j<Lista->size; j++){
        aux=aux->prox;
        if(aux->x>x){
            push_anywhere(Lista, x, j+1);
            return;
        }
    }
    push_last(Lista, x);
}

int main(){
    TipoLista Fila1, Fila2;
    Node *aux1,*aux2;
    int n,i,j,testes,nota,ans;
    crialista(&Fila1), crialista(&Fila2);
    scanf("%d", &testes);
    while(testes--){
        scanf("%d", &n);
        destroi(&Fila1), destroi(&Fila2);;
        crialista(&Fila1), crialista(&Fila2);
        ans=0;
        for(i=0; i<n; i++){
            scanf("%d", &nota);
            push_last(&Fila1, nota), adiciona_ordenado(&Fila2, -nota); 
        }
        aux1=Fila1.first, aux2=Fila2.first;
        for(i=0; i<n; i++){
            aux1=aux1->prox, aux2=aux2->prox;
            if(aux1->x == -(aux2->x)) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
