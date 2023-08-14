#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define QTD 50
typedef struct node Node;

typedef struct matricula{
    char *mat;
    char *nome;
    char *curso;
    int nota1, nota2; // considerando notas inteiras 
} Matricula;

struct node{
    Matricula dados;
    Node *prox, *ant;
};

typedef struct{
    int size;
    Node *first, *last;
} TipoLista;

void aloca_matricula(Matricula *mat_new);
void CriaLista(TipoLista *Lista);
void Create_matricula(TipoLista *Lista);
void Read(TipoLista *Lista);
void Insere_last(Matricula *mat_new, TipoLista *Lista);
void Delete(TipoLista *Lista);
void Update(TipoLista *Lista);
void Legenda();

int main(){
    TipoLista Lista;
    Node *aux;
    int i,x;
    Legenda();
    CriaLista(&Lista);
    scanf("%d", &x);
    while(1){
        while(x<0 || x>4){
            printf("Erro! Digite um numero da legenda de 0 a 4: ");
            scanf("%d", &x);
        }
        switch(x){
            case 0:
                if(Lista.size==0) return 0;
                aux=Lista.first->prox;
                while(aux!=Lista.last){
                    free(aux->ant);
                    aux=aux->prox;
                }
                free(Lista.last);
                printf("Programa finalizado.\n");
                return 0;
            case 1:
                Create_matricula(&Lista);
                break;
            case 2:
                Read(&Lista);
                break;
            case 3:
                Update(&Lista);
                break;
            case 4:
                Delete(&Lista);
                break;
        }
        Legenda();
        scanf("%d", &x);
    }
    return 0;
}

void aloca_matricula(Matricula *mat_new){
    mat_new->mat = (char*)malloc(sizeof(char)*QTD);
    mat_new->nome = (char*)malloc(sizeof(char)*QTD);
    mat_new->curso = (char*)malloc(sizeof(char)*QTD);
}

void CriaLista(TipoLista *Lista){ // Lista->first não guardará nenhum dado, só apontará para o primeiro elemento da matriz
                                  // Lista->last será o próprio último elemento
    Lista->first = NULL;
    Lista->last = NULL;
    Lista->size=0;
}

void Create_matricula(TipoLista *Lista){
    if(Lista->size==50){
        printf("Matriz cheia: Não é possivel criar mais um registro!\n");
        return;
    }
    int ok=1,i,x;
    char nota[QTD];
    Node *aux;
    Matricula new_mat;
    aloca_matricula(&new_mat);

    printf("Digite a matricula: ");
    scanf("%*c%[^\n]%*c", new_mat.mat);

    aux = Lista->first;
    for(i=0; i<Lista->size; i++){
        aux = aux->prox;
        if(strcmp(new_mat.mat, aux->dados.mat)==0){
            printf("Matricula ja existe!\n");
            return;
        }
    }

    printf("Digite o nome: ");
    scanf("%[^\n]%*c", new_mat.nome);
    printf("Digite o curso: ");
    scanf("%[^\n]%*c", new_mat.curso);
    printf("Digite a nota 1: ");
    scanf("%[^\n]%*c", nota);
    while(ok){
        for(i=0; i<strlen(nota); i++){
            if(strlen(nota)>2 || nota[i]<'0' || nota[i]>'9'){
                ok=0;
                break;
            }
        }
        if(strlen(nota)==1) x=nota[0]-'0';
        else x = (nota[0]-'0')*10 + nota[1]-'0';
        if(x<0 || x>10) ok=0;

        if(ok==0){
            printf("Erro! Digite a nota 1 novamente: ");
            scanf("%[^\n]%*c", nota);
            ok=1;
            continue;
        }
        new_mat.nota1 = atoi(nota);
        break;
    }
    printf("Digite a nota 2: ");
    scanf("%[^\n]%*c", nota);
    while(ok){
        for(i=0; i<strlen(nota); i++){
            if(strlen(nota)>2 || nota[i]<'0' || nota[i]>'9'){
                ok=0;
                break;
            }
        }
        if(strlen(nota)==1) x=nota[0]-'0';
        else x = (nota[0]-'0')*10 + nota[1]-'0';
        if(x<0 || x>10) ok=0;
        if(ok==0){
            printf("Erro! Digite a nota 2 novamente: ");
            scanf("%[^\n]%*c", nota);
            ok=1;
            continue;
        }
        new_mat.nota2 = atoi(nota);
        break;
    }
    printf("Media final = %.2lf\n", (new_mat.nota1+new_mat.nota2)/2.0);
    Insere_last(&new_mat, Lista);
} 

void Read(TipoLista *Lista){
    int ind,ok,i;
    Node *aux;
    if(Lista->size==0){
        printf("Erro! Nao ha matriculas cadastradas\n");
        return;
    }
    printf("Deseja ler todas matriculas?\n(1)Sim\n(2)Nao\n");
    scanf("%d", &ok);
    if(ok==1){
        aux = Lista->first->prox;
        printf("\n");
        while(aux!=Lista->first){
            printf("Matricula: %s\nNome: %s\nCurso: %s\nNota 1: %d\nNota 2: %d\n", aux->dados.mat, aux->dados.nome, aux->dados.curso, aux->dados.nota1, aux->dados.nota2);
            printf("Media final = %.2lf\n", (aux->dados.nota1+aux->dados.nota2)/2.0);
            printf("----------------------------------------------------------------------------\n");
            aux = aux->prox;
        }
        return;
    }
    printf("Selecione o indice da matricula a ser lida: ");
    scanf("%d", &ind);
    while(ind>Lista->size || ind<=0){
        printf("Erro! Digite um indice de uma matricula existente: ");
        scanf("%d", &ind);
    }
    aux=Lista->first;
    for(i=1; i<=ind; i++){
        aux=aux->prox;
    }
    printf("Matricula: %s\nNome: %s\nCurso: %s\nNota 1: %d\nNota 2: %d\n", aux->dados.mat, aux->dados.nome, aux->dados.curso, aux->dados.nota1, aux->dados.nota2);
    printf("Media final = %.2lf\n", (aux->dados.nota1+aux->dados.nota2)/2.0);
}

