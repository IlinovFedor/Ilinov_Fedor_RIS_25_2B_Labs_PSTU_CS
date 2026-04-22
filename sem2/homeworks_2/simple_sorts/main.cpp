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

struct Person {
    std::string name;
    int height;

    void print() {
        cout << "\t\t" << name << ": " << height << "cm\n";
    }
};

int main() {
    cout << "Bucket sort\n";
    float bucket[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94};
    int n = 6;

    cout << "\tДо сортировки:\n\t\t";
    for (int i = 0; i < n; i++) cout << bucket[i] << ' ';
    cout << endl;

    bucketSort(bucket, n);

    cout << "\tПосле сортировки:\n\t\t";
    for (int i = 0; i < n; i++) cout << bucket[i] << ' ';
    cout << endl;

    cout << "Counting sort\n";
    Person persons[] = {
        {"Алексей", 178},
        {"Мария", 165},
        {"Дмитрий", 182},
        {"Анна", 170},
        {"Иван", 165},
        {"Елена", 175}
    };;

    cout << "\tДо сортировки:\n";
    for (auto &i: persons) i.print();

    countingSort(persons, 6);
    cout << "\n\tПосле сортировки:\n";
    for (auto &i: persons) i.print();

    cout << "Merge sort\n";
    float doubles[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94};

    cout << "\tДо сортировки:\n\t\t";
    for (int i = 0; i < n; i++) cout << doubles[i] << ' ';
    cout << endl;

    mergeSort(doubles, 0, n - 1);

    cout << "\tПосле сортировки:\n\t\t";
    for (int i = 0; i < n; i++) cout << doubles[i] << ' ';
    cout << endl;

}