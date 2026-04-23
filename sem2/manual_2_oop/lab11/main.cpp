#include <iostream>
#include <list>
#include <queue>
#include <random>
#include "Pair.h"
#include "bidirectional.hpp"
#include "PriorityQueue.h"

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
    l.push_back(avg);

    std::cout << "\t\t" << "avg: " << avg << '\n';

    return l;
}

template<class T>
T subtask2(const T& t) {
    T l = t;

    std::cout << "\tsubtask 2\n";
    using Item = typename T::value_type;

    std::uniform_int_distribution<> dist(0, 2);
    BiList<Item> forDelete;
    for (auto &i: l)
        if (!dist(gen))
            forDelete.push_back(i);

    std::cout << "\t\tFor delete:\n\t\t";
    for (auto &i: forDelete) {
        std::cout << i << ' ';
        l.remove(i);
    }
    std::cout << '\n';

    return l;
}

template<class T>
T subtask3(const T& t) {
    T l = t;

    std::cout << "\tsubtask 3\n";
    using Item = typename T::value_type;

    auto mn = l.front(), mx = l.front();
    for (auto &i: l) {
        if (i < mn) mn = i;
        if (i > mx) mx = i;
    }
    Item avg = (mn + mx) / 2;
    for (auto &i: l)
        i += avg;
    std::cout << "\t\t(min + max) / 2 = " << avg << '\n';

    return l;
}

void task_1() {
    std::cout << "task 1\n";

    std::list<double> l;
    std::uniform_int_distribution<> dist(-99, 99);
    for (int i = 0; i < 10; i++)
        l.push_back((double) dist(gen) / 10);

    std::cout << '\t';
    for (double &i: l) std::cout << i << ' ';
    std::cout << '\n';

    l = subtask1(l);
    printContainerAfterSubtask(l);
    
    l = subtask2(l);
    printContainerAfterSubtask(l);

    l = subtask3(l);
    printContainerAfterSubtask(l);
}

void task_2() {
    std::cout << "task 2\n";

    std::list<Pair> l;
    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        l.push_back(p);
    }

    std::cout << '\t';
    for (auto &i: l) std::cout << i << ' ';
    std::cout << '\n';

    l = subtask1(l);
    printContainerAfterSubtask(l);

    l = subtask2(l);
    printContainerAfterSubtask(l);

    l = subtask3(l);
    printContainerAfterSubtask(l);
}

void task_3() {
    std::cout << "task 3\n";

    BiList<Pair> bilist;
    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        bilist.push_back(p);
    }

    std::cout << '\t';
    for (auto &i: bilist) std::cout << i << ' ';
    std::cout << '\n';

    bilist = subtask1(bilist);
    printContainerAfterSubtask(bilist);

    bilist = subtask2(bilist);
    printContainerAfterSubtask(bilist);

    bilist = subtask3(bilist);
    printContainerAfterSubtask(bilist);
}

template<class T>
std::priority_queue<T> copyBiListToSTLPriorityQueue(const BiList<T> & bl) {
    std::priority_queue<T> q;
    for (auto& i : bl)
        q.push(i);
    return q;
}

template<class T>
BiList<T> copySTLPriorityQueueToBiList(std::priority_queue<T> & q) {
    BiList<T> bl;
    while (!q.empty()) {
        bl.push_back(q.top());
        q.pop();
    }
    q = copyBiListToSTLPriorityQueue(bl);
    return bl;
}


template<class T>
void printSTLPriorityQueue(std::priority_queue<T> & q) {
    auto v = copySTLPriorityQueueToBiList(q);
    for (auto &i: v) std::cout << i << ' ';
    std::cout << '\n';
}

void task_4() {
    std::cout << "task 4\n";
    std::priority_queue<Pair> q;

    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        q.push(p);
    }

    std::cout << '\t';
    printSTLPriorityQueue(q);

    auto v = copySTLPriorityQueueToBiList(q);
    v = subtask1(v);
    q = copyBiListToSTLPriorityQueue(v);
    std::cout << "\t\t";
    printSTLPriorityQueue(q);

    v = copySTLPriorityQueueToBiList(q);
    v = subtask2(v);
    q = copyBiListToSTLPriorityQueue(v);
    std::cout << "\t\t";
    printSTLPriorityQueue(q);

    v = copySTLPriorityQueueToBiList(q);
    v = subtask3(v);
    q = copyBiListToSTLPriorityQueue(v);
    std::cout << "\t\t";
    printSTLPriorityQueue(q);

    std::cout << '\n';
}


template<class T>
PriorityQueue<T> copyBiListToMyPriorityQueue(const BiList<T> & bl) {
    PriorityQueue<T> q;
    for (auto& i : bl)
        q.push(i);
    return q;
}

template<class T>
BiList<T> copyMyPriorityQueueToBiList(PriorityQueue<T> & q) {
    BiList<T> bl;
    while (!q.empty()) {
        bl.push_back(q.top());
        q.pop();
    }
    q = copyBiListToMyPriorityQueue(bl);
    return bl;
}


template<class T>
void printMyPriorityQueue(PriorityQueue<T> & q) {
    auto v = copyMyPriorityQueueToBiList(q);
    for (auto &i: v) std::cout << i << ' ';
    std::cout << '\n';
}


void task_5() {
    std::cout << "task 5\n";
    PriorityQueue<Pair> q;

    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        q.push(p);
    }

    std::cout << '\t';
    printMyPriorityQueue(q);

    auto v = copyMyPriorityQueueToBiList(q);
    v = subtask1(v);
    q = copyBiListToMyPriorityQueue(v);
    std::cout << "\t\t";
    printMyPriorityQueue(q);

    v = copyMyPriorityQueueToBiList(q);
    v = subtask2(v);
    q = copyBiListToMyPriorityQueue(v);
    std::cout << "\t\t";
    printMyPriorityQueue(q);

    v = copyMyPriorityQueueToBiList(q);
    v = subtask3(v);
    q = copyBiListToMyPriorityQueue(v);
    std::cout << "\t\t";
    printMyPriorityQueue(q);

    std::cout << '\n';
}

int main() {
    task_1();
    task_2();
    task_3();
    task_4();
    task_5();
}