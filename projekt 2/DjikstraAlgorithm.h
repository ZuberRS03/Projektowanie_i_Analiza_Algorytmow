#ifndef GRAFY_DJIKSTRAALGORITHM_H
#define GRAFY_DJIKSTRAALGORITHM_H

#include <vector>
#include <limits>
#include "Graph.h"
#include "PriorityQueue.h"

class DijkstraAlgorithm {
private:
    Graph graph;
    std::vector<int> distances;
    PriorityQueue<std::pair<int, int>> queue; // Kolejka priorytetowa (odległość, wierzchołek)

public:
    DijkstraAlgorithm(const Graph& graph) : graph(graph) {
        distances.resize(graph.verticesCount, std::numeric_limits<int>::max());
    }

    std::vector<int> findShortestPathMatrix(int source) {
        distances[source] = 0;
        queue.push(std::make_pair(0, source));

        while (!queue.empty()) {
            int u = queue.top().second;
            queue.pop();

            // Iteracja po sąsiadach wierzchołka u
            for (int v = 0; v < graph.verticesCount; ++v) {
                if (graph.adjacencyMatrix[u][v] && distances[u] != std::numeric_limits<int>::max()) {
                    int newDist = distances[u] + graph.adjacencyMatrix[u][v];
                    if (newDist < distances[v]) {
                        distances[v] = newDist;
                        queue.push(std::make_pair(distances[v], v));
                    }
                }
            }
        }

        return distances;
    }

    std::vector<int> findShortestPathList(int source) {
        std::vector<int> distances(graph.verticesCount, std::numeric_limits<int>::max());
        PriorityQueue<std::pair<int, int>> queue;

        distances[source] = 0;
        queue.push(std::make_pair(0, source));

        while (!queue.empty()) {
            int u = queue.top().second;
            queue.pop();

            for (const auto& neighbor : graph.adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                int newDist = distances[u] + weight;
                if (newDist < distances[v]) {
                    distances[v] = newDist;
                    queue.push(std::make_pair(distances[v], v));
                }
            }
        }

        return distances;
    }

};

#endif //GRAFY_DJIKSTRAALGORITHM_H
