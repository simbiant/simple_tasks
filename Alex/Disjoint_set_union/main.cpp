#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int _id, _size;
    Item *_next, *_tail, *_head;

    Item(int id) {
        _id = id;
        _next = nullptr;
        _tail = this;
        _head = this;
        _size = 1;
    }
};

struct DSU {
    vector<Item *> elem;

    DSU(int n = 0) {
        init_dsu(n);
    }

    void init_dsu(int n) {
        elem.resize(n);
        for (int i = 0; i < n; ++i) {
            elem[i] = new Item(i);
        }
    }

    int find(int i) {
        return elem[i]->_head->_id;
    }
    void unionn(int id1, int id2) {
        Item *a = elem[id1], *b = elem[id2];
        a = a->_head;
        b = b->_head;
        if (a == b) {
            return;
        }
        if (b->_size > a->_size) {
            swap(a, b);
        }
        a->_tail->_next = b;
        a->_tail = b->_tail;
        a->_size += b->_size;
        while (b != nullptr) {
            b->_head = a;
            b = b->_next;
        }
    }
};

int main()
{
    DSU my_dsu(10);
    my_dsu.unionn(1, 2);
    my_dsu.unionn(0, 3);
    my_dsu.unionn(6, 2);
    my_dsu.unionn(7, 3);
    my_dsu.unionn(9, 8);
    my_dsu.unionn(9, 6);
    for (int i = 0; i < 10; ++i) {
        cout << i << " - " << my_dsu.find(i) << "\n";
    }
    return 0;
}
