#include "../include/listaAdjGrafo.hpp"
#include <iostream>

GraphList::GraphList(int vertices)
{
    numVertices = vertices;
    adjList = new Aresta *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adjList[i] = nullptr;
    }
}

GraphList::~GraphList()
{
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

Aresta *GraphList::createAresta(int verticeDest, double peso)
{
    Aresta *novaAresta = new Aresta;
    novaAresta->verticeDest = verticeDest;
    novaAresta->peso = peso;
    novaAresta->prox = nullptr;
    return novaAresta;
}

void GraphList::addAresta(int src, int dest, double peso)
{
    // std::cout << "valor na linha " << src << " ligada ao vertice " << adjList[src]->verticeDest << " com peso: " << adjList[src]->peso << std::endl;
    Aresta *novaAresta = createAresta(dest, peso);
    novaAresta->prox = adjList[src];
    adjList[src] = novaAresta;
    // std::cout << "valor novo na linha " << src << " ligada ao vertice " << adjList[src]->verticeDest << " com peso: " << adjList[src]->peso << std::endl;
}

void GraphList::addPortal(int src, int dest)
{
    addAresta(src, dest, 0);
}

Aresta **GraphList::getAdjList()
{
    return adjList;
}

int GraphList::getNumVertices()
{
    return numVertices;
}
