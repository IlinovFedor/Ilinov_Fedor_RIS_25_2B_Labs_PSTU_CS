#include <iostream>
#include <limits.h>

using namespace std;

struct Person {
    std::string name;
    int height;
    
    void print() {
        cout << name << ": " << height << "cm\n";
    }
};

template<class T>
void countingSort(T* a, int s) {
    int mn = a[0].height, mx = a[0].height;
    for (int i = 1; i < s; i++) {
        if (a[i].height < mn)
            mn = a[i].height;
        if (a[i].height > mx)
            mx = a[i].height;
    }

    int l = mx - mn + 1;
    int* p = new int[l];
    T* b = new T[s];

    for (int i = 0; i < l; i++)
        p[i] = 0;

    for (int i = 0; i < s; i++)
        p[a[i].height - mn]++;

    for (int i = 1; i < l; i++)
        p[i] += p[i - 1];

    for (int i = l - 1; i > 0; i--)
        p[i] = p[i - 1];
    p[0] = 0;

    for (int i = 0; i < s; i++)
        b[p[a[i].height - mn]++] = a[i];

    for (int i = 0; i < s; i++)
        a[i] = b[i];

    delete[] p;
    delete[] b;
}

int main() {
    Person a[] = {
        {"Алексей", 178},
        {"Мария", 165},
        {"Дмитрий", 182},
        {"Анна", 170},
        {"Иван", 165},
        {"Елена", 175}
    };;

    //int a[10] = {13, 2, 7, 5, 3, 4, 6, 6, 6, 9};
    for (auto &i: a) i.print();

    countingSort(a, 6);
    cout << '\n';
    for (auto &i: a) i.print();

}