/*
1) Реализовать с использованием массива однонаправленное
кольцо (просмотр возможен справа налево, от первого
элемента можно перейти к последнему).
2) Распечатать полученный массив, начиная с К-ого элемента
и до К+1.
3) Упорядочить элементы по убыванию
4) Удалить из кольца нечетные элементы.
5) Распечатать полученный массив, начиная с К-ого элемента
и до К+1.
*/

#include <iostream>

using namespace std;

int s;


void print(int* a, int s) {
    int k = s + 1;
    if (s == 0) {
        cout << "Кольцо пустое!\n";
        return;
    }

    while (k > s || k < 1) {
        cout << "Введите k, не большее чем размер кольца: " << s << '\n';
        cin >> k;
    }
    cout << "Ваше кольцо, начиная с " << k << " элемента справа налево:\n";
    for (int i = k - 1; i >= 0; i--) {
        cout << a[i] << ' ';
    }
    for (int i = s - 1; i >= k; i--) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

void sortDesc(int* a, int s) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s - 1; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    cout << "Кольцо отсортировано по убыванию справа налево.\n";
}

void deleteOdd(int* a, int* s) {
    int cnt = 0;
    int pos = 0;
    for (int i = *s - 1; i >= 0; i--)
        if (abs(a[i]) % 2 == 0)
            cnt++;

    while (pos != cnt) {
        bool f = true;
        int n = 0;
        for (int j = *s - 1; j >= 0 && f; j--) {
            if (abs(a[j]) % 2 == 0) n++;
            if (n == cnt - pos) {
                a[pos] = a[j];
                pos++;
                f = false;
            }
        }
    }
    *s = cnt;
    cout << "Из кольца удалены нечетные числа.\n";
}

int main() {
    while (s < 2) {
        cout << "Введите размер (минимум 2):\n";
        cin >> s;
    }
    int a[s];
    cout << "Введите элементы справа налево:\n";
    for (int i = s - 1; i >= 0; i--)
        cin >> a[i];

    print(a, s);

    sortDesc(a, s);
    deleteOdd(a, &s);

    print(a, s);
}