#include <iostream>

using namespace std;

enum chiselki {
    nolik,
    raz = 4,
    dva,
    tri,
    chetire,
    pyat
};

chiselki mem = pyat;
chiselki house(raz);

int main() {
    int a = tri;
    cout << a;
    int b = chiselki(pyat);
    cout << '\n' << b;

    cout << '\n' << house;
    cout << '\n' << mem;
}
