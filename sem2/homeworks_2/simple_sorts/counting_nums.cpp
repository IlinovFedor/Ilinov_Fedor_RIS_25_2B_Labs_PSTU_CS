#include <chrono>
#include <iostream>
#include <limits.h>

using namespace std;


template<class T>
void countingSort(T* a, int s) {
    int mn = a[0], mx = a[0];
    for (int i = 1; i < s; i++) {
        if (a[i] < mn)
            mn = a[i];
        if (a[i] > mx)
            mx = a[i];
    }

    int l = mx - mn + 1;
    int* p = new int[l];
    T* b = new T[s];

    for (int i = 0; i < l; i++)
        p[i] = 0;

    for (int i = 0; i < s; i++)
        p[a[i] - mn]++;

    for (int i = 1; i < l; i++)
        p[i] += p[i - 1];

    for (int i = l - 1; i > 0; i--)
        p[i] = p[i - 1];
    p[0] = 0;

    for (int i = 0; i < s; i++)
        b[p[a[i] - mn]++] = a[i];

    for (int i = 0; i < s; i++)
        a[i] = b[i];

    delete[] p;
    delete[] b;
}

constexpr long long N = 1000000000LL;
int main() {
    int* a = new int[N];
    for (long long i = 0; i < N; ++i)
        a[i] = rand() % 100;
    cout << "Nums generated\n";

    auto start = std::chrono::high_resolution_clock::now();
    countingSort(a, N);
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    std::cout << "Time: " << elapsed.count() << " seconds\n";


    //for (auto& i : a) cout << i << ' ';
    cout << a[0] << ' ' << a[N - 1];
    delete[] a;
}