#include <iostream>
#include <vector>

void cut(int among, std::vector<int> &prices, std::vector<int> &results, std::vector<int> &splits);
void print_solution(int among, std::vector<int> &splits);

int main() {
  int among = 0;
  std::cin >> among;
  // the array of rod prices
  std::vector<int>prices(among);
  for (int ind = 0; ind < among; ++ind) {
    std::cin >> prices[ind];
  }
  // the array of optimal prices
  std::vector<int>results(among + 1);
  // the array of optimal sizes of the first part
  std::vector<int>splits(among + 1);
  cut(among, prices, results, splits);
  print_solution(among, splits);
  return 0;
}

void cut(int among, std::vector<int> &prices, std::vector<int> &results, std::vector<int> &splits) {
  results[0] = 0;
  for (int jnd = 1; jnd < among + 1; ++jnd) {
    int result = -1;
    for (int ind = 1; ind < jnd + 1; ++ind) {
      int candidate = prices[ind - 1] + results[jnd - ind];
      if (candidate > result) {
        result = candidate;
        splits[jnd] = ind;
      }
    }
    results[jnd] = result;
  }
}

void print_solution(int among, std::vector<int> &splits) {
  int size = among;
  while (size > 0) {
    std::cout << splits[size] << " ";
    size = size - splits[size];
  }
}