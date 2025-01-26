#include <iostream>
#include <tuple>
#include "graph.hpp"

using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;
    int capacidade_total_gerador = 0;

    Graph graph(V + 2); // Inclui fonte e consumidor
    int source = V;     // Fonte fictícia
    int sink = V + 1;   // consumidor fictício

    for (int i = 0; i < V; i++)
    {
        int id, type;
        cin >> id >> type;

        if (type == 0)
        { // Gerador
            graph.addEdge(source, id - 1, INT_MAX);
        }
        else
        { // Consumidor
            /*
            Vi que a parte 2.2 era só de pegar o somatório da capacidade máxima que cada consumidor
            e subtrair pelo fluxo total, até pensei em fazer uma função que calcula isso, mas poxa,
            é tão mais fácil e efetivo fazer dessa forma, mas mesmo assim, criei a função, apesar de não
            utiliza-la
            */
            capacidade_total_gerador += type;
            graph.addEdge(id - 1, sink, type);
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        graph.addEdge(u - 1, v - 1, c);
    }
    int fluxo_maximo = graph.maxFlow(source, sink);
    cout << fluxo_maximo << endl;
    int energia_nao_atendida = capacidade_total_gerador - fluxo_maximo;
    cout << energia_nao_atendida << endl;
    // cout <<graph.energiaPerdida(source) - fluxo_maximo << endl;
    // cout << graph.energiaPerdida(source, sink) << endl;
    // cout << graph.energiaPerdida(source, sink) << endl;
    int energia_perdida = graph.energiaPerdida(source);
    cout << energia_perdida - fluxo_maximo << endl;

    // Imprimir as conexões críticas
    auto criticas = graph.conexoesCriticas(source, sink);
    cout << criticas.size() << endl; // Número de conexões críticas
    for (const auto &critica : criticas)
    {
        int u, v, capacity;
        std::tie(u, v, capacity) = critica;                       // Descompacta a tupla
        cout << u + 1 << " " << v + 1 << " " << capacity << endl; // IDs das conexões críticas
    }

    return 0;
}