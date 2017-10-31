#include <vector>
#include <iostream>
#include <algorithm>

void find_a(long long &weight, long long &among, std::vector<long long> &values, long long *ans);

int main() {
  long long among, weight, ans = 0;
  std::cin >> among;
  std::vector<long long> values(among);
  for (long long ind = 0; ind < among; ++ind) {
    std::cin >> values[ind];
  }
  std::cin >> weight;
  find_a(weight, among, values, &ans);
  std::cout << ans;
  return 0;
}

void find_a(long long &weight, long long &among, std::vector<long long> &values, long long *ans) {
  long long sizeL = 1 << (among / 2);
  long long sizeR = 1 << (among - among / 2);
  std::vector<long long> list1(sizeL);
  std::vector<long long> list2(sizeR);
  for (long long ind = 0; ind < sizeL; ++ind) {
    for (long long jnd = 0; jnd < among / 2; ++jnd) {
      if ((ind & (1 << jnd)) > 0) {
        list1[ind] += values[jnd];
      }
    }
  }
  for (long long ind = 0; ind < sizeR; ++ind) {
    for (long long jnd = 0; jnd < among - among / 2; ++jnd) {
      if ((ind & (1 << jnd)) > 0) {
        list2[ind] += values[jnd + among / 2];
      }
    }
  }
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());
  long long pointsPl = 0;
  for (long long ind = 0; ind < sizeL; ++ind) {
    if (list1[ind] <= weight) {
      pointsPl = lower_bound(list2.begin(), list2.end(), weight - list1[ind] + 1) - list2.begin();
      *ans = *ans + pointsPl;
    }
    else {
      break;
    }
  }
}
