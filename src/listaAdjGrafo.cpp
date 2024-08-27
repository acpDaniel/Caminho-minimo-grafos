#include "../include/listaAdjGrafo.hpp"
#include <iostream>

// Construtor da classe GraphList, inicializa a lista de adjacências com um número dado de vértices.
GraphList::GraphList(int vertices)
{
    numVertices = vertices;
    adjList = new Aresta *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adjList[i] = nullptr;
    }
}

// Destrutor da classe GraphList, libera a memória alocada para a lista de adjacências.
GraphList::~GraphList()
{
    // Percorre cada lista de adjacências e libera a memória alocada para cada aresta.
    for (int i = 0; i < numVertices; i++)
    {
        Aresta *temp = adjList[i];
        while (temp)
        {
            Aresta *next = temp->prox;
            delete temp;
            temp = next;
        }
    }
    delete[] adjList;
}

// Cria uma nova aresta com o vértice de destino e peso fornecidos.
Aresta *GraphList::createAresta(int verticeDest, double peso)
{
    Aresta *novaAresta = new Aresta;
    novaAresta->verticeDest = verticeDest;
    novaAresta->peso = peso;
    novaAresta->prox = nullptr;
    return novaAresta;
}

// Adiciona uma aresta na lista de adjacências do vértice fonte para o vértice de destino com o peso fornecido.
void GraphList::addAresta(int src, int dest, double peso)
{
    Aresta *novaAresta = createAresta(dest, peso);
    novaAresta->prox = adjList[src];
    adjList[src] = novaAresta;
}

// Adiciona uma aresta com peso 0 na lista de adjacências do vértice fonte para o vértice de destino (usado para portais).
void GraphList::addPortal(int src, int dest)
{
    addAresta(src, dest, 0);
}

// Retorna a lista de adjacências.
Aresta **GraphList::getAdjList()
{
    return adjList;
}

// Retorna o número de vértices no grafo.
int GraphList::getNumVertices()
{
    return numVertices;
}
