#include <iostream>
#include <vector>
#include <algorithm>

#define INF  2147483647


class Partition {
    int n_;

//  на сколько частей делим
    int k_;

    std::vector<int> sequence_;

//  вектор частичных сумм, для того чтомы быстро считать сумму от i до x элемента
//  в последовательности
    std::vector<int> partial_sum_;

//  вестор минимальных максимальных занчаний (M[n][k]) :)
//  ответ будет в последней нижней ячейке
    std::vector<std::vector<int>> value_;

//  это нужно для востановления последовательности разделителей
    std::vector<std::vector<int>> delimiters_;

public:
    explicit Partition(std::istream& in) {
        in >> n_ >> k_;

        sequence_ = std::vector<int>(n_, 0);
        for (int i = 0; i < n_; ++i) {
            in >> sequence_[i];
        }

        partial_sum_ = std::vector<int>(n_ + 1, 0);
        for (int i = 1; i <= n_; ++i) {
            partial_sum_[i] = partial_sum_[i - 1] + sequence_[i - 1];
        }

        value_ = std::vector<std::vector<int>>(n_ + 1, std::vector<int>(k_ + 1, 0));
        delimiters_ = std::vector<std::vector<int>>(n_ + 1, std::vector<int>(k_ + 1, 0));

        for (int i = 1; i <= n_; ++i) {
            value_[i][1] = partial_sum_[i];
        }
        for (int i = 1; i <= k_; ++i) {
            value_[1][i] = sequence_[0];
        }
    }

//  тут заполняем массив value_
    int get_max_part() {
//      по всем эелементам последовательности
        for (int i = 2; i <= n_; ++i) {
//          по любому количеству делителей
            for (int j = 2; j <= k_; j++) {
                value_[i][j] = INF;
                int new_value = 0;
//              x - это положение самого правого делителя, будем сравнивать сумму элементов
//              после него и M для части котороя находится перед x
                for (int x = 1; x <= i; ++x) {
//                  вот тут вся магия
//                  ищем маскимальную часть для этих зачений n, i и x
                    new_value = std::max(value_[x][j - 1], partial_sum_[i] - partial_sum_[x]);
                    if (value_[i][j] > new_value) {
                        value_[i][j] = new_value;
                        delimiters_[i][j] = x;
                    }
                }
            }
        }

        return value_[n_][k_];
    }
//  метод возвращает последовательность номеров элементов, после котрых нужно поставить разделитель
    std::vector<int> get_delimiters() {
        std::vector<int> delimiters_sequence = std::vector<int>();

        int n = n_;
        int k = k_;

        while (delimiters_sequence.size() < k_ - 1) {
            delimiters_sequence.push_back(delimiters_[n][k]);
            n = delimiters_[n][k];
            k = k - 1;
        }
        std::reverse(delimiters_sequence.begin(), delimiters_sequence.end());
        return delimiters_sequence;
    }
};


int main() {

//  n > 0
//  k > 0
//  опять же, лучший тест в мире :)
//  6 3
//  1 2 3 4 5 6
//  (делим последовательнсоть из 6 элементов на 3 части)

    Partition pt = Partition(std::cin);
    std::cout << pt.get_max_part() << std::endl;
    std::vector<int> delimiters = pt.get_delimiters();
    std::copy(delimiters.begin(), delimiters.end(), std::ostream_iterator<int>(std::cout," "));

    return 0;
}