#include <stdio.h>
#include <stdlib.h>

#define BRANCO 1
#define CINZA 2
#define PRETO 3
#define RED 4

/*Estrutura para um vértice em uma lista encadeada: */
typedef struct vertice
{
    int d;
    int f;
    int cor;
    int pai;
    int identificador;       /*Identificador do vértice armazenado no nó. */
    struct vertice *proximo; /* Próximo nó na lista encadeada. */
} Vertice;

/*Estrutura do Grafo: */
typedef struct grafo
{
    int E;              /* Quantidade de arestas. */
    int V;              /* Quantidade de vértices. */
    Vertice **listaAdj; /* Lista de adjacências. */
} Grafo;

/* */
Grafo *criar_grafo(int tamanho)
{
    int v;
    Grafo *G = (Grafo *)malloc(sizeof(Grafo));
    G->E = 0;
    G->V = tamanho;
    G->listaAdj = (Vertice **)malloc(tamanho * sizeof(Vertice *));
    for (v = 0; v < G->V; v++)
    {
        G->listaAdj[v] = NULL;
    }
    return G;
}

/* */
void liberar_grafo(Grafo *G)
{
    int v;
    for (v = 0; v < G->V; v++)
    {
        if (G->listaAdj[v] != NULL)
        {
            free(G->listaAdj[v]);
        }
    }
    free(G->listaAdj);
    free(G);
}

/* */
void inserir_aresta(Grafo *G, int u, int v)
{
    Vertice *temp, *ultimo = NULL;
    /* Verificando se o vértice v já existe na lista de adjacência de u: */
    for (temp = G->listaAdj[u]; temp != NULL; temp = temp->proximo)
    {
        if (temp->identificador == v)
        {
            return;
        }
        ultimo = temp;
    }
    /* Inserindo a aresta (u,v): */
    Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
    novo->identificador = v;
    novo->proximo = NULL;
    if (ultimo != NULL)
    {
        /* Inserção na última posição da lista: */
        ultimo->proximo = novo;
    }
    else
    {
        /* Nova cabeça da lista: */
        G->listaAdj[u] = novo;
    }
    /* Incrementando o número de arestas: */
    G->E++;
}

/* */
void imprimir_grafo(Grafo *G)
{
    printf("Lista de adjacência de G:\n");
    int v;
    for (v = 0; v < G->V; v++)
    {
        if (G->listaAdj[v] != NULL)
        {
            Vertice *temp;
            for (temp = G->listaAdj[v]; temp != NULL; temp = temp->proximo)
            {
                // if()
                // printf("Nó %d : ", v);
                printf("Aresta: %d - %d \n", v, temp->identificador);
            }
            // printf("\n");
        }
    }
}

/* */
void DFS_Visit(Grafo *G, Vertice *V, int u, int *tempo)
{
    V[u].cor = CINZA;
    *tempo = (*tempo) + 1;
    V[u].d = (*tempo);
    Vertice *v;

    for (v = G->listaAdj[u]; v != NULL; v = v->proximo)
    {
        if (V[v->identificador].cor == BRANCO)
        {
            printf("Aresta Arvore: %d - %d \n", u, v->identificador);
            V[v->identificador].pai = u;
            DFS_Visit(G, V, v->identificador, tempo);
        }
        else
        {
            printf("Aresta Outra:  %d - %d \n", u, v->identificador);
        }
    }
    V[u].cor = PRETO;
    *tempo = (*tempo) + 1;
    V[u].f = *tempo;
}

void Busca_Profundidade(Grafo *G)
{
    int u;
    int tempo = 0;
    Vertice *V = (Vertice *)malloc(G->V * sizeof(Vertice));
    for (u = 0; u < G->V; u++)
    {
        V[u].cor = BRANCO;
        V[u].pai = -1;
    }

    for (u = 0; u < G->V; u++)
    {

        if (V[u].cor == BRANCO)
        {
            DFS_Visit(G, V, u, &tempo);
        }
    }

    for (u = 0; u < G->V; u++)
    {
        if (V[u].pai == -1)
            printf("\nComeçando no vértice %d: ", u);
        printf("%d ", u);
    }
    printf("\n");
}

/* */
int main()
{

    int tamanho = 12; /*Número de vértices!*/

    Grafo *G = criar_grafo(tamanho);
    printf("Ex1: A, B, C, E, D, G, H, F, I");
    /*Inserção das arestas conforme a aula: EX 2*/
    inserir_aresta(G, 0, 1);
    inserir_aresta(G, 0, 3);
    inserir_aresta(G, 1, 2);
    inserir_aresta(G, 2, 5);
    inserir_aresta(G, 5, 4);
    inserir_aresta(G, 5, 6);
    inserir_aresta(G, 6, 0);
    inserir_aresta(G, 6, 3);
    inserir_aresta(G, 6, 4);
    inserir_aresta(G, 4, 1);
    inserir_aresta(G, 7, 8);
    inserir_aresta(G, 9, 10);
    inserir_aresta(G, 10, 11);
    inserir_aresta(G, 11, 9);

    // printf("--------Ex3--------");
    // inserir_aresta(G, 0, 1); /*Aresta 0-1 e 1-0*/
    // inserir_aresta(G, 1, 0);
    // inserir_aresta(G, 0, 5); /*Aresta 0-5 e 5-0*/
    // inserir_aresta(G, 5, 0);
    // inserir_aresta(G, 2, 1); /*Aresta 2-1 e 1-2*/
    // inserir_aresta(G, 1, 2);
    // inserir_aresta(G, 4, 1); /*Aresta 4-1 e 1-4*/
    // inserir_aresta(G, 1, 4);
    // inserir_aresta(G, 4, 5); /*Aresta 4-5 e 5-4*/
    // inserir_aresta(G, 5, 4);
    // inserir_aresta(G, 6, 3); /*Aresta 6-3 e 3-6*/
    // inserir_aresta(G, 3, 6);

    // imprimir_grafo(G);

    Busca_Profundidade(G);

    liberar_grafo(G);

    return 0;
}