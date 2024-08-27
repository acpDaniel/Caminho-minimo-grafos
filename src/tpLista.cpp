#include <iostream>
#include <cmath>
#include <limits>
#include "../include/listaAdjGrafo.hpp"
#include "../include/minHeap.hpp"
#include "../include/auxStructs.hpp"

using namespace std;

double distanciaEuclidiana(Coords a, Coords b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool dijkstra(GraphList &grafo, int portaisPermitidos, double energia)
{
    int numVertices = grafo.getNumVertices();
    Aresta **adj = grafo.getAdjList();
    double *dist = new double[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        dist[i] = std::numeric_limits<double>::max();
    }

    dist[0] = 0;

    MinHeap pq(numVertices * (portaisPermitidos + 1));
    pq.push({0, 0, portaisPermitidos});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        // Queremos sempre chegar no vértice numVertices - 1
        if (estadoAtual.no == numVertices - 1)
        {
            if (dist[numVertices - 1] <= energia)
            {
                delete[] dist;
                return true;
            }
            else
            {
                delete[] dist;
                return false;
            }
        }

        for (Aresta *aresta = adj[estadoAtual.no]; aresta; aresta = aresta->prox)
        {
            bool ehPortal = aresta->peso == 0.0;
            int portaisUsados = 0;
            if (ehPortal)
            {
                portaisUsados = 1;
            }

            // podemos inserir se tiver portais restantes para ser usado ou se nao for portal
            bool liberaInsercao = estadoAtual.portaisRestantes > 0 || !ehPortal;

            if (dist[aresta->verticeDest] > estadoAtual.custo + aresta->peso && liberaInsercao)
            {
                dist[aresta->verticeDest] = estadoAtual.custo + aresta->peso;
                pq.push({aresta->verticeDest, estadoAtual.custo + aresta->peso, estadoAtual.portaisRestantes - portaisUsados});
            }
        }
    }

    delete[] dist;
    return false;
}

bool a_star(GraphList &grafo, int portaisPermitidos, double energia, Coords *coords)
{
    int numVertices = grafo.getNumVertices();
    Aresta **adj = grafo.getAdjList();

    double *dist = new double[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        dist[i] = std::numeric_limits<double>::max();
    }

    dist[0] = 0;

    MinHeap pq(numVertices * (portaisPermitidos + 1));
    pq.push({0, distanciaEuclidiana(coords[0], coords[numVertices - 1]), portaisPermitidos});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        if (estadoAtual.no == numVertices - 1)
        {
            if (dist[numVertices - 1] <= energia)
            {
                delete[] dist;
                return true;
            }
            else
            {
                delete[] dist;
                return false;
            }
        }

        double pesoCorrigido = estadoAtual.custo - distanciaEuclidiana(coords[estadoAtual.no], coords[numVertices - 1]);

        for (Aresta *aresta = adj[estadoAtual.no]; aresta; aresta = aresta->prox)
        {
            bool ehPortal = aresta->peso == 0.0;
            int portaisUsados = 0;
            if (ehPortal)
            {
                portaisUsados = 1;
            }

            // podemos inserir se tiver portais restantes para ser usado ou se nao for portal
            bool liberaInsercao = estadoAtual.portaisRestantes > 0 || !ehPortal;

            if (dist[aresta->verticeDest] > pesoCorrigido + aresta->peso && liberaInsercao)
            {
                dist[aresta->verticeDest] = pesoCorrigido + aresta->peso;
                double valorComHeuristica = dist[aresta->verticeDest] + distanciaEuclidiana(coords[aresta->verticeDest], coords[numVertices - 1]);
                pq.push({aresta->verticeDest, valorComHeuristica, estadoAtual.portaisRestantes - portaisUsados});
            }
        }
    }
    delete[] dist;
    return false;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    Coords coords[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> coords[i].x >> coords[i].y;
    }

    GraphList g(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        double peso = distanciaEuclidiana(coords[u], coords[v]);
        g.addAresta(u, v, peso);
    }

    for (int i = 0; i < k; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addPortal(u, v);
    }

    double s;
    int q;
    cin >> s >> q;

    bool dijkstra_result = dijkstra(g, q, s);

    bool a_star_result = a_star(g, q, s, coords);

    cout << (dijkstra_result ? 1 : 0) << " " << (a_star_result ? 1 : 0) << endl;

    return 0;
}
