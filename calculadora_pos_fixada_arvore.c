#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node Node;
typedef struct TipoRaiz Raiz;
#define MAX 100 // tamanho maximo da expressao

struct node{
    double x;
    char c;
    Node *prox, *ant;
};

typedef struct{
    Node *first, *last;
    int size;
} TipoLista;

struct TipoRaiz{
    double x;
    char c;
    Raiz *left, *right;
};

void CriaLista(TipoLista *Lista){
    Lista->size=0;
    Lista->first=NULL, Lista->last=NULL;
}

void Insere_valor(TipoLista *Lista, double val){
    Node *new = (Node*)malloc(sizeof(Node));
    new->x = val;
    new->c='@'; // controle para saber o que inseriu no Node
    Lista->size++;
    if(Lista->size==1){
        Lista->first = (Node*)malloc(sizeof(Node));
        Lista->first->prox = new;
        Lista->last = new;
        Lista->last->prox = NULL;
        Lista->first->ant = NULL;
    }
    Lista->last->prox = new;
    new->ant = Lista->last;
    Lista->last = new; 
}

void Insere_caracter(TipoLista *Lista, char c){
    Node *new = (Node*)malloc(sizeof(Node));
    new->c = c;
    Lista->size++;
    if(Lista->size==1){
        Lista->first = (Node*)malloc(sizeof(Node));
        Lista->first->prox = new;
        Lista->last = new;
        Lista->last->prox = NULL;
        Lista->first->ant = NULL;
    }
    Lista->last->prox = new;
    new->ant = Lista->last;
    Lista->last = new; 
}

int Remove(TipoLista *Lista){
    if(Lista->size==0) return 0;
    Node *last_new = Lista->last->ant;
    Lista->size--;
    if(Lista->size==0){
        CriaLista(Lista);
        return 1;
    }
    free(Lista->last);
    last_new->prox = NULL;
    Lista->last = last_new;
    return 1;
}

void Cria_raiz(Raiz **raiz){
    (*raiz) = (Raiz*)malloc(sizeof(Raiz));
    (*raiz)->right=NULL;
    (*raiz)->left=NULL;
}

void Constroi_arvore(Raiz **raiz, TipoLista *Lista){
    if(Lista->size<1) return;
    Cria_raiz(raiz);
    double x=Lista->last->x;
    char c=Lista->last->c;
    Remove(Lista);
    (*raiz)->x=x, (*raiz)->c=c;
    if(c=='@') return;
    if((*raiz)->c=='@') return;
    Constroi_arvore(&(*raiz)->right, Lista); // adiciona o ramo direito caso o Node esteja armazenando um caracter valido
    Constroi_arvore(&(*raiz)->left, Lista); // adiciona o ramo esquerdo
}

void imprime_lista(TipoLista *Lista){
    if(Lista->size==0){
        printf("Lista vazia\n");
    }
    Node *aux=Lista->first;
    for(int i=0; i<Lista->size; i++){
        aux=aux->prox;
        printf("(%lf,%c) ", aux->x, aux->c);
    }
    printf("\n");
}

void imprime_raiz(Raiz *raiz){
    if(raiz==NULL) return;
    printf("raiz (%.2lf,%c) ", raiz->x, raiz->c);
    imprime_raiz(raiz->right);
    imprime_raiz(raiz->left);
}
int Calculadora(Raiz *raiz, int *ok){ // Se *ok==1, é possível calcular, ou seja, a expressão é válida. 
    if(*ok==0) return 0;
    if(raiz==NULL){
        *ok = 0;
        return 0;
    }
    if(raiz->c=='@'){
        return raiz->x;
    }
    double a = Calculadora(raiz->left, ok), b = Calculadora(raiz->right, ok);
    int i;
    if(raiz->c=='+'){
        raiz->x = a + b;
    }
    if(raiz->c=='-'){
        raiz->x = a - b;
    }
    if(raiz->c=='*'){
        raiz->x = a * b;
    }
    if(raiz->c=='/'){
        raiz->x = a / b;
    }
    if(raiz->c=='^'){
        raiz->x=1;
        for(i=0; i<b; i++){
            raiz->x = raiz->x * a;
        }
    }
    raiz->c='@';
    return raiz->x;
}


int main(){
    TipoLista Lista;
    Raiz *raiz;
    CriaLista(&Lista);
    char expressao[MAX], val[MAX], c;
    int i=0,j=0,ok=1;
    double a, ans;

    printf("Este programa simula uma calculadora pós-fixada com árvore binária\n");
    printf("OBS: Digite apenas números inteiros de até 5 dígitos e caracteres ('+', '-', '*', '/') de forma que a expressão obtenha um resultado\n");
    printf("\nDigite a expressão:\n");
    scanf("%[^\n]", expressao);

    while(i<strlen(expressao)){
        j=0;
        if(expressao[i]==' '){
            i++;
            continue;
        }
        if(expressao[i]=='+' || expressao[i]=='-' || expressao[i]=='/' || expressao[i]=='^' || expressao[i]=='*'){
            Insere_caracter(&Lista, expressao[i]);
            i++;
            continue;
        }
        while(expressao[i]!=' ' && expressao[i]!='\0'){
            val[j]=expressao[i];
            if(expressao[i]=='+' || expressao[i]=='-' || expressao[i]=='/' || expressao[i]=='^' || expressao[i]=='*'){
                break;
            }
            if((val[j]<'0' || val[j]>'9') && val[j]!='+' && val[j]!='-' && val[j]!='*' && val[j]!='/' && val[j]!='^'){
                printf("Erro: expressão digitada indevidamente\n");
                return 0;
            }
            i++, j++;
        }
        val[j]='\0';
        a = atof(val);
        Insere_valor(&Lista, a);
        
    }
    //imprime_lista(&Lista);
    Constroi_arvore(&raiz, &Lista);
    ans = Calculadora(raiz, &ok);

    if(ans==0){
        printf("Erro: expressão digitada indevidamente\n");
    }
    else{
        printf("\nResposta = %lf\n", ans);
    }
    //imprime_raiz(raiz);
    return 0;
}
