#ifndef MATRIZ_ADJ_GRAFO_HPP
#define MATRIZ_ADJ_GRAFO_HPP

class GraphMatriz
{
private:
    double **adjMatrix;
    int numVertices;

public:
    GraphMatriz(int vertices);
    ~GraphMatriz();

    void addAresta(int src, int dest, double peso);
    void addPortal(int src, int dest);
    double **getAdjMatrix();
    int getNumVertices();
};

#endif
