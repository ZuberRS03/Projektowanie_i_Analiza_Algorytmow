#ifndef GRAFY_DJIKSTRAALGORITHM_H
#define GRAFY_DJIKSTRAALGORITHM_H

#include <vector>
#include <limits>
#include "Graph.h"
#include "PriorityQueue.h"

/*
 * Klasa implementująca algorytm Dijkstry znajdowania najkrótszych ścieżek w grafie
 */
class DijkstraAlgorithm {
private:
    Graph graph; // Graf
    std::vector<int> distances; // Tablica odległości od źródła
    PriorityQueue<std::pair<int, int>> queue; // Kolejka priorytetowa (odległość, wierzchołek)

public:
    // Konstruktor
    DijkstraAlgorithm(const Graph& graph) : graph(graph) {
        distances.resize(graph.verticesCount, std::numeric_limits<int>::max()); // Inicjalizacja tablicy odległości
    }

    /*
     * @brief Znajduje najkrótsze ścieżki od zadanego źródła do pozostałych wierzchołków w grafie
     * @param source Wierzchołek źródłowy
     * @return Tablica odległości od źródła
     */
    std::vector<int> findShortestPathMatrix(int source) {
        distances[source] = 0; // Odległość od źródła do żródła wynosi 0
        queue.push(std::make_pair(0, source)); // Dodanie wierzchołka źródłowego do kolejki

        while (!queue.empty()) { // Dopóki kolejka nie jest pusta
            int u = queue.top().second; // Pobranie wierzchołka o najmniejszej odległości
            queue.pop(); // Usunięcie wierzchołka z kolejki

            // Iteracja po sąsiadach wierzchołka u
            for (int v = 0; v < graph.verticesCount; ++v) { // Dla każdego wierzchołka v
                if (graph.adjacencyMatrix[u][v] && distances[u] != std::numeric_limits<int>::max()) { // Jeśli istnieje krawędź u -> v i odległość u nie jest nieskończonością
                    int newDist = distances[u] + graph.adjacencyMatrix[u][v]; // Nowa odległość
                    if (newDist < distances[v]) { // Jeśli nowa odległość jest mniejsza od obecnej
                        distances[v] = newDist; // Zaktualizuj odległość
                        queue.push(std::make_pair(distances[v], v)); // Dodaj wierzchołek do kolejki
                    }
                }
            }
        }

        return distances; // Zwróć tablicę odległości
    }

    /*
     * @brief Znajduje najkrótsze ścieżki od zadanego źródła do pozostałych wierzchołków w grafie
     * @param source Wierzchołek źródłowy
     * @return Tablica odległości od źródła
     */
    std::vector<int> findShortestPathList(int source) {
        std::vector<int> distances(graph.verticesCount, std::numeric_limits<int>::max()); // Inicjalizacja tablicy odległości
        PriorityQueue<std::pair<int, int>> queue; // Kolejka priorytetowa (odległość, wierzchołek)

        distances[source] = 0; // Odległość od źródła do żródła wynosi 0
        queue.push(std::make_pair(0, source)); // Dodanie wierzchołka źródłowego do kolejki

        while (!queue.empty()) { // Dopóki kolejka nie jest pusta
            int u = queue.top().second; // Pobranie wierzchołka o najmniejszej odległości
            queue.pop(); // Usunięcie wierzchołka z kolejki

            for (const auto& neighbor : graph.adjacencyList[u]) { // Dla każdego sąsiada wierzchołka u
                int v = neighbor.first; // Numer wierzchołka
                int weight = neighbor.second; // Waga krawędzi
                int newDist = distances[u] + weight; // Nowa odległość
                if (newDist < distances[v]) { // Jeśli nowa odległość jest mniejsza od obecnej
                    distances[v] = newDist; // Zaktualizuj odległość
                    queue.push(std::make_pair(distances[v], v)); // Dodaj wierzchołek do kolejki
                }
            }
        }

        return distances; // Zwróć tablicę odległości
    }

};

#endif //GRAFY_DJIKSTRAALGORITHM_H
