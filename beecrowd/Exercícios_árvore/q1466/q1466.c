#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node Node;
typedef struct tipolista TipoLista;

int size=0;

struct node{
	int val, nivel;
	Node *left, *right;
    Node *prox;
};

struct tipolista{
    Node *first, *last;
    int size;
};

void cria_no(Node **raiz){
	(*raiz) = (Node*)malloc(sizeof(Node));
	(*raiz)->left = NULL, (*raiz)->right = NULL;
}

void insere(Node **raiz, int x, int nivel){
	if((*raiz)==NULL){
		cria_no(raiz);
		(*raiz)->val=x;
        (*raiz)->nivel=nivel+1;
		size++;
		return;
	}
	if(x>(*raiz)->val){
		insere(&(*raiz)->right, x, (*raiz)->nivel);
	}
	else{
		insere(&(*raiz)->left, x, (*raiz)->nivel);
	}
}

void libera_arvore(Node *raiz){
	if(raiz==NULL) return;
	libera_arvore(raiz->left);
	libera_arvore(raiz->right);
	free(raiz);
}

void bfs(Node *raiz){
    int tam=0, i=0,j=0;
    Node *fila[505], *no;
    fila[++j] = raiz, tam++, i++; // i guarda a posição no qual o último valor está salvo
    while(tam>0 && j>=i && i>=1){
        no = fila[i++];
        printf("%d", no->val);
        tam--;
        if(no->left!=NULL) fila[++j] = no->left, tam++;
        if(no->right!=NULL) fila[++j] = no->right, tam++;
        if(tam!=0) printf(" ");
    }
}

int main(){ 
	int c,n,x,i,j;
	Node *raiz=NULL;
	scanf("%d", &c);
	for(i=1; i<=c; i++){
        printf("Case %d:\n", i);
        scanf("%d", &n);
        size=0;
        for(j=0; j<n; j++){
            scanf("%d", &x);
            insere(&raiz, x,1);
        }
        bfs(raiz);
        libera_arvore(raiz);
        raiz=NULL;
        printf("\n");
        printf("\n");
    }
	return 0;
}