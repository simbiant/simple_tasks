#include <vector>
#include <iostream>
#include <algorithm>

int among = 10;
std::vector<std::vector<int>> matrix; //={{},{}...}

std::vector<std::vector<int>> warshall() {
  std::vector<std::vector<int>> matrix_copy = matrix;
  for (int knd = 0; knd < among; ++knd) {
    for (int ind = 0; ind < among; ++ind) {
      for (int jnd = 0; jnd < among; ++jnd) {
        matrix_copy[ind][jnd] = matrix_copy[ind][jnd] | (matrix_copy[ind][knd] & matrix_copy[knd][jnd]);
      }
    }
  }
  return matrix_copy;
}

int main() {
  warshall();
  return 0;
}