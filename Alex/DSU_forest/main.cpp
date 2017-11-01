#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> _rank, _parent;


    DSU(int n) {
        _rank.resize(n);
        _parent.resize(n);

        for (int i = 0; i < n; ++i) {
            _rank[i] = 0;
            _parent[i] = i;
        }
    }
    int find(int a) {
        if (_parent[a] != a) {
            _parent[a] = find(_parent[a]);
        }
        return _parent[a];
    }
    void unionn(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (_rank[a] == _rank[b]) {
            _rank[a] += 1;
        }
        if (_rank[a] < _rank[b]) {
            _parent[a] = b;
        } else {
            _parent[b] = a;
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
