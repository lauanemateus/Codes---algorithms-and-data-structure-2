#include<stdio.h>
#include<stdlib.h>

const int max = 1005;

int main(){
    int cont,ans, i,j, t;
    char s[max];
    scanf("%d", &t);
    for(j=0; j<t; j++){
        ans=0,cont=0;
        scanf("%s", s);
        for(i=0; s[i]!='\0'; i++){
            if(s[i]=='<')  cont++;
            if(s[i]=='>' && cont>0) cont--, ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}