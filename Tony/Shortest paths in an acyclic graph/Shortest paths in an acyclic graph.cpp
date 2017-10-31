#include <vector>
#include <iostream>
#include <algorithm>

const int INF = 2147483647;

int among = 8;
std::vector<std::vector<std::vector<int>>> graph = { {{4,2}},
                                                    {{0,1},{2,1},{4,4},{5,3}},
                                                    {{5,1}},
                                                    {},
                                                    {{3,3},{7,1}},
                                                    {{3,5},{6,2}},
                                                    {{3,2}},
                                                    {{3,1}} }; //# взвешенный граф, заданный списком смежности пар 
															   //# (индекс смежной вершины, ее вес
std::vector<int> visited(among, 0);

void dfs(int vertex, std::vector<int> &p) {
  visited[vertex] = 1;
  for (int ind = 0; ind < graph[vertex].size(); ++ind) {
    int u = graph[vertex][ind][0]; //вершина, смежная с `v`
    if (!visited[u]) {
      dfs(u,p);
    }
  }
  p.push_back(vertex);
}

std::vector<int> top_sort() {
  std::vector<int> p; //индексы вершин в порядке топологической сортировки
  for (int vertex = 0; vertex < among; ++vertex) {
    if (!visited[vertex]) {
      dfs(vertex, p);
    }
  }
  std::reverse(p.begin(), p.end());
  return p;
}

int min_distance(int u, int vertex) {
  std::vector<int> distances(among, INF); //# кратчайшие расстояния
  distances[u] = 0;
  std::vector<int> p = top_sort();
  for (int ind = 0; ind < among; ++ind) { //# вершины в порядке топологической сортировки
    int vertex1 = p[ind];
    for (int jnd = 0; jnd < graph[vertex1].size(); ++jnd) { //# смежные вершины
      int vertex2 = graph[vertex1][jnd][0];
      int w = graph[vertex1][jnd][1];
      distances[vertex2] = std::min(distances[vertex2], distances[vertex1] + w);
    }
  }
  return distances[vertex];
}

int main() {
  int u, v;
  std::cin >> u >> v;
  std::cout << min_distance(u, v);
  return 0;
}