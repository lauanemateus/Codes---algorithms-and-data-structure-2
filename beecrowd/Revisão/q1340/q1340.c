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
    TipoLista Fila, Pilha, Priority;
    Node *aux;
    int n,a,b,i,j, ok1, ok2, ok3;
    crialista(&Fila), crialista(&Pilha), crialista(&Priority);

    while(scanf("%d", &n)!=EOF){
        ok1 = 1, ok2 = 1, ok3 = 1;
        destroi(&Pilha), destroi(&Fila), destroi(&Priority);
        crialista(&Fila), crialista(&Pilha), crialista(&Priority);
        for(i=0; i<n; i++){
            scanf("%d %d", &a, &b);
            //printf("a=%d b=%d\n",a,b);
            if(a==1){
                push_last(&Fila, b), push_last(&Pilha, b), adiciona_ordenado(&Priority, b);
                continue;
            }
            if(busca(&Fila, b)==0){
                ok1=0, ok2=0, ok3=0;
            }
            if(ok1){
                if(b==Fila.first->prox->x){
                    pop_first(&Fila);
                }
                else ok1=0;
            }
            if(ok2){
                if(b==Priority.last->x){
                    pop_last(&Priority);
                } 
                else ok2=0;
            }
            if(ok3){
                if(b==Pilha.last->x){
                    pop_last(&Pilha);
                }
                else ok3=0;
            }
        }
        if((ok1==1 && ok2==1) || (ok1==1 && ok3==1) || (ok2==1 && ok3==1))
            printf("not sure\n");
        else if(ok1==1) printf("queue\n");
        else if(ok2==1) printf("priority queue\n");
        else if(ok3==1) printf("stack\n");
        else{
            printf("impossible\n");

        }
    }
    return 0;
}
