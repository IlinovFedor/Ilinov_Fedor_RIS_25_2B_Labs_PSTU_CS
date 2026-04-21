#include <iostream>
#include "../../lab11/stack/stack.h"

using namespace std;

int main() {
    Stack<char> stack;
    string s;
    cin >> s;

    bool isOk = true;
    int idx = 0;
    for (auto c : s) {
        if (c == '(' ||
            c == '[' ||
            c == '{')
            stack.push(c);
        else if (stack.peek().node != nullptr &&
            (c == ')' && stack.peek().node->data == '(' ||
            c == ']' && stack.peek().node->data == '[' ||
            c == '}' && stack.peek().node->data == '{'))
            stack.pop();
        else {
            isOk = false;
            idx++;
        }
    }

    if (stack.size != 0)
        isOk = false;

    cout << s << '\n';
    if (isOk) {
        cout << "ok";
        return 0;
    }

    for (int i = 0; i < idx; i++)
        cout << ' ';

    cout << "^\nisn't ok";

}