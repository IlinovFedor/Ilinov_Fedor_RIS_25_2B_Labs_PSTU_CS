#include <chrono>
#include <climits>
#include <iostream>

using namespace std;

template<class T>
void merge(T* a, int l, int m, int r) {
    int i = 0, j = 0;
    T* res = new T[r - l];

    while (l + i < m && m + j < r) {
        if (a[l + i] < a[m + j]) {
            res[i + j] = a[l + i];
            i++;
        } else {
            res[i + j] = a[m + j];
            j++;
        }
    }

    while (l + i < m) {
        res[i + j] = a[l + i];
        i++;
    }

    while (m + j < r) {
        res[i + j] = a[m + j];
        j++;
    }

    for (int i = 0; i < r - l; i++)
        a[l + i] = res[i];

    delete[] res;
}

template<class T>
void mergeSort(T* a, int l, int r) {
    if (r - l <= 1)
        return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, m, r);
}

constexpr long long N = 1000000000LL;
int main() {
    int* a = new int[N];
    uint64_t seed = 123456789;

    auto fast_rand = [&]() {
        seed ^= seed << 13;
        seed ^= seed >> 7;
        seed ^= seed << 17;
        return (int)seed;
    };

    for (long long i = 0; i < N; ++i)
        a[i] = fast_rand();
    cout << "Nums generated\n";

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(a, 0, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time: " << elapsed.count() << " seconds\n";


    //for (auto& i : a) cout << i << ' ';
    cout << a[0] << ' ' << a[N - 1];
    delete[] a;
}