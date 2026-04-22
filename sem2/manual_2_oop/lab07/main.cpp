#include <iostream>
#include "Pair.h"
#include "bidirectional.h"

int main()
{
    BiList<Pair> l1, l2;
    std::cin >> l1 >> l2;
    std::cout << l1 << '\n' << l2 << '\n';
    std::cout << "l1[0] + l2[1]\n";
    std::cout << l1[0] + l2[1] << '\n';
    std::cout << "Multiplication:\n" << l1 * l2;
}

