#include "matrizAdjGrafo.hpp"
#include <iostream>
#include <limits>

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

GraphMatriz::~GraphMatriz()
{
    for (int i = 0; i < numVertices; ++i)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void GraphMatriz::addAresta(int src, int dest, double peso)
{
    adjMatrix[src][dest] = peso;
}

void GraphMatriz::addPortal(int src, int dest)
{
    adjMatrix[src][dest] = 0;
}

double **GraphMatriz::getAdjMatrix()
{
    return adjMatrix;
}

int GraphMatriz::getNumVertices()
{
    return numVertices;
}
