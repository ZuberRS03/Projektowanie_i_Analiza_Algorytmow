#ifndef GRAFY_GRAPH_H
#define GRAFY_GRAPH_H

#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <list>

/*
 * Klasa reprezentująca graf nieskierowany w postaci macierzy sąsiedztwa
 * Wierzchołki grafu są numerowane od 0 do verticesCount - 1
 * Krawędzie są ważone, wagi krawędzi są liczbami całkowitymi
 * Graf nie zawiera pętli (krawędzi z wierzchołka do samego siebie)
 * Graf nie zawiera wielokrotnych krawędzi między dwoma wierzchołkami
 */
class Graph {
private:
    std::vector<std::vector<int>> adjacencyMatrix; // Macierz sąsiedztwa
    std::vector<std::list<std::pair<int, int>>> adjacencyList; // Lista sąsiedztwa
    int verticesCount; // Liczba wierzchołków w grafie

public:
    // Konstruktor grafu o zadanej liczbie wierzchołków
    Graph(int vertices) : verticesCount(vertices) {
        adjacencyMatrix.resize(verticesCount, std::vector<int>(verticesCount, 0)); // Macierz wypełniona zerami
        adjacencyList.resize(verticesCount); // Lista sąsiedztwa wypełniona pustymi listami
    }

    // Dodanie krawędzi do grafu
    // Uwzględniając graf nieskierowany, dodaje krawędzie w obu kierunkach
    void addEdge(int u, int v, int weight) {
        // Dodanie do macierzy sąsiedztwa
        if(u >= 0 && u < verticesCount && v >= 0 && v < verticesCount) {
            adjacencyMatrix[u][v] = weight;
            adjacencyMatrix[v][u] = weight;
        }

        // Dodanie do listy sąsiedztwa
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    // Generator losowego grafu
    void generateGraph(int verticesCount, int density, int weightRange) {
        // Inicjalizacja generatora liczb pseudolosowych
        std::random_device rd;
        std::mt19937 gen(rd());

        // Resetujemy macierz sąsiedztwa
        adjacencyMatrix.assign(verticesCount, std::vector<int>(verticesCount, 0));

        // Najpierw tworzymy szkielet grafu gwarantujący spójność (drzewo rozpinające)
        for (int i = 1; i < verticesCount; ++i) {
            int weight = std::uniform_int_distribution<>(1, weightRange)(gen);
            int j = std::uniform_int_distribution<>(0, i - 1)(gen); // łączymy z losowym wcześniejszym wierzchołkiem
            addEdge(i, j, weight);
        }

        // Obliczamy ile krawędzi należy jeszcze dodać, aby osiągnąć zadaną gęstość
        int existingEdges = verticesCount - 1; // liczba krawędzi w drzewie rozpinającym
        int maxEdges = verticesCount * (verticesCount - 1) / 2;
        int desiredEdges = static_cast<int>(density / 100.0 * maxEdges);
        int additionalEdges = desiredEdges - existingEdges;

        // Tworzymy pulę wszystkich możliwych krawędzi, które nie są częścią drzewa rozpinającego
        std::vector<std::pair<int, int>> potentialEdges;
        for (int i = 0; i < verticesCount; ++i) {
            for (int j = i + 1; j < verticesCount; ++j) {
                if (adjacencyMatrix[i][j] == 0) { // tylko jeśli krawędź nie istnieje
                    potentialEdges.emplace_back(i, j);
                }
            }
        }

        // Mieszamy i dodajemy odpowiednią liczbę dodatkowych krawędzi
        std::shuffle(potentialEdges.begin(), potentialEdges.end(), gen);
        for (int i = 0; i < additionalEdges && i < potentialEdges.size(); ++i) {
            int weight = std::uniform_int_distribution<>(1, weightRange)(gen);
            addEdge(potentialEdges[i].first, potentialEdges[i].second, weight);
        }
    }

    // Wyświetla macierz sąsiedztwa grafu
    void printMatrix() {
        for (const auto &row : adjacencyMatrix) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    // Wyświetla listę sąsiedztwa grafu
    void printAdjacencyList() {
        for (int i = 0; i < verticesCount; ++i) {
            std::cout << "Sasiedzi wierzcholka " << i << ": ";
            for (const auto& pair : adjacencyList[i]) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    // Umożliwia klasie DijkstraAlgorithm dostęp do prywatnych składników klasy Graph
    friend class DijkstraAlgorithm;
};

#endif //GRAFY_GRAPH_H
