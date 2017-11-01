#include <iostream>
#include <vector>
#include <algorithm>

class Knapsack {
//  объем рюкзака
    int volume_;

//  количество вещей которые можно положить в рюкзак
    int n_;

//  массивы весов и цен вещей, которые можно положть в рюкзак
    std::vector<int> weights_;
    std::vector<int> prices_;

//  массив с ответами для объема [1, volume_] и для [1, n] вещей
    std::vector<std::vector<int>> answers_;

public:
    explicit Knapsack(std::istream& in) {
        in >> n_;
        in >> volume_;

        weights_ = std::vector<int>(n_, 0);
        prices_ = std::vector<int>(n_, 0);
        for (int i = 0; i < n_; ++i) {
            in >> weights_[i] >> prices_[i];
        }
        answers_ = std::vector<std::vector<int>>(n_ + 1, std::vector<int>(volume_ + 1, 0));
    }

//  Метод котрый возращает максимальную стоимость вещей которые влазят в рюкзак
    int get_max_price() {
//      по всем вещам
        for (int indexOfThing = 1; indexOfThing <= n_; ++indexOfThing) {
            // по всем объемам рюкзака
            for (int volume = 1; volume <= volume_; ++volume) {

//              сравниваем вес текущей вещи с текущим объемом
                if (weights_[indexOfThing - 1] <= volume) {

                    int newWeight = volume - weights_[indexOfThing - 1];
//                  смотрим как будет стимость больше: с этим предметом или без него
                    answers_[indexOfThing][volume] = std::max(answers_[indexOfThing - 1][volume],
                                 answers_[indexOfThing - 1][newWeight] + prices_[indexOfThing - 1]);
                } else {
                    answers_[indexOfThing][volume] = answers_[indexOfThing - 1][volume];
                }
            }
        }

//      ответ в последней ячейке
        return answers_[n_][volume_ - 1];
    }

//  метод для востановления ответа, печатает номер необходимых предметов
    void print_things(std::ostream& out) {
        int indexOfThing = n_;
        int volume = volume_;
        while (true) {

            if (answers_[indexOfThing][volume] == answers_[indexOfThing - 1][volume]) {
            } else {
                out << indexOfThing << "\n";
                volume -= weights_[indexOfThing - 1];
            }

            indexOfThing = indexOfThing - 1;

            if (indexOfThing < 0 || volume < 0) break;
        }
    }


};


int main() {
//    Лучший тест в мире инфа 100
//    5 13
//    3 1
//    4 6
//    5 4
//    8 7
//    9 6
    Knapsack back = Knapsack(std::cin);
    std::cout << back.get_max_price() << std::endl;
    back.print_things(std::cout);

    return 0;
}