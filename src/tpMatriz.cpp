#include <iostream>
#include <cmath>
#include <limits>
#include "../include/matrizAdjGrafo.hpp"
#include "../include/minHeap.hpp"

using namespace std;

double distanciaEuclidiana(Coords a, Coords b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool dijkstra(int n, double **adjMatrix, int portaisPermitidos, double energia)
{
    double dist[n][portaisPermitidos + 1];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= portaisPermitidos; ++j)
        {
            dist[i][j] = numeric_limits<double>::max();
        }
    }

    dist[0][0] = 0;

    MinHeap pq(n * (portaisPermitidos + 1)); // capacidade inicial
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        // cout << "Visitando nó " << estadoAtual.no << " com custo " << estadoAtual.custo << " e " << estadoAtual.portaisUsados << " portais usados." << endl;

        if (estadoAtual.no == n - 1 && estadoAtual.custo <= energia)
        {
            return true;
        }

        if (estadoAtual.custo > dist[estadoAtual.no][estadoAtual.portaisUsados])
        {
            continue;
        }

        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[estadoAtual.no][v] != numeric_limits<double>::max())
            {
                if (adjMatrix[estadoAtual.no][v] == 0)
                {
                    if (estadoAtual.portaisUsados < portaisPermitidos)
                    {
                        double portalCost = estadoAtual.custo; // Custo do portal é 0
                        if (portalCost < dist[v][estadoAtual.portaisUsados + 1])
                        {
                            dist[v][estadoAtual.portaisUsados + 1] = portalCost;
                            pq.push({v, portalCost, estadoAtual.portaisUsados + 1});
                            // cout << "Atualizando nó " << v << " com novo custo " << portalCost << " através de portal." << endl;
                        }
                    }
                }
                else
                {
                    double newCost = estadoAtual.custo + adjMatrix[estadoAtual.no][v];
                    if (newCost < dist[v][estadoAtual.portaisUsados])
                    {
                        dist[v][estadoAtual.portaisUsados] = newCost;
                        pq.push({v, newCost, estadoAtual.portaisUsados});
                        // cout << "Atualizando nó " << v << " com novo custo " << newCost << " através de trilha." << endl;
                    }
                }
            }
        }
    }

    return false;
}

bool a_star(int n, double **adjMatrix, int portaisPermitidos, double energia, Coords *coords)
{
    double dist[n][portaisPermitidos + 1];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= portaisPermitidos; ++j)
        {
            dist[i][j] = numeric_limits<double>::max();
        }
    }

    dist[0][0] = 0;

    MinHeap pq(n * (portaisPermitidos + 1)); // capacidade inicial
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        // cout << "Visitando nó " << estadoAtual.no << " com custo " << estadoAtual.custo << " e " << estadoAtual.portaisUsados << " portais usados." << endl;

        if (estadoAtual.no == n - 1)
        {
            // Verificar se chegamos ao destino dentro da energia disponível
            if (estadoAtual.custo <= energia)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[estadoAtual.no][v] != numeric_limits<double>::max())
            {
                if (adjMatrix[estadoAtual.no][v] == 0)
                {
                    if (estadoAtual.portaisUsados < portaisPermitidos)
                    {
                        double portalCost = estadoAtual.custo; // Custo do portal é 0
                        if (portalCost < dist[v][estadoAtual.portaisUsados + 1])
                        {
                            dist[v][estadoAtual.portaisUsados + 1] = portalCost;
                            pq.push({v, portalCost + distanciaEuclidiana(coords[v], coords[n - 1]), estadoAtual.portaisUsados + 1});
                            // cout << "Atualizando nó " << v << " com novo custo " << portalCost << " através de portal." << endl;
                        }
                    }
                }
                else
                {
                    double newCost = estadoAtual.custo + adjMatrix[estadoAtual.no][v];
                    if (newCost < dist[v][estadoAtual.portaisUsados])
                    {
                        dist[v][estadoAtual.portaisUsados] = newCost;
                        pq.push({v, newCost + distanciaEuclidiana(coords[v], coords[n - 1]), estadoAtual.portaisUsados});
                        // cout << "Atualizando nó " << v << " com novo custo " << newCost << " através de trilha." << endl;
                    }
                }
            }
        }
    }

    return false;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    // cout << "Numero de vertices: " << n << ", trilhas: " << m << ", portais: " << k << endl;

    Coords coords[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> coords[i].x >> coords[i].y;
        // cout << "Coordenadas do vertice " << i << ": (" << coords[i].x << ", " << coords[i].y << ")" << endl;
    }

    GraphMatriz g(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        double peso = distanciaEuclidiana(coords[u], coords[v]);
        g.addAresta(u, v, peso);
        // cout << "Trilha de " << u << " para " << v << " com peso " << peso << endl;
    }

    for (int i = 0; i < k; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addPortal(u, v);
        // cout << "Portal de " << u << " para " << v << endl;
    }

    double s;
    int q;
    cin >> s >> q;
    // cout << "Energia: " << s << ", portais permitidos: " << q << endl
    //      << endl;

    // cout << "Dijkstra:" << endl;
    bool dijkstra_result = dijkstra(n, g.getAdjMatrix(), q, s);

    cout << endl
         << endl;

    // cout << "A estrela:" << endl;
    bool a_star_result = a_star(n, g.getAdjMatrix(), q, s, coords);

    cout << (dijkstra_result ? 1 : 0) << " " << (a_star_result ? 1 : 0) << endl;

    return 0;
}
