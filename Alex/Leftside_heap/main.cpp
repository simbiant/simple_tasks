#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

struct Leftside_tree {
    Leftside_tree *_left, *_right;
    int _rank, _key;
    Leftside_tree(int key) {
        _left = nullptr;
        _right = nullptr;
        _rank = 0;
        _key = key;
    }
};

static Leftside_tree * merge(Leftside_tree * a, Leftside_tree * b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->_key > b->_key) {
        swap(a, b);
    }
    a->_right = merge(a->_right, b);
    if (a->_right != nullptr && a->_left != nullptr && a->_right->_rank > a->_left->_rank) {
        swap(a->_right, a->_left);
    }
    if (a->_right != nullptr && a->_left == nullptr) {
        a->_left = a->_right;
        a->_right = nullptr;
    }
    if (a->_right != nullptr) {
        a->_rank = a->_right->_rank + 1;
    } else {
        a->_rank = 0;
    }
    return a;
}

static Leftside_tree * insert(Leftside_tree * a, int value) {
    Leftside_tree * for_insert = new Leftside_tree(value);
    a = merge(a, for_insert);
    return a;
}

static Leftside_tree * find_and_cut_node(Leftside_tree * a, int x) {
    if (a == nullptr) {
        return a;
    }
    if (a->_left != nullptr && a->_left->_key == x) {
        Leftside_tree * founded = a->_left;
        a->_left = a->_right;
        a->_rank = 0;
        a->_right = nullptr;
        return founded;
    }
    if (a->_right != nullptr && a->_right->_key == x) {
        Leftside_tree * founded = a->_right;
        a->_rank = 0;
        a->_right = nullptr;
        return founded;
    }
    Leftside_tree * left = find_and_cut_node(a->_left, x);
    if (left != nullptr) {
        if (a->_right != 0) {
            if (a->_right->_rank > a->_left->_rank) {
                swap(a->_right, a->_left);
            }
        }
        return left;
    }
    Leftside_tree * right = find_and_cut_node(a->_right, x);
    if (a->_right != 0) {
        if (a->_right->_rank > a->_left->_rank) {
            swap(a->_right, a->_left);
        }
    }
    return left;
}

static Leftside_tree * decrease_key(Leftside_tree * a, int x) {
    if (a->_key == x) {
        a->_key = numeric_limits<int>::min();
    } else {
        Leftside_tree * for_decrease = find_and_cut_node(a, x);
        for_decrease->_key = numeric_limits<int>::min();
        a = merge(for_decrease, a);
    }
    return a;
}

static Leftside_tree * build_tree(vector<int> arr) {
    queue<Leftside_tree *> trees;
    for (size_t i = 0; i < arr.size(); ++i) {
        trees.push(new Leftside_tree(arr[i]));
    }
    while (trees.size() > 1) {
        Leftside_tree * a = trees.front();
        trees.pop();
        Leftside_tree * b = trees.front();
        trees.pop();
        trees.push(merge(a, b));
    }
    return trees.front();
}

static void deletee(Leftside_tree * a, int x) {
    Leftside_tree * new_tree = decrease_key(a, x);
    a = merge(a->_left, a->_right);
}

static pair<Leftside_tree *, int> extract_min(Leftside_tree * a) {
    int minimum = a->_key;
    Leftside_tree * left = a->_left;
    Leftside_tree * right = a->_right;
    return make_pair(merge(a->_left, a->_right), minimum);
}

int main() {
    vector<int> arr(4);
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = (i + 2) * (i + 2);
    }
    Leftside_tree * a = build_tree(arr);
    a = insert(a, 2);
    pair<Leftside_tree *, int> f = extract_min(a);
    cout << f.second;
    return 0;
}
