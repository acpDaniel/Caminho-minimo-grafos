#include "matrizAdjGrafo.hpp"
#include <iostream>
#include <limits>

// Construtor da classe GraphMatriz, inicializa a matriz de adjacência com um número dado de vértices.
GraphMatriz::GraphMatriz(int vertices)
{
    numVertices = vertices;
    adjMatrix = new double *[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        adjMatrix[i] = new double[numVertices];
        for (int j = 0; j < numVertices; ++j)
        {
            if (i == j)
            {
                adjMatrix[i][j] = 0;
            }
            else
            {
                adjMatrix[i][j] = std::numeric_limits<double>::max();
            }
        }
    }
}

// Destrutor da classe GraphMatriz, libera a memória alocada para a matriz de adjacência.
GraphMatriz::~GraphMatriz()
{
    for (int i = 0; i < numVertices; ++i)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

// Adiciona uma aresta na matriz de adjacência do vértice fonte para o vértice de destino com o peso fornecido.
void GraphMatriz::addAresta(int src, int dest, double peso)
{
    adjMatrix[src][dest] = peso;
}

// Adiciona uma aresta com peso 0 na matriz de adjacência do vértice fonte para o vértice de destino (usado para portais).
void GraphMatriz::addPortal(int src, int dest)
{
    adjMatrix[src][dest] = 0;
}

// Retorna a matriz de adjacência.
double **GraphMatriz::getAdjMatrix()
{
    return adjMatrix;
}

// Retorna o número de vértices no grafo.
int GraphMatriz::getNumVertices()
{
    return numVertices;
}
