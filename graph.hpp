#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <limits>

const int INF = std::numeric_limits<int>::max();

// Estrutura para representar uma aresta
struct Edge {
    int to;
    int weight;
};

class Graph {
public:
    Graph(int numVertices);
    void addEdge(int from, int to, int weight);
    const std::vector<Edge>& getAdjList(int vertex) const;
    int getNumVertices() const;

private:
    int numVertices;
    std::vector<std::vector<Edge>> adjList;
};

#endif
