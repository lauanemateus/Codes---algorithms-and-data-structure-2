#include<stdio.h>
#include<stdlib.h>

typedef struct node Node;


struct node{
	int val;
	Node *left, *right;
};

void cria_no(Node **raiz){
	(*raiz) = (Node*)malloc(sizeof(Node*));
	(*raiz)->left = NULL, (*raiz)->right = NULL;
}

void insere(Node **raiz, int x){
	if((*raiz)==NULL){
		cria_no(raiz);
		(*raiz)->val=x;
		return;
	}
	if(x>(*raiz)->val){
		insere(&(*raiz)->right, x);
	}
	else{
		insere(&(*raiz)->left, x);
	}
}

void print_pre(Node *raiz){
	if(raiz==NULL) return;
	printf(" %d", raiz->val);
	print_pre(raiz->left);
	print_pre(raiz->right);
}

void print_in(Node *raiz){
	if(raiz==NULL) return;
	print_in(raiz->left);
	printf(" %d", raiz->val);
	print_in(raiz->right);
}

void print_pos(Node *raiz){
	if(raiz==NULL) return;
	print_pos(raiz->left);
	print_pos(raiz->right);
	printf(" %d", raiz->val);
}

void libera_arvore(Node *raiz){
	if(raiz==NULL) return;
	libera_arvore(raiz->left);
	libera_arvore(raiz->right);
	free(raiz);
}

int main(){
	int c,n,x,i,j;
	Node *raiz=NULL;
	scanf("%d", &c);
	for(j=1; j<=c; j++){
		scanf("%d", &n);
		libera_arvore(raiz);
		raiz = NULL;
		for(i=0; i<n; i++){
			scanf("%d", &x);
			insere(&raiz, x);
		}
		printf("Case %d:\n", j);
		printf("Pre.:");
		print_pre(raiz);
		printf("\nIn..:");
		print_in(raiz);
		printf("\nPost:");
		print_pos(raiz);
		printf("\n\n");

	}

	return 0;
}