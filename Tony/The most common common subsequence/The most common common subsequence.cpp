#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

std::vector<std::vector<std::string>> arrows;

int lcs_length(std::string x, std::string y) {
  int n = x.size();
  int m = y.size();
  std::vector<std::vector<int>> length(n + 1, std::vector<int>(m + 1, 0));
  arrows.resize(n + 1, std::vector<std::string>(m + 1, "top"));

  for (int ind = 1; ind < n + 1; ++ind) {
    for (int jnd = 1; jnd < m + 1; ++jnd) {
      if (x[ind - 1] == y[jnd - 1]) {
        length[ind][jnd] = length[ind - 1][jnd - 1] + 1;
        arrows[ind][jnd] = "diag";
      } else if(length[ind - 1][jnd] >= length[ind][jnd - 1]) {
        length[ind][jnd] = length[ind - 1][jnd];
        arrows[ind][jnd] = "top";
      } else {
        length[ind][jnd] = length[ind][jnd - 1];
        arrows[ind][jnd] = "left";
      }
    }
  }
  return length[n][m];
}

void print_lcs(std::string x, std::string y,  int ind = -1, int jnd = -1) { //# i, j: текущие индексы первой и второй строки
  if (ind == -1 || jnd == -1) {
    ind = x.size();
    jnd = y.size();
  }
  if (ind == 0 || jnd == 0) {
    return;
  }
  if (arrows[ind][jnd] == "diag") {
    print_lcs(x, y, ind - 1, jnd - 1);
    std::cout << x[ind - 1];
  } else if (arrows[ind][jnd] == "top") {
    print_lcs(x, y, ind - 1, jnd);
  } else {
    print_lcs(x, y, ind, jnd - 1);
  }
}
int main() {
  std::string x, y;
  std::cin >> x >> y;
  std::cout << lcs_length(x, y) << '\n';
  print_lcs(x, y);
  return 0;
}
