#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <algorithm>
#include "Pair.h"
#include "PriorityQueue.h"

std::random_device rd;
std::mt19937 gen(rd());

template<class T>
void printItem(const T& i) { std::cout << i << ' '; }

void printPair(const std::pair<const Pair, int>& pair) { std::cout << "([" << pair.first << "] = " << pair.second << ") "; }

Pair extractKey(const std::pair<const Pair, int>& pair) { return pair.first; }

template<class T>
void printContainerAfterSubtask(const T& l) {
    std::cout << "\t\t";
    std::for_each(l.begin(), l.end(), printItem<typename T::value_type>);
    std::cout << '\n';
}

template<class T>
T subtask1(const T& t) {
    T l = t;
    std::cout << "\tsubtask 1\n";
    using Item = typename T::value_type;

    Item avg = Item();
    std::for_each(l.begin(), l.end(), [&avg](const Item& i){ avg += i; });
    avg /= (int)l.size();
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

    std::vector<Item> forDelete;
    std::remove_copy_if(l.begin(), l.end(), std::back_inserter(forDelete),
        [&](const Item&){ return dist(gen) != 0; });

    std::cout << "\t\tFor delete:\n\t\t";

    std::for_each(forDelete.begin(), forDelete.end(), printItem<Item>);

    if constexpr (std::is_same_v<T, std::list<Item>>) {
        std::for_each(forDelete.begin(), forDelete.end(), [&](const Item& i){ l.remove(i); });
    } else {
        std::for_each(forDelete.begin(), forDelete.end(), [&](const Item& i){
            l.erase(std::remove(l.begin(), l.end(), i), l.end());
        });
    }
    std::cout << '\n';

    return l;
}

template<class T>
T subtask3(const T& t) {
    T l = t;

    std::cout << "\tsubtask 3\n";
    using Item = typename T::value_type;

    auto mn = *std::min_element(l.begin(), l.end());
    auto mx = *std::max_element(l.begin(), l.end());
    Item avg = (mn + mx) / 2;

    std::for_each(l.begin(), l.end(), [&avg](Item& i){ i += avg; });

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
    std::for_each(l.begin(), l.end(), printItem<double>);
    std::cout << '\n';

    l.sort();
    std::cout << "\t[asc]:  "; std::for_each(l.begin(), l.end(), printItem<double>); std::cout << '\n';
    l.sort(std::greater<double>());
    std::cout << "\t[desc]: "; std::for_each(l.begin(), l.end(), printItem<double>); std::cout << '\n';

    l = subtask1(l);
    printContainerAfterSubtask(l);

    l = subtask2(l);
    printContainerAfterSubtask(l);

    l = subtask3(l);
    printContainerAfterSubtask(l);
}

template<class T>
PriorityQueue<T> copyBiListToSTLPriorityQueue(const std::vector<T>& bl) {
    PriorityQueue<T> q;
    std::for_each(bl.begin(), bl.end(), [&q](const T& i){ q.push(i); });
    return q;
}

template<class T>
std::vector<T> copySTLPriorityQueueToBiList(PriorityQueue<T>& q) {
    std::vector<T> bl;
    while (!q.empty()) {
        bl.push_back(q.top());
        q.pop();
    }
    q = copyBiListToSTLPriorityQueue(bl);
    return bl;
}

template<class T>
void printSTLPriorityQueue(PriorityQueue<T>& q) {
    auto v = copySTLPriorityQueueToBiList(q);
    std::for_each(v.begin(), v.end(), printItem<T>);
    std::cout << '\n';
}

void task_2() {
    std::cout << "task 2\n";
    PriorityQueue<Pair> q;

    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        q.push(p);
    }

    std::cout << '\t';
    printSTLPriorityQueue(q);

    {
        auto sv = copySTLPriorityQueueToBiList(q);
        std::sort(sv.begin(), sv.end());
        std::cout << "\t[asc]:  "; std::for_each(sv.begin(), sv.end(), printItem<Pair>); std::cout << '\n';
        std::sort(sv.begin(), sv.end(), std::greater<Pair>());
        std::cout << "\t[desc]: "; std::for_each(sv.begin(), sv.end(), printItem<Pair>); std::cout << '\n';
    }

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

void task_3() {
    std::cout << "task 3\n";
    std::map<Pair, int> mp;

    std::uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10; i++) {
        Pair p((double)dist(gen) / 10, dist(gen));
        mp[p] = dist(gen);
    }

    std::cout << '\t';
    std::for_each(mp.begin(), mp.end(), printPair);
    std::cout << '\n';

    std::vector<Pair> v;
    std::transform(mp.begin(), mp.end(), std::back_inserter(v), extractKey);

    std::sort(v.begin(), v.end());
    std::cout << "\t[asc]:  "; std::for_each(v.begin(), v.end(), printItem<Pair>); std::cout << '\n';
    std::sort(v.begin(), v.end(), std::greater<Pair>());
    std::cout << "\t[desc]: "; std::for_each(v.begin(), v.end(), printItem<Pair>); std::cout << '\n';

    v = subtask1(v);
    std::cout << "\t\t";
    std::for_each(v.begin(), v.end(), printItem<Pair>);
    std::cout << '\n';

    v = subtask2(v);
    std::cout << "\t\t";
    std::for_each(v.begin(), v.end(), printItem<Pair>);
    std::cout << '\n';

    v = subtask3(v);
    std::cout << "\t\t";
    std::for_each(v.begin(), v.end(), printItem<Pair>);
    std::cout << '\n';

    std::cout << '\n';
}

int main() {
    task_1();
    task_2();
    task_3();
}