#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int size=0, aux=0;

typedef struct node Node;


struct node{
	int c;
	Node *left, *right;
};

void cria_no(Node **raiz){
	(*raiz) = (Node*)malloc(sizeof(Node*));
	(*raiz)->left = NULL, (*raiz)->right = NULL;
}

void insere(Node **raiz, int x){
	if((*raiz)==NULL){
		cria_no(raiz);
		(*raiz)->c=x;
		size++;
		return;
	}
	if(x>(*raiz)->c){
		insere(&(*raiz)->right, x);
	}
	else{
		insere(&(*raiz)->left, x);
	}
}

void print_pre(Node *raiz){
	if(raiz==NULL) return;
	printf("%c", (char)raiz->c);
	aux++;
	if(aux!=size) printf(" ");
	print_pre(raiz->left);
	print_pre(raiz->right);
}

void print_in(Node *raiz){
	if(raiz==NULL) return;
	print_in(raiz->left);
	aux++;
	printf("%c", (char)(raiz->c));
	if(aux!=size) printf(" ");
	print_in(raiz->right);
}

void print_pos(Node *raiz){
	if(raiz==NULL) return;
	print_pos(raiz->left);
	print_pos(raiz->right);
	aux++;
	printf("%c", (char)(raiz->c));
	if(aux!=size) printf(" ");
}

void libera_arvore(Node *raiz){
	if(raiz==NULL) return;
	libera_arvore(raiz->left);
	libera_arvore(raiz->right);
	free(raiz);
}

void procura(Node *raiz, int x, int *ok){
	if(raiz==NULL) return;
	if(raiz->c==x){
		*ok=1;
		return;
	}
	if(raiz->c < x){
		procura(raiz->right, x, ok);
	}
	else procura(raiz->left, x, ok);
}

int main(){
	int c,n,x,i,j;
	Node *raiz=NULL;
	char s[8];
	while(scanf("%[^\n]%*c", s)!=EOF){
		aux=0;
		if(strlen(s)>3){
			if(strcmp(s, "INFIXA")==0){
				print_in(raiz);
				printf("\n");
			}
			if(strcmp(s, "PREFIXA")==0){
				print_pre(raiz);
				printf("\n");
			}
			if(strcmp(s, "POSFIXA")==0){
				print_pos(raiz);
				printf("\n");
			}
			continue;
		}
		if(s[0]=='I'){
			insere(&raiz, (int)s[2]);
		}
		else{
			int ok=0;
			procura(raiz, (int)s[2] , &ok);
			if(ok) printf("%c existe\n", s[2]);
			else printf("%c nao existe\n", s[2]);
		}
	}

	return 0;
}
