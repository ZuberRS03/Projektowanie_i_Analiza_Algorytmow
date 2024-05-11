#include <iostream>
#include <chrono>
#include <fstream> //do wczytywania i zapisywania plików
#include "Graph.h"
#include "DjikstraAlgorithm.h"

std::ifstream fin;
std::ofstream fout;

int wyborGestosci(){
    while(true) {
        std::cout << "Wybierz gęstosc: " << std::endl;
        std::cout << "1. 25%" << std::endl;
        std::cout << "2. 50%" << std::endl;
        std::cout << "3. 75%" << std::endl;
        std::cout << std::endl;
        int wybor;
        std::cout << "Wybor: ";
        std::cin >> wybor;

        if (wybor == 1) {
            return 25;
        } else if (wybor == 2) {
            return 50;
        } else if (wybor == 3) {
            return 75;
        } else {
            std::cout << "Niepoprawnny wybor, wybierz 1, 2 lub 3." << std::endl;
            std::cout << std::endl;
        }
    }
}
int main() {
// Utworzenie i wygenerowanie grafu
    int vertices = 5; // liczba wierzchołków
    int density = 25; // gęstość grafu w procentach
    int weightRange = 10; // zakres wag krawędzi
    int startVertex = 0; // wierzchołek startowy

    //density = wyborGestosci();

    int czyPrezentacja;
    std::cout << "Czy prezentacja? (tak - 1 / nie - 0): " << std::endl;
    std::cin >> czyPrezentacja;

    if(czyPrezentacja == 1){
        Graph g(vertices);
        g.generateGraph(vertices, density, weightRange); // Generowanie grafu

        // Wypisanie wygenerowanego grafu jako macierzy sąsiedztwa
        std::cout << "Macierz sasiedztwa:" << std::endl;
        std::cout << std::endl;
        g.printMatrix();

        std::cout << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << std::endl;

        // Wypisanie wygenerowanego grafu jako listy sąsiedztwa
        std::cout << "Lista sasiedztwa:" << std::endl;
        std::cout << std::endl;
        g.printAdjacencyList();
        std::cout << std::endl;

        // Uruchomienie algorytmu Dijkstry i wyświetlenie wyników dla macierzy sąsiedztwa
        DijkstraAlgorithm dijkstra(g);
        auto startMatrix = std::chrono::high_resolution_clock::now();
        std::vector<int> shortestPathsMatrix = dijkstra.findShortestPathMatrix(startVertex);
        auto endMatrix = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> durationMatrix = endMatrix - startMatrix;

        std::cout << "Najkrotsze sciezki (macierz):" << std::endl;
        for (int i = 0; i < shortestPathsMatrix.size(); ++i) {
            std::cout << startVertex << " -> " << i << ": " << shortestPathsMatrix[i] << std::endl;
        }

        // Uruchomienie algorytmu Dijkstry i wyświetlenie wyników dla listy sąsiedztwa
        auto startList = std::chrono::high_resolution_clock::now();
        std::vector<int> shortestPathsList = dijkstra.findShortestPathList(startVertex);
        auto endList = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> durationList = endList - startList;

        std::cout << "Najkrotsze sciezki (lista):" << std::endl;
        for (int i = 0; i < shortestPathsList.size(); ++i) {
            std::cout << startVertex << " -> " << i << ": " << shortestPathsList[i] << std::endl;
        }

        // Porównanie czasów wykonania
        std::cout << "Czas wykonania algorytmu Dijkstry (macierz): " << durationMatrix.count() << " ms" << std::endl;
        std::cout << "Czas wykonania algorytmu Dijkstry (lista): " << durationList.count() << " ms" << std::endl;

    } else if (czyPrezentacja == 0){
        fout.open("wyniki.csv");
        density = 25;
        weightRange = 1000;
        fout <<"gestosc_grafu" << ";" << "ilosc_wierzchołkow" << ";" << "srednia_czasu_dla_macierzy" << ";" << "srednia_czasu_dla_listy" << std::endl;
        while(density <= 100){
            vertices = 10;
            while(vertices <= 1000){
                float aveageMatrix = 0;
                float aveageList = 0;

                for(int i = 0; i < 100; i++){
                    Graph g(vertices);
                    g.generateGraph(vertices, density, weightRange); // Generowanie grafu

                    // Uruchomienie algorytmu Dijkstry dla macierzy sąsiedztwa
                    DijkstraAlgorithm dijkstra(g);
                    auto startMatrix = std::chrono::high_resolution_clock::now();
                    std::vector<int> shortestPathsMatrix = dijkstra.findShortestPathMatrix(startVertex);
                    auto endMatrix = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> durationMatrix = endMatrix - startMatrix;

                    // Uruchomienie algorytmu Dijkstry dla listy sąsiedztwa
                    auto startList = std::chrono::high_resolution_clock::now();
                    std::vector<int> shortestPathsList = dijkstra.findShortestPathList(startVertex);
                    auto endList = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> durationList = endList - startList;

                    aveageMatrix += durationMatrix.count();
                    aveageList += durationList.count();
                }
                aveageMatrix = aveageMatrix / 100;
                aveageList = aveageList / 100;

                fout << density << ";" << vertices << ";" << aveageMatrix << ";" << aveageList << std::endl;
                switch(vertices){
                    case 10: {
                        vertices = 50;
                        break;
                    }
                    case 50: {
                        vertices = 100;
                        break;
                    }
                    case 100: {
                        vertices = 500;
                        break;
                    }
                    case 500: {
                        vertices = 1000;
                        break;
                    }
                    case 1000: {
                        vertices = 1001; //wyjscie z petli
                        break;
                    }
                }
            }
            density = density + 25;
        }


        fout.close();
    } else {
        std::cout << "Niepoprawna odpowiedz" << std::endl;
        return 0;
    }

    return 0;
}
