#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

//O(n x m)
int levrnstein(std::string s1, 
               std::string s2, 
               int insert_cost, 
               int delete_cost, 
               int replace_cost) {
  int m = s1.size();
  int n = s2.size();
  std::vector<std::vector<int>> list(m + 1, std::vector<int>(n + 1, 0));
  for (int jnd = 1; jnd < n + 1; ++jnd) {
    list[0][jnd] = list[0][jnd - 1] + insert_cost;
  }
  for (int ind = 1; ind < m + 1; ++ind) {
    list[ind][0] = list[ind - 1][0] + delete_cost;
    for (int jnd = 1; jnd < n + 1; ++jnd) {
      if (s1[ind - 1] == s2[jnd - 1]) {
        list[ind][jnd] = list[ind - 1][jnd - 1];
      } else {
        list[ind][jnd] = std::min(
          list[ind - 1][jnd] + delete_cost,
          list[ind][jnd - 1] + insert_cost);
        list[ind][jnd] = std::min(list[ind][jnd], list[ind - 1][jnd - 1] + replace_cost);
      }
    }
  }
  return list[m][n];
}

//≈сли нужно только рассто€ние, то ѕјћя“№ можно уменьшить до O(N)
//int levrnstein1(std::string s1,
//                std::string s2,
//                int insert_cost,
//                int delete_cost,
//                int replace_cost) {
//  int m = s1.size();
//  int n = s2.size();
//  std::vector<std::vector<int>> list(2, std::vector<int>(n + 1, 0));
//  for (int jnd = 1; jnd < n + 1; ++jnd) {
//    list[0][jnd] = list[0][jnd - 1] + insert_cost;
//  }
//  int prev_row = 0, current_row = 1;
//  list[1][0] = delete_cost;
//  for (int ind = 1; ind < m + 1; ++ind) {
//    current_row = 1 - prev_row;
//    list[current_row][0] = list[prev_row][0] + delete_cost;
//    for (int jnd = 1; jnd < n + 1; ++jnd) {
//      if (s1[ind - 1] == s2[jnd - 1]) {
//        list[current_row][jnd] = list[prev_row][jnd - 1];
//      } else {
//        list[current_row][jnd] = std::min(
//          list[prev_row][jnd] + delete_cost,
//          list[current_row][jnd - 1] + insert_cost,
//          list[prev_row][jnd - 1] + replace_cost
//        );
//      }
//    }
//    prev_row = current_row;
//  }
//  return list[current_row][n];
//}

int main() {
  std::string s1 = "abc", s2 = "abs";
  std::cout << levrnstein(s1, s2, 1, 1, 1);
  return 0;
}