void Update(TipoLista *Lista){
    int ind,x, ok=1,i;
    Matricula *mat_atual;
    Node *aux;
    char y[QTD];
    if(Lista->size==0){
        printf("Erro! Nao ha matriculas cadastradas\n");
        return;
    }
    printf("Digite o indice da matricula que deseja atualizar: \n");
    scanf("%d", &ind);
    while(ind<=0 || ind>Lista->size){
        printf("Erro! Digite novamente o indice: ");
        scanf("%d", &ind);
    }
    aux=Lista->first;
    for(i=0; i<ind; i++){
        aux=aux->prox;
    }
    mat_atual = &(aux->dados);
    printf("O que deseja atualizar?\n");
    printf("(1)Codigo da matricula\n");
    printf("(2)Nome\n(3)Curso\n(4)Nota 1\n(5)Nota 2\n");
    scanf("%d%*c", &x);
    while(x<1 && x>5){
        printf("Erro! Digite um numero da legenda de 1 a 5: ");
        scanf("%d%*c", &x);
    }
    switch(x){
        case 1:
            printf("Digite o novo codigo da matricula: ");
            scanf("%[^\n]%*c", y);
            strcpy(mat_atual->mat, y);
            break;
        case 2:
            printf("Digite o novo nome: ");
            scanf("%[^\n]%*c", y);
            strcpy(mat_atual->nome, y);
            break;
        case 3:
            printf("Digite o novo curso: ");
            scanf("%[^\n]%*c", y);
            strcpy(mat_atual->curso, y);
            break;
        case 4:
            printf("Digite a nova nota1: ");
            scanf("%[^\n]%*c", y);
            while(ok){
                for(i=0; i<strlen(y); i++){
                    if(strlen(y)>2 || y[i]<'0' || y[i]>'9'){
                        ok=0;
                        break;
                    }
                }
                if(strlen(y)==1) x=y[0]-'0';
                else x = (y[0]-'0')*10 + y[1]-'0';
                if(x<0 || x>10) ok=0;

                if(ok==0){
                    printf("Erro! Digite a nota 1 novamente: ");
                    scanf("%[^\n]%*c", y);
                    ok=1;
                    continue;
                }
                mat_atual->nota1 = atoi(y);
                break;
            }
            break;
        case 5:
            printf("Digite a nova nota 2: ");
            scanf("%[^\n]%*c", y);
            while(ok){
                for(i=0; i<strlen(y); i++){
                    if(strlen(y)>2 || y[i]<'0' || y[i]>'9'){
                        ok=0;
                        break;
                    }
                }
                if(strlen(y)==1) x=y[0]-'0';
                else x = (y[0]-'0')*10 + y[1]-'0';
                if(x<0 || x>10) ok=0;

                if(ok==0){
                    printf("Erro! Digite a nota 2 novamente: ");
                    scanf("%[^\n]%*c", y);
                    ok=1;
                    continue;
                }
                mat_atual->nota2 = atoi(y);
                break;
            }
            break;
    }
    printf("Matricula atualizada.\n");
}


void Insere_last(Matricula *mat_new, TipoLista *Lista){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->dados = (*mat_new);
    Lista->size++;

    if(Lista->size==1){
        Lista->first = (Node*)malloc(sizeof(Node));
        Lista->last = new_node;
        Lista->first->prox = Lista->last;
        Lista->first->ant = Lista->last;
        Lista->last->prox = Lista->first;
        Lista->last->ant = Lista->first;
        return;
    }

    Lista->last->prox = new_node;
    new_node->ant = Lista->last;
    Lista->last = Lista->last->prox; // new
    Lista->first->ant = Lista->last;
    Lista->last->prox = Lista->first;
}

void Delete(TipoLista *Lista){
    int i=0, ind,ok;
    Node *aux;
    if(Lista->size==0){
        printf("Erro! Nao ha matriculas cadastradas\n");
        return;
    }
    printf("Selecione o indice da matricula a ser deletada: ");
    scanf("%d", &ind);
    while(ind<=0 || ind>Lista->size){
        printf("Erro! Digite um indice de uma matricula existente: ");
        scanf("%d", &ind);
    }
    printf("Tem certeza que deseja deletar?\n(1)Sim\n(2)Nao\n");
    scanf("%d", &ok);
    if(ok==2) return;

    Lista->size--;
    if(Lista->size==0){
        free(Lista->last);
        Lista->first = NULL;
        Lista->last = NULL;
        printf("Matricula deletada.\n");
        return;
    }
    aux=Lista->first;
    for(i=1; i<=ind; i++){
        aux=aux->prox;
    }
    aux->ant->prox = aux->prox;
    aux->prox->ant = aux->ant;
    free(aux);
    if(Lista->size==1){
        Lista->last=Lista->first->prox;
    }
    printf("Matricula deletada.\n");
}

void Legenda(){
    printf("\nDigite os numeros de 0 a 4\n");
    printf("(0)Sair do programa\n");
    printf("(1)Criar uma nova matricula\n");
    printf("(2)Ler os dados das matriculas\n");
    printf("(3)Atualizar os dados de uma matricula\n");
    printf("(4)Deletar os dados de uma matricula\n");
    printf("**OBS: Os indices das matriculas vao de 1 a 50**\n");
}