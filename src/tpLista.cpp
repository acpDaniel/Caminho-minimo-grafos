#include <iostream>
#include <cmath>
#include <limits>
#include "../include/listaAdjGrafo.hpp"
#include "../include/minHeap.hpp"

using namespace std;

double distanciaEuclidiana(Coords a, Coords b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool dijkstra(GraphList &grafo, int portaisPermitidos, double energia)
{
    int numVertices = grafo.getNumVertices();
    Aresta **adj = grafo.getAdjList();
    double dist[numVertices][portaisPermitidos + 1];
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j <= portaisPermitidos; ++j)
        {
            dist[i][j] = numeric_limits<double>::max();
        }
    }

    dist[0][0] = 0;

    MinHeap pq(numVertices * (portaisPermitidos + 1)); // capacidade inicial
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        // cout << "Visitando nó " << estadoAtual.no << " com custo " << estadoAtual.custo << " e " << estadoAtual.portaisUsados << " portais usados." << endl;

        // Queremos sempre chegar no vértice numVertices - 1
        if (estadoAtual.no == numVertices - 1 && estadoAtual.custo <= energia)
        {
            return true;
        }

        if (estadoAtual.custo > dist[estadoAtual.no][estadoAtual.portaisUsados])
        {
            continue;
        }

        for (Aresta *aresta = adj[estadoAtual.no]; aresta; aresta = aresta->prox)
        {
            if (aresta->peso == 0)
            {
                if (estadoAtual.portaisUsados < portaisPermitidos)
                {
                    double portalCost = estadoAtual.custo; // Custo do portal é 0
                    // cout << "Calculando novo custo para portal: " << portalCost << " (atual: " << estadoAtual.custo << ")" << endl;
                    if (portalCost < dist[aresta->verticeDest][estadoAtual.portaisUsados + 1])
                    {
                        dist[aresta->verticeDest][estadoAtual.portaisUsados + 1] = portalCost;
                        pq.push({aresta->verticeDest, portalCost, estadoAtual.portaisUsados + 1});
                        // cout << "Atualizando nó " << aresta->verticeDest << " com novo custo " << portalCost << " através de portal." << endl;
                    }
                }
            }
            else
            {
                double newCost = estadoAtual.custo + aresta->peso;
                // cout << "Calculando novo custo para trilha: " << newCost << " (atual: " << estadoAtual.custo << " + peso: " << aresta->peso << ")" << endl;
                if (newCost < dist[aresta->verticeDest][estadoAtual.portaisUsados])
                {
                    dist[aresta->verticeDest][estadoAtual.portaisUsados] = newCost;
                    pq.push({aresta->verticeDest, newCost, estadoAtual.portaisUsados});
                    // cout << "Atualizando nó " << aresta->verticeDest << " com novo custo " << newCost << " através de trilha." << endl;
                }
            }
        }
    }

    return false;
}

bool a_star(GraphList &grafo, int portaisPermitidos, double energia, Coords *coords)
{
    int numVertices = grafo.getNumVertices();
    Aresta **adj = grafo.getAdjList();
    double dist[numVertices][portaisPermitidos + 1];

    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j <= portaisPermitidos; ++j)
        {
            dist[i][j] = numeric_limits<double>::max();
        }
    }

    dist[0][0] = 0;

    MinHeap pq(numVertices * (portaisPermitidos + 1)); // capacidade inicial
    double prioridadeInicial = distanciaEuclidiana(coords[0], coords[numVertices - 1]);
    pq.push({0, 0, 0}); // Inserindo o estado inicial com prioridade inicial

    while (!pq.empty())
    {
        State estadoAtual = pq.top();
        pq.pop();

        cout << "Visitando nó " << estadoAtual.no << " com custo " << estadoAtual.custo << " e " << estadoAtual.portaisUsados << " portais usados." << endl;

        if (estadoAtual.no == numVertices - 1)
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

        for (Aresta *aresta = adj[estadoAtual.no]; aresta; aresta = aresta->prox)
        {
            if (aresta->peso == 0)
            { // Portal
                if (estadoAtual.portaisUsados < portaisPermitidos)
                {
                    double portalCost = estadoAtual.custo; // Custo do portal é 0
                    if (portalCost < dist[aresta->verticeDest][estadoAtual.portaisUsados + 1])
                    {
                        dist[aresta->verticeDest][estadoAtual.portaisUsados + 1] = portalCost;
                        double valorComHeuristica = portalCost + distanciaEuclidiana(coords[aresta->verticeDest], coords[numVertices - 1]);
                        pq.push({aresta->verticeDest, valorComHeuristica, estadoAtual.portaisUsados + 1});
                        // cout << "Atualizando nó " << aresta->verticeDest << " com novo custo " << portalCost << " através de portal." << endl;
                    }
                }
            }
            else
            { // Trilha
                double newCost = estadoAtual.custo + aresta->peso;
                if (newCost < dist[aresta->verticeDest][estadoAtual.portaisUsados])
                {
                    dist[aresta->verticeDest][estadoAtual.portaisUsados] = newCost;
                    double valorComHeuristica = newCost + distanciaEuclidiana(coords[aresta->verticeDest], coords[numVertices - 1]);
                    pq.push({aresta->verticeDest, valorComHeuristica, estadoAtual.portaisUsados});
                    // cout << "Atualizando nó " << aresta->verticeDest << " com novo custo " << newCost << " através de trilha." << endl;
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

    cout << "Numero de vertices: " << n << ", trilhas: " << m << ", portais: " << k << endl;

    Coords coords[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> coords[i].x >> coords[i].y;
        cout << "Coordenadas do vertice " << i << ": (" << coords[i].x << ", " << coords[i].y << ")" << endl;
    }

    GraphList g(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        double peso = distanciaEuclidiana(coords[u], coords[v]);
        g.addAresta(u, v, peso);
        cout << "Trilha de " << u << " para " << v << " com peso " << peso << endl;
    }

    for (int i = 0; i < k; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.addPortal(u, v);
        cout << "Portal de " << u << " para " << v << endl;
    }

    double s;
    int q;
    cin >> s >> q;
    cout << "Energia: " << s << ", portais permitidos: " << q << endl
         << endl;

    // cout << "Dijkstra:" << endl;
    // bool dijkstra_result = dijkstra(g, q, s);

    // cout << endl
    //<< endl;

    // cout << "A estrela:" << endl;
    bool a_star_result = a_star(g, q, s, coords);

    cout << " " << (a_star_result ? 1 : 0) << endl; //(dijkstra_result ? 1 : 0)

    return 0;
}
