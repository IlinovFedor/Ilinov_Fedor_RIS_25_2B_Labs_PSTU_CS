#include <iostream>
#include "bidirectional.h"

using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    for (int l: arr)
        cout << l << ' ';
    BiList list1, list2;
    cin >> list1 >> list2;
    BiList list3 = list2;

    for (int i = 0; i < list2(); i++)
        list2[i] = -1;
    cout << list2;

    cout << list1 * list3;

    for (auto i: list1) {
        cout << i << ':';
    }
    cout << '\n';
    cout << '\n';

    auto iter = list1.begin();
    cout << (iter + 2).value() << ' ';
    cout << (--iter).value() << ' ';
    cout << (iter - 1).value() << ' ';
    cout << '\n';

    iter = list2.begin();
    iter + 2;
    iter.setValue(10);
    cout << list2;
}
