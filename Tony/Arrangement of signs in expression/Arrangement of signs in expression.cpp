#include <vector>
#include <iostream>
#include <algorithm>

int get_max_value(std::vector<int> a) {
  //# a - исходная последовательность
  int among = a.size();
  std::vector<std::vector<int>> d(among, std::vector<int>(among, 0));
  for (int ind = 0; ind < among; ++ind) {
    d[ind][ind] = a[ind];
  }
  for (int ind = among - 2; ind > -1; --ind) {
    for (int jnd = ind + 1; jnd < among; ++jnd) {
      for (int knd = ind; knd < jnd; ++knd) {
        d[ind][jnd] = std::max(d[ind][jnd], d[ind][knd] + d[knd + 1][jnd]);
        d[ind][jnd] = std::max(d[ind][jnd], d[ind][knd] * d[knd + 1][jnd]);
      }
    }
  }
  return d[0][among - 1];
}
int main() {
  int among;
  std::cin >> among;
  std::vector<int> list(among);
  for (int ind = 0; ind < among; ++ind) {
    std::cin >> list[ind];
  }
  std::cout << get_max_value(list);
  return 0;
}