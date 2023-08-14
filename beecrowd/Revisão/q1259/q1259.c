#include<stdio.h>
#include<stdlib.h>

#define MAX 100005

void Merge(int ini, int meio, int fim, int v[]){
    int i=ini, j = meio+1, k=0;
    int aux[MAX];
    while(i<=meio && j<=fim){
        if(v[i]<v[j]){
            aux[k++] = v[i++];
        }
        else aux[k++] = v[j++];
    }
    while(i<=meio){
        aux[k++] = v[i++];
    }
    while(j<=fim){
        aux[k++] = v[j++];
    }
    for(i=ini; i<=fim; i++){
        v[i] = aux[i-ini];
    }
}

void Sort(int ini, int fim, int v[]){
    if(ini<fim){
        int meio = (ini+fim)/2;
        Sort(ini, meio, v);
        Sort(meio+1, fim, v);
        Merge(ini, meio, fim, v);
    }
}

int main(){
    int v[MAX], odd[MAX], even[MAX], i=0, j=0,w,n;
    scanf("%d", &n);
    for(w=0; w<n; w++){
        scanf("%d", &v[w]);
        if(v[w]%2==0) even[i++]=v[w];
        else odd[j++] = -v[w];
    }
    Sort(0, i-1, even);
    Sort(0, j-1, odd);
    for(w=0; w<i; w++) printf("%d\n", even[w]);
    for(w=0; w<j; w++) printf("%d\n", -odd[w]);
    return 0;
}