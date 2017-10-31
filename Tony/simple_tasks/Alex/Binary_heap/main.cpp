#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Binary_heap {
    vector<int> _heap;
    size_t _size;

    Binary_heap() {
        _heap.resize(0);
        _size = 0;
    }

    void sift_down(size_t curr) {
        while (curr * 2 + 1 < _size) {
            size_t left = curr * 2 + 1;
            size_t right = curr * 2 + 2;
            size_t minimal = left;
            if (right < _size && _heap[right] < _heap[left]) {
                minimal = right;
            }
            if (_heap[minimal] >= _heap[curr]) {
                break;
            }
            swap(_heap[curr], _heap[minimal]);
            curr = minimal;
        }
    }

    void sift_up(size_t curr) {
        size_t parent = (curr - 1) / 2;
        while (_heap[curr] < _heap[parent] && curr != 0) {
            swap(_heap[curr], _heap[parent]);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
    int extract_min() {
        int minimum = _heap[0];
        _heap[0] = _heap[_size - 1];
        _heap.pop_back();
        _size--;
        sift_down(0);
        return minimum;
    }
    void insert(int value) {
        _heap.push_back(value);
        _size++;
        sift_up(_size - 1);
    }
    void heapify() {
        size_t mid = _size / 2;
        for (size_t i = mid; i >= 0; --i) {
            sift_down(i);
            if (i == 0) {
                break;
            }
        }
    }
    void merge(Binary_heap other) {
        for (size_t i = 0; i < other._size; ++i) {
            _heap.push_back(other._heap[i]);
        }
        heapify();
    }
};

int main()
{
    Binary_heap * a = new Binary_heap();
    a->insert(1);
    a->insert(3);
    a->insert(43);
    a->insert(5);
    a->insert(23);
    a->insert(25);
    a->insert(12214);
    a->insert(5);
    a->insert(23);
    cout << a->extract_min() << "\n";
    cout << a->extract_min() << "\n";
    cout << a->extract_min() << "\n";
    cout << a->extract_min() << "\n";
    cout << a->extract_min() << "\n";
    cout << a->extract_min() << "\n";
    cout << a->extract_min() << "\n";
    return 0;
}
