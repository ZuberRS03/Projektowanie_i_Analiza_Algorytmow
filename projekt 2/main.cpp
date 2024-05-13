#include <iostream> //do obsługi strumieni wejścia/wyjścia
#include <chrono> //do mierzenia czasu
#include <fstream> //do wczytywania i zapisywania plików
#include "Graph.h"
#include "DjikstraAlgorithm.h"

std::ifstream fin;
std::ofstream fout;

int main() {
// Utworzenie i wygenerowanie grafu
    int vertices = 5; // liczba wierzchołków
    int density = 25; // gęstość grafu w procentach
    int weightRange = 10; // zakres wag krawędzi
    int startVertex = 0; // wierzchołek startowy

    int czyPrezentacja;
    std::cout << "Czy prezentacja? (tak - 1 / nie - 0): " << std::endl;
    std::cin >> czyPrezentacja;

    if(czyPrezentacja == 1){
        Graph g(vertices); // Tworzenie grafu
        g.generateGraph(vertices, density, weightRange); // Generowanie grafu

        // Wypisanie wygenerowanego grafu jako macierzy sąsiedztwa
        std::cout << "Macierz sasiedztwa:" << std::endl;
        std::cout << std::endl;
        g.printMatrix(); // Wypisanie macierzy sąsiedztwa

        std::cout << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << std::endl;

        // Wypisanie wygenerowanego grafu jako listy sąsiedztwa
        std::cout << "Lista sasiedztwa:" << std::endl;
        std::cout << std::endl;
        g.printAdjacencyList(); // Wypisanie listy sąsiedztwa
        std::cout << std::endl;

        // Uruchomienie algorytmu Dijkstry i wyświetlenie wyników dla macierzy sąsiedztwa
        DijkstraAlgorithm dijkstra(g); // Inicjalizacja algorytmu Dijkstry
        auto startMatrix = std::chrono::high_resolution_clock::now(); // Początek mierzenia czasu
        std::vector<int> shortestPathsMatrix = dijkstra.findShortestPathMatrix(startVertex); // Uruchomienie algorytmu Dijkstry
        auto endMatrix = std::chrono::high_resolution_clock::now(); // Koniec mierzenia czasu
        std::chrono::duration<double, std::milli> durationMatrix = endMatrix - startMatrix; // Obliczenie czasu wykonania

        // Wypisanie najkrótszych ścieżek dla macierzy sąsiedztwa
        std::cout << "Najkrotsze sciezki (macierz):" << std::endl;
        for (int i = 0; i < shortestPathsMatrix.size(); ++i) {
            std::cout << startVertex << " -> " << i << ": " << shortestPathsMatrix[i] << std::endl;
        }

        // Uruchomienie algorytmu Dijkstry i wyświetlenie wyników dla listy sąsiedztwa
        auto startList = std::chrono::high_resolution_clock::now(); // Początek mierzenia czasu
        std::vector<int> shortestPathsList = dijkstra.findShortestPathList(startVertex); // Uruchomienie algorytmu Dijkstry
        auto endList = std::chrono::high_resolution_clock::now(); // Koniec mierzenia czasu
        std::chrono::duration<double, std::milli> durationList = endList - startList; // Obliczenie czasu wykonania

        // Wypisanie najkrótszych ścieżek dla listy sąsiedztwa
        std::cout << "Najkrotsze sciezki (lista):" << std::endl;
        for (int i = 0; i < shortestPathsList.size(); ++i) {
            std::cout << startVertex << " -> " << i << ": " << shortestPathsList[i] << std::endl;
        }

        // Porównanie czasów wykonania
        std::cout << "Czas wykonania algorytmu Dijkstry (macierz): " << durationMatrix.count() << " ms" << std::endl;
        std::cout << "Czas wykonania algorytmu Dijkstry (lista): " << durationList.count() << " ms" << std::endl;

    } else if (czyPrezentacja == 0){
        fout.open("wyniki.csv"); // Otwarcie pliku do zapisu wyników
        density = 25; // gęstość grafu w procentach
        weightRange = 1000; // zakres wag krawędzi
        fout <<"gestosc_grafu" << ";" << "ilosc_wierzchołkow" << ";" << "srednia_czasu_dla_macierzy" << ";" << "srednia_czasu_dla_listy" << std::endl;
        while(density <= 100){ // Pętla do gęstościach grafu
            vertices = 10;
            while(vertices <= 1000){ // Pętla do liczby wierzchołków
                float aveageMatrix = 0;
                float aveageList = 0;

                for(int i = 0; i < 100; i++){ // Pętla do 100 prób
                    Graph g(vertices); // Tworzenie grafu
                    g.generateGraph(vertices, density, weightRange); // Generowanie grafu

                    // Uruchomienie algorytmu Dijkstry dla macierzy sąsiedztwa
                    DijkstraAlgorithm dijkstra(g); // Inicjalizacja algorytmu Dijkstry
                    auto startMatrix = std::chrono::high_resolution_clock::now(); // Początek mierzenia czasu
                    std::vector<int> shortestPathsMatrix = dijkstra.findShortestPathMatrix(startVertex); // Uruchomienie algorytmu Dijkstry
                    auto endMatrix = std::chrono::high_resolution_clock::now(); // Koniec mierzenia czasu
                    std::chrono::duration<double, std::milli> durationMatrix = endMatrix - startMatrix; // Obliczenie czasu wykonania

                    // Uruchomienie algorytmu Dijkstry dla listy sąsiedztwa
                    auto startList = std::chrono::high_resolution_clock::now(); // Początek mierzenia czasu
                    std::vector<int> shortestPathsList = dijkstra.findShortestPathList(startVertex); // Uruchomienie algorytmu Dijkstry
                    auto endList = std::chrono::high_resolution_clock::now(); // Koniec mierzenia czasu
                    std::chrono::duration<double, std::milli> durationList = endList - startList; // Obliczenie czasu wykonania

                    aveageMatrix += durationMatrix.count(); // Dodanie czasu wykonania do sumy
                    aveageList += durationList.count(); // Dodanie czasu wykonania do sumy
                }
                aveageMatrix = aveageMatrix / 100; // Obliczenie średniego czasu wykonania
                aveageList = aveageList / 100; // Obliczenie średniego czasu wykonania

                // Zapisanie wyników do pliku
                fout << density << ";" << vertices << ";" << aveageMatrix << ";" << aveageList << std::endl;

                switch(vertices){ // Zwiększenie liczby wierzchołków
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
            density = density + 25; // Zwiększenie gęstości grafu
        }

        fout.close();
    } else {
        std::cout << "Niepoprawna odpowiedz" << std::endl;
        return 0;
    }

    return 0;
}
