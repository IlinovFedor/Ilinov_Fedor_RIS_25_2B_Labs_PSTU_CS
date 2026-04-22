#include "Human.h"
#include "LinearMap.h"
#include "ChainMap.h"
#include <iostream>

int main() {
    Human humans[10];
    for (auto & human : humans) human = Human();

    LinearMap linear;
    linear.createTable(10);

    for (auto & human : humans) linear.add(human);

    std::cout << "Find index for " << humans[1].getBirthday() << ": "
              << linear.findIndex(humans[1].getBirthday()) << '\n';
    linear.show();

    linear.pop(humans[1].getBirthday());
    std::cout << "After delete:\n";
    linear.show();
    std::cout << "Linear collisions: " << collision_count << "\n\n";
    linear.clearTable();

    ChainMap chain;
    chain.createTable(5);

    collision_count = 0;
    for (auto & human : humans) chain.add(human);

    std::cout << "Find index for " << humans[0].getBirthday() << ": "
              << chain.findIndex(humans[0].getBirthday()) << '\n';
    chain.show();

    chain.pop(humans[0].getBirthday());
    std::cout << "After delete:\n";
    chain.show();
    std::cout << "Chain collisions: " << collision_count << '\n';

    chain.clearTable();
    return 0;
}
