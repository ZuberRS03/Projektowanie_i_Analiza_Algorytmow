# include "Graph.h"

void Graph::addEdge(int u, int v, int weight) {

    // Dodanie do macierzy sąsiedztwa
    if(u >= 0 && u < verticesCount && v >= 0 && v < verticesCount) {
        adjacencyMatrix[u][v] = weight; // krawędź u -> v
        adjacencyMatrix[v][u] = weight; // krawędź v -> u
    }

    // Dodanie do listy sąsiedztwa
    adjacencyList[u].push_back(std::make_pair(v, weight)); // krawędź u -> v
    adjacencyList[v].push_back(std::make_pair(u, weight)); // krawędź v -> u

}

void Graph::generateGraph(int verticesCount, int density, int weightRange) {
    // Inicjalizacja generatora liczb pseudolosowych
    std::random_device rd; // generator liczb losowych
    std::mt19937 gen(rd()); // silnik losujący

    // Resetujemy macierz sąsiedztwa
    adjacencyMatrix.assign(verticesCount, std::vector<int>(verticesCount, 0)); // Macierz wypełniona zerami

    // Najpierw tworzymy szkielet grafu gwarantujący spójność (drzewo rozpinające)
    for (int i = 1; i < verticesCount; ++i) { // łączymy wierzchołki 1, 2, ..., n-1 z losowym wcześniejszym wierzchołkiem
        int weight = std::uniform_int_distribution<>(1, weightRange)(gen); // losowa waga krawędzi
        int j = std::uniform_int_distribution<>(0, i - 1)(gen); // łączymy z losowym wcześniejszym wierzchołkiem
        addEdge(i, j, weight); // dodajemy krawędź między wierzchołkami i i j
    }

    // Obliczamy ile krawędzi należy jeszcze dodać, aby osiągnąć zadaną gęstość
    int existingEdges = verticesCount - 1; // liczba krawędzi w drzewie rozpinającym
    int maxEdges = verticesCount * (verticesCount - 1) / 2; // maksymalna liczba krawędzi w grafie pełnym
    int desiredEdges = static_cast<int>(density / 100.0 * maxEdges); // docelowa liczba krawędzi
    int additionalEdges = desiredEdges - existingEdges; // liczba krawędzi do dodania

    // Tworzymy pulę wszystkich możliwych krawędzi, które nie są częścią drzewa rozpinającego
    std::vector<std::pair<int, int>> potentialEdges; // potencjalne krawędzie do dodania
    for (int i = 0; i < verticesCount; ++i) { // dla każdej pary wierzchołków
        for (int j = i + 1; j < verticesCount; ++j) { // tylko dla par (i, j) z i < j
            if (adjacencyMatrix[i][j] == 0) { // tylko jeśli krawędź nie istnieje
                potentialEdges.emplace_back(i, j); // dodajemy krawędź (i, j) do puli
            }
        }
    }

    // Mieszamy i dodajemy odpowiednią liczbę dodatkowych krawędzi
    std::shuffle(potentialEdges.begin(), potentialEdges.end(), gen); // tasujemy potencjalne krawędzie
    for (int i = 0; i < additionalEdges && i < potentialEdges.size(); ++i) { // dodajemy krawędzie
        int weight = std::uniform_int_distribution<>(1, weightRange)(gen); // losowa waga krawędzi
        addEdge(potentialEdges[i].first, potentialEdges[i].second, weight); // dodajemy krawędź między wierzchołkami i i j
    }
}

void Graph::printMatrix() {
    for (const auto &row : adjacencyMatrix) { // dla każdego wiersza macierzy
        for (int val : row) { // dla każdej komórki w wierszu
            std::cout << val << " "; // wypisz wartość komórki
        }
        std::cout << std::endl; // przejdź do nowej linii
    }
}

void Graph::printAdjacencyList() {
    for (int i = 0; i < verticesCount; ++i) { // dla każdego wierzchołka
        std::cout << "Sasiedzi wierzcholka " << i << ": "; // wypisz informację o wierzchołku
        for (const auto& pair : adjacencyList[i]) { // dla każdego sąsiada wierzchołka
            std::cout << "(" << pair.first << ", " << pair.second << ") "; // wypisz sąsiada
        }
        std::cout << std::endl; // przejdź do nowej linii
    }
}
