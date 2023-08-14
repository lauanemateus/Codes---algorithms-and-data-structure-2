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
	printf("%d", raiz->c);
	aux++;
	if(aux<size) printf(" ");
	print_pre(raiz->left);
	print_pre(raiz->right);
}

void print_in(Node *raiz){
	if(raiz==NULL) return;
	print_in(raiz->left);
	aux++;
	printf("%d", (raiz->c));
	if(aux<size) printf(" ");
	print_in(raiz->right);
}

void print_pos(Node *raiz){
	if(raiz==NULL) return;
	print_pos(raiz->left);
	print_pos(raiz->right);
	aux++;
	printf("%d", (raiz->c));
	if(aux<size) printf(" ");
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

Node* remover(Node *raiz, int x){
    Node *aux;
    if(raiz==NULL) return NULL;
    if(raiz->c == x){
        if(raiz->left==NULL && raiz->right==NULL){
            size--;
            free(raiz);
            return NULL;
        }
        else if(raiz->left == NULL || raiz->right==NULL){
            size--;
            if(raiz->left!=NULL)
                aux = raiz->left;
            else
                aux = raiz->right;
            free(raiz);
            return aux;
        }
        else{
            aux = raiz->left;
            while(aux->right!=NULL)
                aux = aux->right;
            raiz->c = aux->c;
            aux->c = x;
            raiz->left = remover(raiz->left, x);
            return raiz; 
        }
    }
    else{
        if(x<raiz->c)
            raiz->left = remover(raiz->left, x);
        else
            raiz->right = remover(raiz->right, x);
        return raiz;
    }
}

int main(){
	int c,n,x,i,j;
	Node *raiz=NULL;
	char s[1000], auxs[1000];
	while(scanf("%[^\n]%*c", s)!=EOF){
		aux=0;
        if(size==0) raiz=NULL;
        if(strcmp(s, "INFIXA")==0){
            print_in(raiz);
            printf("\n");
            //printf("\nSIZE=%d\n", size);
            continue;
        }
        if(strcmp(s, "PREFIXA")==0){
            print_pre(raiz);
            printf("\n");
            //printf("\nSIZE=%d\n", size);
            continue;
        }
        if(strcmp(s, "POSFIXA")==0){
            print_pos(raiz);
            printf("\n");
            //printf("\naux=%d SIZE=%d\n",aux, size);
            continue;
        }
        i=2,j=0;
        while(s[i]!=' ' && s[i]!='\0'){
            auxs[j++] = s[i++]; 
        }
        auxs[j] = '\0';
        x = atoi(auxs);
		if(s[0]=='I'){
			insere(&raiz, x);
		}
		else if(s[0]=='P'){
			int ok=0;
			procura(raiz, x , &ok);
			if(ok) printf("%d existe\n", x);
			else printf("%d nao existe\n", x);
		}
        else if(s[0]=='R'){
            raiz = remover(raiz, x);

        }
	}
    libera_arvore(raiz);
	return 0;
}