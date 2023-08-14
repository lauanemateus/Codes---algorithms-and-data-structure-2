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
   int **m = malloc(r * sizeof(int *));
   for (vertex i = 0; i < r; ++i)
      m[i] = malloc(c * sizeof(int));
   for (vertex i = 0; i < r; ++i)
      for (vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit(int V)
{
   Graph G = malloc(sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = MATRIXint(V, V, 0);
   return G;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc(Graph G, vertex v, vertex w, int peso)
{
   if (G->adj[v][w] == 0)
   {
      G->adj[v][w] = peso; // a matriz de adjacência armazenará o peso do arco entre v-w
      G->A++;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHremoveArc() remove do grafo G o arco v-w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */
void GRAPHremoveArc(Graph G, vertex v, vertex w)
{
   if (G->adj[v][w] != 0)
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
         if (G->adj[v][w] != 0)
            printf(" (%d, %d)", w, G->adj[v][w]);
      printf("\n");
   }
}

int main()
{
   Graph G = GRAPHinit(5);
   GRAPHinsertArc(G, 0, 1, 9);
   GRAPHinsertArc(G, 1, 0, 4);
   GRAPHinsertArc(G, 1, 3, 8);
   GRAPHinsertArc(G, 3, 2, 2);
   GRAPHinsertArc(G, 2, 1, 17);
   GRAPHinsertArc(G, 3, 0, 7);
   GRAPHinsertArc(G, 1, 4, 15);
   GRAPHinsertArc(G, 4, 0, 3);
   GRAPHinsertArc(G, 4, 3, 5);
   GRAPHinsertArc(G, 4, 2, 12);
   printf("\n\n");
   GRAPHshow(G);
   printf("\n\n");
   return 0;
}