#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define QTD 50

typedef struct matricula{
    char mat[QTD];
    char nome[QTD];
    char curso[QTD];
    int nota1, nota2;
} Matricula;

void Create(Matricula *dados, Matricula *dado_atual, int* ind_atual){
    if(*ind_atual==50){
        printf("Matriz cheia: Não é possivel criar mais um registro!\n");
        return;
    }
    int ok=1,i,x;
    char nota[QTD];

    printf("Digite a matricula: ");
    scanf("%*c%[^\n]%*c", (dado_atual)->mat);

    for(i=0; i<*ind_atual; i++){
        if(strcmp(dado_atual->mat, dados[i].mat)==0){
            printf("Matricula ja existe!\n");
            return;
        }
    }

    printf("Digite o nome: ");
    scanf("%[^\n]%*c", (dado_atual)->nome);
    printf("Digite o curso: ");
    scanf("%[^\n]%*c", (dado_atual)->curso);
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
        (dado_atual)->nota1 = atoi(nota);
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
        (dado_atual)->nota2 = atoi(nota);
        break;
    }
    (*ind_atual) ++;
    printf("Media final = %.2lf\n", (dado_atual->nota1+dado_atual->nota2)/2.0);
} 

void Read(Matricula *dados, int *ind_atual){
    int ind;
    if(*ind_atual==0){
        printf("Erro! Nao ha matriculas cadastradas\n");
        return;
    }
    printf("Selecione o indice da matricula a ser lida: ");
    scanf("%d", &ind);
    while(ind>=*ind_atual || ind<0){
        printf("Erro! Digite um indice de uma matricula existente: ");
        scanf("%d", &ind);
    }
    printf("Matricula: %s\nNome: %s\nCurso: %s\nNota 1: %d\nNota 2: %d\n", dados[ind].mat, dados[ind].nome, dados[ind].curso, dados[ind].nota1, dados[ind].nota2);
    printf("Media final = %.2lf\n", (dados[ind].nota1+dados[ind].nota2)/2.0);
}

void Update(Matricula *dados, int *ind_atual){
    int ind,x, ok=1,i;
    char y[QTD];
    if(*ind_atual==0){
        printf("Erro! Nao ha matriculas cadastradas\n");
        return;
    }
    printf("Digite o indice da matricula que deseja atualizar: \n");
    scanf("%d", &ind);
    while(ind<0 || ind>=*ind_atual){
        printf("Erro! Digite novamente o indice: ");
        scanf("%d", &ind);
    }
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
            strcpy((dados[ind]).mat, y);
            break;
        case 2:
            printf("Digite o novo nome: ");
            scanf("%[^\n]%*c", y);
            strcpy((dados[ind]).nome, y);
            break;
        case 3:
            printf("Digite o novo curso: ");
            scanf("%[^\n]%*c", y);
            strcpy((dados[ind]).curso, y);
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
                (dados[ind]).nota1 = atoi(y);
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
                (dados[ind]).nota2 = atoi(y);
                break;
            }
            break;
    }
    printf("Matricula atualizada.\n");
}

void Delete(Matricula *dados, int *ind_atual){
    int ind, i,ok;
    if(*ind_atual==0){
        printf("Erro! Nao ha matriculas cadastradas\n");
        return;
    }
    printf("Digite o indice da matricula que deseja deletar: ");
    scanf("%d", &ind);
    while(ind<0 || ind>=*ind_atual){
        printf("Erro! Digite um indice de uma matricula existente: ");
        scanf("%d", &ind);
    }
    printf("Tem certeza que deseja deletar?\n(1)Sim\n(2)Nao\n");
    scanf("%d", &ok);
    if(ok==2) return;
    for(i=ind; i<*ind_atual; i++){
        dados[i] = dados[i+1];
    }
    (*ind_atual)--;
    printf("Matricula deletada.\n");
}

void Legenda(){
    printf("\nDigite os numeros de 1 a 4\n");
    printf("(0)Sair do programa\n");
    printf("(1)Criar uma nova matricula\n");
    printf("(2)Ler os dados de uma matricula\n");
    printf("(3)Atualizar os dados de uma matricula\n");
    printf("(4)Deletar os dados de uma matricula\n");
    printf("**OBS: Os indices das matriculas vao de 0 a 49**\n");
}

int main(){
    Matricula *dados;
    dados = (Matricula*)malloc(QTD*sizeof(Matricula));
    int ind_atual=0, x, i;
    Legenda();
    scanf("%d", &x);
    while(1){
        while(x<0 || x>4){
            printf("Erro! Digite um numero da legenda de 0 a 4: ");
            scanf("%d", &x);
        }
        switch(x){
            case 0:
                free(dados);
                printf("Programa finalizado.\n");
                return 0;
            case 1:
                Create(dados, &dados[ind_atual], &ind_atual);
                break;
            case 2:
                Read(dados, &ind_atual);
                break;
            case 3:
                Update(dados, &ind_atual);
                break;
            case 4:
                Delete(dados, &ind_atual);
                break;
        }
        Legenda();
        scanf("%d", &x);
    }
    return 0;
}