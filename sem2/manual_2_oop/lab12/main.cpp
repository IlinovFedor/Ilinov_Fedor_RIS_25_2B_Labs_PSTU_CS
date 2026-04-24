#include <iostream>
#include <set>
#include <random>
#include "Pair.h"
#include "MultiSet.hpp"

std::random_device rd;
std::mt19937 gen(rd());

template<class T>
void printContainerAfterSubtask(const T& l) {
    std::cout << "\t\t";
    for (auto &i: l) std::cout << i << ' ';
    std::cout << '\n';
}

template<class T>
T subtask1(const T& t) {
    T l = t;
    std::cout << "\tsubtask 1\n";
    using Item = typename T::value_type;

    Item avg = Item();
    for (auto &i: l)
        avg += i;
    avg /= l.size();
    l.insert(avg);

    std::cout << "\t\t" << "avg: " << avg << '\n';

    return l;
}

template<class T>
T subtask2(const T& t) {
    T l = t;

    std::cout << "\tsubtask 2\n";
    using Item = typename T::value_type;

    std::uniform_int_distribution<> dist(0, 2);
    std::vector<Item> forDelete;
    for (auto &i: l)
        if (!dist(gen))
            forDelete.push_back(i);

    std::cout << "\t\tFor delete:\n\t\t";
    for (auto &i: forDelete) {
        std::cout << i << ' ';
        l.erase(i);
    }
    std::cout << '\n';

    return l;
}

template<class T>
T subtask3(const T& t) {
    T l = t;

    std::cout << "\tsubtask 3\n";
    using Item = typename T::value_type;

    auto mn = *l.begin(), mx = *l.begin();
    for (auto &i: l) {
        if (i < mn) mn = i;
        if (i > mx) mx = i;
    }
    const Item avg = (mn + mx) / 2;

    T tmp;
    for (auto &i: l)
        tmp.insert(i + avg);
    std::cout << "\t\t(min + max) / 2 = " << avg << '\n';

    return tmp;
}

void task_1() {
    std::cout << "task 1\n";

    std::multiset<double> ms;
    std::uniform_int_distribution<> dist(-99, 99);
    for (int i = 0; i < 10; i++)
        ms.insert((double)dist(gen) / 10);

    std::cout << '\t';
    for (auto &i: ms) std::cout << i << ' ';
    std::cout << '\n';

    ms = subtask1(ms);
    printContainerAfterSubtask(ms);
    
    ms = subtask2(ms);
    printContainerAfterSubtask(ms);

    ms = subtask3(ms);
    printContainerAfterSubtask(ms);
}


void task_2() {
    std::cout << "task 2\n";

    std::multiset<Pair> ms;
    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        ms.insert(p);
    }

    std::cout << '\t';
    for (auto &i: ms) std::cout << i << ' ';
    std::cout << '\n';

    ms = subtask1(ms);
    printContainerAfterSubtask(ms);

    ms = subtask2(ms);
    printContainerAfterSubtask(ms);

    ms = subtask3(ms);
    printContainerAfterSubtask(ms);
}


void task_3() {
    std::cout << "task 3\n";

    MultiSet<Pair> ms;
    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        ms.insert(p);
    }

    std::cout << '\t';
    for (auto &i: ms) std::cout << i << ' ';
    std::cout << '\n';

    ms = subtask1(ms);
    printContainerAfterSubtask(ms);

    ms = subtask2(ms);
    printContainerAfterSubtask(ms);

    ms = subtask3(ms);
    printContainerAfterSubtask(ms);
}

int main() {
    task_1();
    task_2();
    task_3();
}