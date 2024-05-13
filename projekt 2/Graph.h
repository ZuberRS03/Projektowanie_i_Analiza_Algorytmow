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

    /*
     * @brief Dodaje krawędź między wierzchołkami u i v o zadanej wadze
     * @param u Pierwszy wierzchołek krawędzi
     * @param v Drugi wierzchołek krawędzi
     * @param weight Waga krawędzi
     * @return void
     */
    void addEdge(int u, int v, int weight);

    /*
     * @brief Generuje graf o zadanej liczbie wierzchołków, gęstości i zakresie wag
     * @param verticesCount Liczba wierzchołków w grafie
     * @param density Gęstość grafu w procentach
     * @param weightRange Zakres wag krawędzi
     * @return void
     */
    void generateGraph(int verticesCount, int density, int weightRange);

    /*
     * @brief Wypisuje macierz sąsiedztwa grafu
     * @return void
     */
    void printMatrix();

    /*
     * @brief Wypisuje listę sąsiedztwa grafu
     * @return void
     */
    void printAdjacencyList();

    // Umożliwia klasie DijkstraAlgorithm dostęp do prywatnych składników klasy Graph
    friend class DijkstraAlgorithm;
};

#endif //GRAFY_GRAPH_H
