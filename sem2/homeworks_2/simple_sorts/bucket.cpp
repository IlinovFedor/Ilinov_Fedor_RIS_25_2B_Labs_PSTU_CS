#include <iostream>

double* bucketSort(double* array, int n, double minElement, double maxElement, int numBuckets, int &outSize) {
    if (n < 2 || minElement == maxElement) {
        double* res = new double[n];
        for (int i = 0; i < n; i++)
            res[i] = array[i];
        outSize = n;
        return res;
    }

    double** buckets = new double*[numBuckets];
    int* counts = new int[numBuckets];
    double* minBuckets = new double[numBuckets];
    double* maxBuckets = new double[numBuckets];

    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = new double[n];
        counts[i] = 0;
        minBuckets[i] = maxElement;
        maxBuckets[i] = minElement;
    }

    double range = maxElement - minElement;

    for (int i = 0; i < n; i++) {
        int index = 0;
        if (range > 0)
            index = int((array[i] - minElement) * numBuckets / range);
        if (index == numBuckets) index--;

        buckets[index][counts[index]++] = array[i];

        if (array[i] < minBuckets[index]) minBuckets[index] = array[i];
        if (array[i] > maxBuckets[index]) maxBuckets[index] = array[i];
    }


    double** sortedBuckets = new double*[numBuckets];
    int* sortedSizes = new int[numBuckets];

    for (int i = 0; i < numBuckets; i++) {
        sortedBuckets[i] = bucketSort(buckets[i], counts[i], minBuckets[i], maxBuckets[i], numBuckets, sortedSizes[i]);
    }


    int totalSize = 0;
    for (int i = 0; i < numBuckets; i++)
        totalSize += sortedSizes[i];

    double* answer = new double[totalSize];
    int idx = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int k = 0; k < sortedSizes[i]; k++)
            answer[idx++] = sortedBuckets[i][k];
        delete[] sortedBuckets[i];
        delete[] buckets[i];
    }

    delete[] sortedBuckets;
    delete[] buckets;
    delete[] counts;
    delete[] sortedSizes;
    delete[] minBuckets;
    delete[] maxBuckets;

    outSize = totalSize;
    return answer;
}

int main() {
    double a[10] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    int n = 10;

    int outSize = 0;
    int numBuckets = n;
    double* sorted = bucketSort(a, n, 0.0, 1.0, numBuckets, outSize);

    for (int i = 0; i < outSize; i++)
        std::cout << a[i] << ' ';
    delete[] sorted;
}