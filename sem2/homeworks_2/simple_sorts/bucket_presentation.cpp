#include <iostream>
using namespace std;

void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(float* a, int n) {
    float mx = a[0];
    float mn = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > mx) mx = a[i];
        if (a[i] < mn) mn = a[i];
    }

    int bucket_count = n;
    float** buckets = new float*[bucket_count];
    int* bucket_sizes = new int[bucket_count]();

    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = new float[n];
        bucket_sizes[i] = 0;
    }

    float range = mx - mn;
    if (range == 0) range = 1;

    for (int i = 0; i < n; i++) {
        int bucket_index = (a[i] - mn) * (bucket_count - 1) / range;
        if (bucket_index >= bucket_count) bucket_index = bucket_count - 1;

        buckets[bucket_index][bucket_sizes[bucket_index]++] = a[i];
    }

    for (int i = 0; i < bucket_count; i++)
        if (bucket_sizes[i] > 0)
            insertionSort(buckets[i], bucket_sizes[i]);



    int idx = 0;
    for (int i = 0; i < bucket_count; i++)
        for (int j = 0; j < bucket_sizes[i]; j++)
            a[idx++] = buckets[i][j];

    delete[] bucket_sizes;
    for (int i = 0; i < bucket_count; i++)
        delete[] buckets[i];
    delete[] buckets;
}

int main() {
    float a[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94};
    int n = sizeof(a)/sizeof(a[0]);

    cout << "До сортировки: ";
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << endl;

    bucketSort(a, n);

    cout << "После сортировки: ";
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << endl;
}