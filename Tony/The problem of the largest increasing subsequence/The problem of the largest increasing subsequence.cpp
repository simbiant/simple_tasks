#include <vector>
#include <iostream>
#include <algorithm>

const int INF = 2147483647;

std::vector<int> input_of_data(std::istream &in);
const std::vector<int> the_largest_non_decreasing_subsequence(std::vector<int> &list_of_quality);
int binary_search(std::vector<int> &end_of_sequence, int key);
void output_of_data(std::ostream &out, std::vector<int> const &answer);

int main() {
  std::vector<int> list_of_quality = input_of_data(std::cin);
  const std::vector<int> answer = the_largest_non_decreasing_subsequence(list_of_quality);
  output_of_data(std::cout, answer);
  return 0;
}

std::vector<int> input_of_data(std::istream &in) {
  int among;
  in >> among;
  std::vector<int> list_of_quality(among);
  for (int index = 0; index < among; ++index) {
    in >> list_of_quality[index];
  }
  return list_of_quality;
}

const std::vector<int> the_largest_non_decreasing_subsequence(std::vector<int> &list_of_quality) {
  const int size = list_of_quality.size();
  std::vector<int> end_of_sequence(size + 1, INF);
  std::vector<int> pos(size + 1, 0);
  std::vector<int> prev(size, 0);
  end_of_sequence[0] = -INF;
  pos[0] = -1;
  int length = 0, indexI, indexJ;
  for (indexI = 0; indexI < size; ++indexI) {
    indexJ = binary_search(end_of_sequence, list_of_quality[indexI]);
    if (end_of_sequence[indexJ - 1] < list_of_quality[indexI] < end_of_sequence[indexJ]) {
      end_of_sequence[indexJ] = list_of_quality[indexI];
      pos[indexJ] = indexI;
      prev[indexI] = pos[indexJ - 1];
      length = std::max(length, indexJ);
    }
  }
  std::vector<int> answer;
  int pos_in_list = pos[length];
  while (pos_in_list != -1) {
    answer.push_back(list_of_quality[pos_in_list]);
    pos_in_list = prev[pos_in_list];
  }
  std::reverse(answer.begin(), answer.end());
  return answer;
}

int binary_search(std::vector<int> &end_of_sequence, int key) {
  int left = 0;
  int right = end_of_sequence.size() - 1;
  int mid = 0;

  while (!(left >= right))
  {
    mid = left + (right - left) / 2;
    if (end_of_sequence[mid] == key)
      return mid;
    if (end_of_sequence[mid] > key)
      right = mid;
    else
      left = mid + 1;
  }
  return left;
}

void output_of_data(std::ostream &out, std::vector<int> const &answer) {
  out << answer.size() << '\n';
  for (auto number : answer) {
    out << number << '\n';
  }
}