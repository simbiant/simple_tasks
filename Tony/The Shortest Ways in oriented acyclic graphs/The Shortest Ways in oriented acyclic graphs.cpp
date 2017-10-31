#include <vector>
#include <iostream>
#include <algorithm>

const int INF = 2147483647;

int among = 8;
std::vector<std::vector<std::vector<int>>> graph = { { { 4,2 } },
                                                      { { 0,1 },{ 2,1 },{ 4,4 },{ 5,3 } },
                                                      { { 5,1 } },
                                                      {},
                                                      { { 3,3 },{ 7,1 } },
                                                      { { 3,5 },{ 6,2 } },
                                                      { { 3,2 } },
                                                      { { 3,1 } } }; //# ���������� ����, �������� ������� ��������� ��� 
                                                                     //# (������ ������� �������, �� ���
std::vector<int> visited(among, 0);

void dfs(int vertex, std::vector<int> &p) {
  visited[vertex] = 1;
  for (int ind = 0; ind < graph[vertex].size(); ++ind) {
    int u = graph[vertex][ind][0]; //�������, ������� � `v`
    if (!visited[u]) {
      dfs(u, p);
    }
  }
  p.push_back(vertex);
}

std::vector<int> top_sort() {
  std::vector<int> p; //������� ������ � ������� �������������� ����������
  for (int vertex = 0; vertex < among; ++vertex) {
    if (!visited[vertex]) {
      dfs(vertex, p);
    }
  }
  std::reverse(p.begin(), p.end());
  return p;
}

int get_min_reliable_distance(int u, int vertex, int k) { //# k -- ����������� ���������� ����� �������� ����
  std::vector<std::vector<int>> distances(among, std::vector<int>(k, INF)); //# ���������� ����������
  distances[u][0] = 0;
  std::vector<int> p = top_sort();

  for (int tnd = 0; tnd < k; ++tnd) {
    for (int ind = 0; ind < among; ++ind) { //# ������� � ������� �������������� ����������
      int vertex1 = p[ind];
      for (int jnd = 0; jnd < graph[vertex1].size(); ++jnd) { //# ������� �������
        int vertex2 = graph[vertex1][jnd][0];
        int w = graph[vertex1][jnd][1];
        distances[vertex2][tnd +1 ] = std::min(distances[vertex2][tnd + 1], distances[vertex1][tnd] + w);
      }
     }
  }
  return distances[vertex][k];
}

int main() {
  int u, v, k;
  std::cin >> u >> v, k;
  std::cout << get_min_reliable_distance(u, v, k);
  return 0;
}