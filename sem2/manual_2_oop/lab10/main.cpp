#include "Pair.h"
#include "file_work.h"
#include <iostream>

using namespace std;

int main() {
    int c = 0;
    char file_name[30];
    do {
        cout << "\n1. Make file";
        cout << "\n2. Print file";
        cout << "\n3. Delete records less than key";
        cout << "\n4. Increase records equal to key";
        cout << "\n5. Add K records after N";
        cout << "\n0. Exit\n";
        cin >> c;
        switch (c) {
            case 1: {
                cout << "file name?";
                cin >> file_name;
                int k = make_file(file_name);
                if (k < 0) {
                    cout << "Can't make file";
                }
                break;
            }
            case 2: {
                cout << "file name?";
                cin >> file_name;
                int k = print_file(file_name);
                if (k == 0) {
                    cout << "Empty file\n";
                }
                if (k < 0) {
                    cout << "Can't read file\n";
                }
                break;
            }
            case 3: {
                cout << "file name?";
                cin >> file_name;
                Pair key;
                cout << "Key pair (int double):";
                cin >> key;
                int k = del_less(file_name, key);
                if (k < 0) {
                    cout << "Can't read file\n";
                }
                break;
            }
            case 4: {
                cout << "file name?";
                cin >> file_name;
                Pair key;
                cout << "Key pair (int double):";
                cin >> key;
                cout << "Constant type (1-int, 2-double)?";
                int kind = 0;
                cin >> kind;
                int count = 0;
                if (kind == 1) {
                    int l;
                    cout << "L?";
                    cin >> l;
                    count = inc_equal(file_name, key, l, true);
                } else {
                    double l;
                    cout << "L?";
                    cin >> l;
                    count = inc_equal(file_name, key, l, false);
                }
                if (count < 0) {
                    cout << "Can't read file\n";
                }
                break;
            }
            case 5: {
                cout << "file name?";
                cin >> file_name;
                int n = 0;
                int k = 0;
                cout << "N?";
                cin >> n;
                cout << "K?";
                cin >> k;
                int added = add_after(file_name, n, k);
                if (added < 0) {
                    cout << "Can't read file\n";
                }
                break;
            }
            default:
                break;
        }
    } while (c != 0);
    return 0;
}
