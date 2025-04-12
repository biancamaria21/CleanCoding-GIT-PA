/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
  int data;
  struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    
typedef struct graph
{
  int v;
  int *vis;
  NODE **alst;
} GPH;

NODE *create_node(int v)
{
  NODE *nn = malloc(sizeof(NODE));
  nn->data = v;
  nn->next = NULL;
  return nn;
}

void add_edge(GPH *g, int src, int dest)
{
  NODE *nn = create_node(dest);
  nn->next = g->alst[src];
  g->alst[src] = nn;
  
  nn = create_node(src);
  nn->next = g->alst[dest];
  g->alst[dest] = nn;
}

GPH *create_g(int v)
{
  int i;
  GPH *g = malloc(sizeof(GPH));
  
  g->v = v;
  g->alst = malloc(v * sizeof(NODE *));
  g->vis = malloc(sizeof(int) * v);
  
  for (i = 0; i<v; i++)
  {
    g->alst[i] = NULL;
    g->vis[i] = 0;
  }    
  
  return g;
}

void DFS(GPH *g,int v_nr)
{
  NODE *adj_list = g->alst[v_nr];
  NODE *aux = adj_list;
  
  g->vis[v_nr] = 1;
  
  while (aux != NULL)
  {
    int con_ver = aux->data;
    
    if (g->vis[con_ver] == 0)
      DFS(g, con_ver);
    
    aux = aux->next;
  }
}

void insert_edges(GPH *g,int edg_nr)
{
  int src, dest, i;
  printf("adauga %d munchii (de la 0 la %d)\n",edg_nr,g->v - 1);
  
  for (i=0; i<edg_nr; i++)
  {
    scanf("%d%d",&src,&dest);
    add_edge(g,src,dest);
  }
}

void wipe(GPH *g)
{
  for (int i=0; i<g->v; i++)
  {
    g->vis[i] = 0;
  }
}

int can_reach(GPH *g, int src, int dest)
{
  wipe(g);
  DFS(g, src);

  return g->vis[dest]; //verificam daca dest este vizitat
}

int main()
{

  int nrv;
  int edg_nr;
  int src, dest;
  int i;
  
  printf("cate noduri are graful? ");
  scanf("%d", &nrv);
  
  printf("cate muchii are graful? ");
  scanf("%d", &edg_nr);
  
  GPH *g = create_g(nrv);
  
  insert_edges(g, edg_nr);

  printf("Introduceti restaurantul de la care plecati: ");
  scanf("%d",&src);

  printf("Introduceti restaurantul la care ajungeti: ");
  scanf("%d",&dest);
  
  if(can_reach(g, src, dest))
  {
    printf("Exista drum de la restaurantul %d la rest %d\n", src, dest);
  }
  else
  {
    printf("Nu exista drum de la restaurantul %d la restaurantul %d\n", src, dest);
  }
  
  return 0;
}
