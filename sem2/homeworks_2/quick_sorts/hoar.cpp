#include <chrono>
#include <climits>
#include <iostream>

using namespace std;

int cnt = 0;
template<class T>
int partition(T* a, int l, int r) {
    T v = a[(l + r) / 2];
    int i = l;
    int j = r;
    bool f = true;
    while (i <= j && f) {
        while (a[i] < v) i++;
        while (a[j] > v) j--;
        if (i >= j) {
            f = false;
            continue;
        }

        T tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        i++;
        j--;
    }
    for (int i = 0; i < 8; i++) cout << a[i] << ' ';
    cout << '\n';
    return j;
}

int step = 0;
template<class T>
void hoarSort(T* a, int l, int r) {
    if (l < r) {
        int q = partition(a, l, r);
        hoarSort(a, l, q);
        hoarSort(a, q + 1, r);
    }
}

constexpr long long N = 8LL;
int main() {
    // int* a = new int[N];
    // uint64_t seed = 123456789;
    //
    // auto fast_rand = [&]() {
    //     seed ^= seed << 13;
    //     seed ^= seed >> 7;
    //     seed ^= seed << 17;
    //     return (int)seed;
    // };
    //
    // for (long long i = 0; i < N; ++i)
    //     a[i] = fast_rand() % 10;
    int a[] = {2, 4, 6, 8, 1, 5, 3, 7};
    cout << "Nums generated\n";
    for (int i = 0; i < N; i++) cout << a[i] << ' ';
    cout << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    hoarSort(a, 0, N - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time: " << elapsed.count() << " seconds\n";


    for (int i = 0; i < N; i++) cout << a[i] << ' ';
    cout << '\n'
    //delete[] a;
}