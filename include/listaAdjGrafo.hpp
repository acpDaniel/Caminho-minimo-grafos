#ifndef LISTAADJGRAFO_HPP
#define LISTAADJGRAFO_HPP

struct Aresta
{
    int verticeDest;
    double peso;
    Aresta *prox;
};

struct Coords
{
    double x;
    double y;
};

// Esse portal sempre sera direcionado do u para v
struct Portal
{
    int u, v;
};

class GraphList
{
private:
    Aresta **adjList;
    int numVertices;

public:
    GraphList(int vertices);
    ~GraphList();

    Aresta *createAresta(int verticeDest, double peso);
    void addAresta(int src, int dest, double peso);
    void addPortal(int src, int dest);
    Aresta **getAdjList();
    int getNumVertices();
};

#endif
