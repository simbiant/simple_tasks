#include <vector>
#include <iostream>
#include <algorithm>
// количество вершин
int among = 6; 
//# список смежности для обратных рёбер графа (обратных?)
std::vector<std::vector<int>> graph_reversed; //= {{}, {}, {},...};

int count_rec(int v, std::vector<int> &d) {
  if (d[v] != -1) {
    return d[v];
  }
  int result = 0;
  for (int index = 0; index < graph_reversed[v].size(); ++index) {
    int u = graph_reversed[v][index];
    result += count_rec(u, d);
  }
  d[v] = result;
  return d[v];
}
int count_paths(int s, int t) {
  std::vector<int> d(among, -1); //# количества путей из `s` до всех вершин
  d[s] = 1;
  return count_rec(t, d);
}

int main() {
  int start = 0, end = 5;
  count_paths(start, end);
  return 0;
}