#include <iostream>
#include <cmath>
#include <limits>
#include "../include/matrizAdjGrafo.hpp"
#include "../include/minHeap.hpp"
#include "../include/auxStructs.hpp"

using namespace std;

double distanciaEuclidiana(Coords a, Coords b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool dijkstra(int n, double **adjMatrix, int portaisPermitidos, double energia)
{
    double *dist = new double[n];
    for (int i = 0; i < n; ++i)
    {
        dist[i] = std::numeric_limits<double>::max();
    }

    dist[0] = 0;

    MinHeap pq(n * (portaisPermitidos + 1));
    pq.push({0, 0, portaisPermitidos});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        if (estadoAtual.no == n - 1)
        {
            if (dist[n - 1] <= energia)
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

        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[estadoAtual.no][v] != std::numeric_limits<double>::max())
            {
                bool ehPortal = adjMatrix[estadoAtual.no][v] == 0.0;
                int portaisUsados = 0;
                if (ehPortal)
                {
                    portaisUsados = 1;
                }

                // podemos inserir se tiver portais restantes para ser usado ou se nao for portal
                bool liberaInsercao = estadoAtual.portaisRestantes > 0 || !ehPortal;

                if (dist[v] > estadoAtual.custo + adjMatrix[estadoAtual.no][v] && liberaInsercao)
                {
                    dist[v] = estadoAtual.custo + adjMatrix[estadoAtual.no][v];
                    pq.push({v, estadoAtual.custo + adjMatrix[estadoAtual.no][v], estadoAtual.portaisRestantes - portaisUsados});
                }
            }
        }
    }

    delete[] dist;
    return false;
}

bool a_star(int n, double **adjMatrix, int portaisPermitidos, double energia, Coords *coords)
{
    double *dist = new double[n];
    for (int i = 0; i < n; ++i)
    {
        dist[i] = std::numeric_limits<double>::max();
    }

    dist[0] = 0;

    MinHeap pq(n * (portaisPermitidos + 1));
    pq.push({0, distanciaEuclidiana(coords[0], coords[n - 1]), portaisPermitidos});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        if (estadoAtual.no == n - 1)
        {
            if (dist[n - 1] <= energia)
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

        double pesoCorrigido = estadoAtual.custo - distanciaEuclidiana(coords[estadoAtual.no], coords[n - 1]);

        for (int v = 0; v < n; ++v)
        {
            // temos que verificar os valores "vazios" na minha matriz
            if (adjMatrix[estadoAtual.no][v] != std::numeric_limits<double>::max())
            {
                bool ehPortal = adjMatrix[estadoAtual.no][v] == 0.0;
                int portaisUsados = 0;
                if (ehPortal)
                {
                    portaisUsados = 1;
                }

                // podemos inserir se tiver portais restantes para ser usado ou se nao for portal
                bool liberaInsercao = estadoAtual.portaisRestantes > 0 || !ehPortal;

                if (dist[v] > pesoCorrigido + adjMatrix[estadoAtual.no][v] && liberaInsercao)
                {
                    dist[v] = pesoCorrigido + adjMatrix[estadoAtual.no][v];
                    double valorComHeuristica = dist[v] + distanciaEuclidiana(coords[v], coords[n - 1]);
                    pq.push({v, valorComHeuristica, estadoAtual.portaisRestantes - portaisUsados});
                }
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

    GraphMatriz g(n);

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

    bool dijkstra_result = dijkstra(n, g.getAdjMatrix(), q, s);

    bool a_star_result = a_star(n, g.getAdjMatrix(), q, s, coords);

    cout << (dijkstra_result ? 1 : 0) << " " << (a_star_result ? 1 : 0) << endl;

    return 0;
}
