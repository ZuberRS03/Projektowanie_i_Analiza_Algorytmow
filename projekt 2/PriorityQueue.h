#ifndef GRAFY_PRIORITYQUEUE_H
#define GRAFY_PRIORITYQUEUE_H

#include <queue>
#include <vector>
#include <stdexcept>

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
private:
    std::vector<T> heap;
    Comparator comp;

    // Metoda do przywracania własności kopca (heapify)
    void heapify(int idx) {
        int size = heap.size();
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < size && comp(heap[left], heap[idx]))
            smallest = left;
        if (right < size && comp(heap[right], heap[smallest]))
            smallest = right;

        if (smallest != idx) {
            std::swap(heap[idx], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    PriorityQueue() {}

    void push(const T& value) {
        heap.push_back(value);
        int i = heap.size() - 1;
        while (i != 0 && comp(heap[i], heap[(i - 1) / 2])) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void pop() {
        if (heap.size() == 0)
            throw std::out_of_range("heap underflow");

        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
    }

    const T& top() const {
        if (heap.size() == 0)
            throw std::out_of_range("heap underflow");

        return heap.front();
    }

    bool empty() const {
        return heap.size() == 0;
    }
};

#endif //GRAFY_PRIORITYQUEUE_H
