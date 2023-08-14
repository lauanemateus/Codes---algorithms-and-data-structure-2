#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define QTD 100
typedef struct node Node;

struct node{
    double x;
    Node *prox, *ant;
};

typedef struct tipolista{
    int size;
    Node *first, *last; // first é a celula cabeça e aponta para o primeiro elemento e second armazena o endereço do ultimo elemento da pilha

} TipoLista;

void CriaLista(TipoLista *Pilha){
    Pilha->first = NULL;
    Pilha->last = NULL;
    Pilha->size=0;
}

void Insere(TipoLista *Pilha, double val){
    Node *new = (Node*)malloc(sizeof(Node));
    new->x = val;
    Pilha->size++;
    if(Pilha->size==1){
        Pilha->first = (Node*)malloc(sizeof(Node));
        Pilha->first->prox = new;
        Pilha->last = new;
        Pilha->last->prox = NULL;
        Pilha->first->ant = NULL;
    }
    Pilha->last->prox = new;
    new->ant = Pilha->last;
    Pilha->last = new; 
}

int Remove(TipoLista *Pilha){
    Node *last_new = Pilha->last->ant;
    if(Pilha->size==0) return 0;
    Pilha->size--;
    if(Pilha->size==0){
        CriaLista(Pilha);
        return 1;
    }
    free(Pilha->last);
    last_new->prox = NULL;
    Pilha->last = last_new;
    return 1;
}

int Solve(char expressao[], TipoLista *Pilha){
    int i=0,j=0;
    char val[QTD];
    double a, b;
    while(i<strlen(expressao)){
        j=0;
        if(expressao[i]==' '){
            i++;
            continue;
        }
        while(expressao[i]!=' ' && expressao[i]!='\0'){
            val[j]=expressao[i];
            if((val[j]<'0' || val[j]>'9') && val[j]!='+' && val[j]!='-' && val[j]!='*' && val[j]!='/') return 0;
            i++, j++;
        }
        val[j]='\0';
        a = atof(val);
        if(strlen(val)==1){
            if(val[0]>='0' && val[0]<='9'){
                Insere(Pilha, a);
            }
            else{
                if(val[0]!='+' && val[0]!='-' && val[0]!='*' && val[0]!='/') return 0;
                if(Pilha->size<2) return 0;
                b = Pilha->last->x;
                Remove(Pilha);
                a=Pilha->last->x;
                Remove(Pilha);
                if(val[0]=='+') Insere(Pilha, a+b);
                if(val[0]=='-') Insere(Pilha, a-b);
                if(val[0]=='/') Insere(Pilha, a/b);
                if(val[0]=='*') Insere(Pilha, a*b);
            }
            continue;
        }
        Insere(Pilha, a);
    }
    if(Pilha->size==1) return 1; 
    return 0;
}

int main(){
    TipoLista Pilha;
    CriaLista(&Pilha);
    char expressao[QTD];
    printf("Este programa simula uma calculadora pós-fixada\n");
    printf("OBS: Digite apenas números reais de até 5 dígitos e caracteres('+', '-', '*', '/') de forma que a expressão obtenha um resultado\n");
    printf("\nDigite a expressão:\n");
    scanf("%[^\n]", expressao);
    if(Solve(expressao, &Pilha)==0){
        printf("Erro: expressão digitada indevidamente\n");
    }
    else{
        printf("Resposta = %lf\n", Pilha.first->prox->x);
    }
    return 0;
}