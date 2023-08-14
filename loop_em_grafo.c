#include <stdio.h>
#include <stdlib.h>

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. O campo adj é um ponteiro para a matriz de adjacências do grafo. O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
struct graph
{
   int V;
   int A;
   int **adj;
};
/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct graph *Graph;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */
static int **MATRIXint(int r, int c, int val)
{
   int **m = (int**)malloc(r * sizeof(int *));
   for (vertex i = 0; i < r; ++i)
      m[i] = (int*)malloc(c * sizeof(int));
   for (vertex i = 0; i < r; ++i)
      for (vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit(int V)
{
   Graph G = (Graph)malloc(sizeof (struct graph));
   G->V = V;
   G->A = 0;
   G->adj = MATRIXint(V, V, 0);
   return G;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
   if (G->adj[v][w] == 0)
   {
      G->adj[v][w] = 1;
      G->A++;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHremoveArc() remove do grafo G o arco v-w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */
void GRAPHremoveArc(Graph G, vertex v, vertex w)
{
   if (G->adj[v][w] == 1)
   {
      G->adj[v][w] = 0;
      G->A--;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void GRAPHshow(Graph G)
{
   for (vertex v = 0; v < G->V; ++v)
   {
      printf("%2d:", v);
      for (vertex w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1)
            printf(" %2d", w);
      printf("\n");
   }
}

int dfs(Graph G, vertex v, int **vis, vertex v_ini){
   int i, ans=0;
   for(i=0; i<G->V; i++){
      if(G->adj[v][i]==1){
         if((*vis)[i]==0){
            (*vis)[i] = 1;
            ans = dfs(G, i, vis, v_ini);
         }
         else if(v!=v_ini && i==v_ini) {
            //printf("loop em v=%d i=%d v_ini=%d\n", v, i, v_ini);
            ans=1;
            break;
         }
      }
   }
   return ans;
}

int PossuiLoops(Graph G){
   int *vis, i, id=1, ans=0;
   vis = (int*)malloc((G->V)*sizeof(int));
   for(i=0; i<G->V; i++){
      vis[i]=0;
   }
   for(i=0; i<G->V; i++){
      if(vis[i]==0){
         vis[i] = 1;
         ans = dfs(G, i, &vis, i);
      }
      if(ans==1) return 1;
   }
   return ans;
}

int main()
{
   Graph G = GRAPHinit(10);
   GRAPHinsertArc(G, 0, 1);
   GRAPHinsertArc(G, 1, 0);
   GRAPHinsertArc(G, 1, 3);
   GRAPHinsertArc(G, 1, 4);
   GRAPHinsertArc(G, 2, 1);
   GRAPHinsertArc(G, 3, 0);
   GRAPHinsertArc(G, 3, 2);
   GRAPHinsertArc(G, 4, 0);
   GRAPHinsertArc(G, 4, 3);
   GRAPHinsertArc(G, 4, 2); 

   /*
   GRAPHinsertArc(G, 0, 1);
   GRAPHinsertArc(G, 1, 2);
   GRAPHinsertArc(G, 2, 3);
   GRAPHinsertArc(G, 1, 4);
   GRAPHinsertArc(G, 0, 4); */
   GRAPHshow(G);
   if(PossuiLoops(G)) printf("O grafo possui loops\n");
   else printf("O grafo nao possui loop\n");
   return 0;
}