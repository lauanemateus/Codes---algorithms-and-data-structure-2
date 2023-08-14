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

Node* insere_right(Node **raiz, int x){
    cria_no(&(*raiz)->right);
    (*raiz)->right->val=x;
    return (*raiz)->right; 
}

Node* insere_left(Node **raiz, int x){
    cria_no(&(*raiz)->left);
    (*raiz)->left->val=x;
    return (*raiz)->left; 
}

void print_pos(Node *raiz){
	if(raiz==NULL) return;
    //printf("chamando a esquerda val do node eh %c\n", (char)raiz->val);
	print_pos(raiz->left);
    //printf("chamando a direita val do node eh %c\n", (char)raiz->val);
	print_pos(raiz->right);
	printf("%c", (char)raiz->val);
}

void libera_arvore(Node *raiz){
	if(raiz==NULL) return;
	libera_arvore(raiz->left);
	libera_arvore(raiz->right);
	free(raiz);
}

int main(){
	int c,n,x,i,j,mark[125], ind[125];
	Node *raiz=NULL, *pre, *in, *root=NULL, *enderecos[125];
    char a[60], b[60], aux;
	scanf("%d", &c);
	for(j=1; j<=c; j++){
		scanf("%d %s %s", &n,a,b);
        for (int i = 0; i < n; i++)
        {
            mark[a[i]]=0;
            ind[b[i]]=i;
        }
        cria_no(&raiz);
        root=raiz;
        raiz->val=a[0];
        enderecos[a[0]]=raiz;
        mark[a[0]]=1;
        for (int i = 1; i < n; i++)
        {
            if (ind[a[i]]<ind[a[i-1]]){
                //printf("inserindo %c a esquerda\n", (char)a[i]);
                raiz = insere_left(&raiz, a[i]);
                enderecos[a[i]] = raiz;
                mark[a[i]]=1;
                continue;
            }
            aux='@';
            for (int k = 0; k < n; k++)
            {
                if(b[k]==a[i]) break;
                if(mark[b[k]]==1){
                    aux=b[k];
                }
            }
            raiz = enderecos[aux];
            //printf("inserindo %c a direita\n", (char)a[i]);
            raiz = insere_right(&raiz, a[i]);
            enderecos[a[i]] = raiz;
            mark[a[i]]=1;
        }
        print_pos(root);
        printf("\n");
        free(root);
	}

	return 0;
}