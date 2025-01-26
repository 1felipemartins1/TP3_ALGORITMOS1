
#include "graph.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <tuple>
Graph::Graph(int V) : adj(V) {}


std::vector<std::tuple<int, int, int>> Graph::conexoesCriticas(int source, int sink) {
    std::vector<std::tuple<int, int, int>> criticas;

    for (size_t u = 0; u < adj.size(); ++u) {
        for (const auto& edge : adj[u]) {
            // Verifica se a conexão está operando no limite
            if (edge.flow == edge.capacity && edge.capacity > 0) {
                // Ignorar conexões que terminam no sumidouro fictício (sink)
                if (static_cast<int>(u) == source || edge.to == sink) {
                    continue;
                }
                criticas.emplace_back(u, edge.to, edge.capacity);
            }
        }
    }

    // Ordena as conexões críticas em ordem decrescente de capacidade usando Bubble Sort
    for (size_t i = 0; i < criticas.size(); ++i) {
        for (size_t j = 0; j < criticas.size() - i - 1; ++j) {
            if (std::get<2>(criticas[j]) < std::get<2>(criticas[j + 1])) { // Comparação pelo terceiro elemento
                // Troca as tuplas
                auto temp = criticas[j];
                criticas[j] = criticas[j + 1];
                criticas[j + 1] = temp;
            }
        }
    }

    return criticas;
}


void Graph::addEdge(int from, int to, int capacity)
{
    Edge forward = {to, capacity, 0, (int)adj[to].size()};
    Edge backward = {from, 0, 0, (int)adj[from].size()};
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}

int Graph::energia_nao_atendida(int source) {
    int totalFluxoSaindo = 0;

    // Calcula o fluxo total saindo da fonte
    for (const auto& edge : adj[source]) {
        totalFluxoSaindo += edge.flow;
    }
    // Retorna a diferença
    return totalFluxoSaindo;
}

bool Graph::bfs(std::vector<int> &parent, std::vector<int> &edgeIndex, int source, int sink)
{
    int V = static_cast<int>(adj.size());
    std::vector<bool> visited(V, false);
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < static_cast<int>(adj[u].size()); i++)
        {
            {
                Edge &e = adj[u][i];
                if (!visited[e.to] && e.flow < e.capacity)
                {
                    parent[e.to] = u;
                    edgeIndex[e.to] = i;
                    visited[e.to] = true;
                    q.push(e.to);

                    if (e.to == sink)
                        return true;
                }
            }
        }
    }
    return false;
}

int Graph::maxFlow(int source, int sink)
{
    int maxFlow = 0;
    std::vector<int> parent(adj.size());
    std::vector<int> edgeIndex(adj.size());

    while (bfs(parent, edgeIndex, source, sink))
    {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            int i = edgeIndex[v];
            pathFlow = std::min(pathFlow, adj[u][i].capacity - adj[u][i].flow);
        }

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            int i = edgeIndex[v];
            adj[u][i].flow += pathFlow;
            adj[v][adj[u][i].reverseIndex].flow -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int Graph::energiaPerdida(int source) {
    int energiaGerada = 0;

    // Itera sobre a lista de adjacência da fonte fictícia para identificar os geradores
    for (const auto& edge : adj[source]) {
        int gerador = edge.to; // ID do gerador

        // Itera sobre as arestas do gerador para calcular a capacidade total das conexões
        for (const auto& conexao : adj[gerador]) {
            energiaGerada += conexao.capacity;
        }
    }

    // Retorna a energia perdida
    return energiaGerada;
}