#include "gpt_cal/Pair.h"
#include "file_work.h"
#include <iostream>

int main() {
    std::string file_name;
    int c = 0;
    do {
        std::cout << "\n1. Make file";
        std::cout << "\n2. Print file";
        std::cout << "\n3. Delete records less than key";
        std::cout << "\n4. Increase records equal to key";
        std::cout << "\n5. Add K records after N";
        std::cout << "\n0. Exit\n";
        std::cin >> c;
        switch (c) {
            case 1: {
                std::cout << "file name? ";
                std::cin >> file_name;
                int k = make_file(file_name);
                if (k < 0) std::cout << "Can't make file\n";

                break;
            }
            case 2: {
                std::cout << "file name? ";
                std::cin >> file_name;
                int k = print_file(file_name);
                if (k == 0) std::cout << "Empty file\n";

                if (k < 0) std::cout << "Can't read file\n";

                break;
            }
            case 3: {
                std::cout << "file name? ";
                std::cin >> file_name;
                Pair key;
                std::cout << "Key pair (int double): ";
                std::cin >> key;
                int k = del_less(file_name, key);
                if (k < 0) std::cout << "Can't read file\n";

                break;
            }
            case 4: {
                std::cout << "file name? ";
                std::cin >> file_name;
                Pair key;
                std::cout << "Key pair (int double): ";
                std::cin >> key;
                std::cout << "Constant type (1-int, 2-double)? ";
                int kind = 0;
                std::cin >> kind;
                int count = 0;
                if (kind == 1) {
                    int l;
                    std::cout << "L? ";
                    std::cin >> l;
                    count = inc_equal(file_name, key, l, true);
                } else {
                    double l;
                    std::cout << "L? ";
                    std::cin >> l;
                    count = inc_equal(file_name, key, l, false);
                }
                if (count < 0) std::cout << "Can't read file\n";

                break;
            }
            case 5: {
                std::cout << "file name? ";
                std::cin >> file_name;
                int n = 0;
                int k = 0;
                std::cout << "N? ";
                std::cin >> n;
                std::cout << "K? ";
                std::cin >> k;
                int added = add_after(file_name, n, k);
                if (added < 0) std::cout << "Can't read file\n";

                break;
            }
            default:
                break;
        }
    } while (c != 0);
    return 0;
}
