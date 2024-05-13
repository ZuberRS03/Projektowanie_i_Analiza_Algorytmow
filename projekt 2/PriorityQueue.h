#ifndef GRAFY_PRIORITYQUEUE_H
#define GRAFY_PRIORITYQUEUE_H

#include <queue>
#include <vector>
#include <stdexcept>

/*
 * Klasa reprezentująca kolejkę priorytetową
 * Kolejka priorytetowa jest implementowana za pomocą kopca
 * Klasa jest generyczna, to znaczy może przechowywać elementy dowolnego typu T
 */
template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
private:
    std::vector<T> heap; // Kopiec
    Comparator comp; // Obiekt porównujący elementy

    /*
     * @brief Przywraca własność kopca dla węzła o zadanym indeksie
     * @param idx Indeks węzła
     * @return void
     */
    void heapify(int idx) {
        int size = heap.size(); // Rozmiar kopca
        int left = 2 * idx + 1; // Indeks lewego dziecka
        int right = 2 * idx + 2; // Indeks prawego dziecka
        int smallest = idx; // Indeks najmniejszego elementu

        if (left < size && comp(heap[left], heap[idx])) // Jeśli lewe dziecko jest mniejsze od rodzica
            smallest = left; // Najmniejszy element to lewe dziecko
        if (right < size && comp(heap[right], heap[smallest])) // Jeśli prawe dziecko jest mniejsze od najmniejszego elementu
            smallest = right; // Najmniejszy element to prawe dziecko

        if (smallest != idx) { // Jeśli najmniejszy element nie jest korzeniem
            std::swap(heap[idx], heap[smallest]); // Zamień miejscami rodzica z najmniejszym elementem
            heapify(smallest); // Rekurencyjnie wywołaj heapify dla najmniejszego elementu
        }
    }

public:
    // Konstruktor
    PriorityQueue() {}

    /*
     * @brief Dodaje element do kolejki
     * @param value Wartość elementu
     * @return void
     */
    void push(const T& value) {
        heap.push_back(value); // Dodaj element na koniec kopca
        int i = heap.size() - 1; // Indeks dodanego elementu
        while (i != 0 && comp(heap[i], heap[(i - 1) / 2])) { // Dopóki element nie jest korzeniem i jest mniejszy od rodzica
            std::swap(heap[i], heap[(i - 1) / 2]); // Zamień miejscami element z rodzicem
            i = (i - 1) / 2; // Przesuń się w górę kopca
        }
    }

    /*
     * @brief Usuwa element z najwyższym priorytetem z kolejki
     * @return void
     */
    void pop() {
        if (heap.size() == 0) // Jeśli kopiec jest pusty
            throw std::out_of_range("heap underflow"); // Rzuć wyjątek

        heap[0] = heap.back(); // Zamień korzeń z ostatnim elementem
        heap.pop_back(); // Usuń ostatni element
        heapify(0); // Przywróć własność kopca dla korzenia
    }

    /*
     * @brief Zwraca element z najwyższym priorytetem z kolejki
     * @return Element z najwyższym priorytetem
     */
    const T& top() const {
        if (heap.size() == 0) // Jeśli kopiec jest pusty
            throw std::out_of_range("heap underflow"); // Rzuć wyjątek

        return heap.front(); // Zwróć korzeń kopca
    }

    /*
     * @brief Sprawdza czy kolejka jest pusta
     * @return true jeśli kolejka jest pusta, false w przeciwnym razie
     */
    bool empty() const {
        return heap.size() == 0; // Kolejka jest pusta jeśli rozmiar kopca wynosi 0
    }
};

#endif //GRAFY_PRIORITYQUEUE_H
