#include "stack.h"
#include "errors.h"
#include <iostream>

template<class T>
void Stack<T>::push(T &data) {
    auto node = new StackNode<T>;
    node->data = data;
    if (size == 0) {
        head = node;
        size++;
        return;
    }

    node->next = head;
    head = node;
    size++;
}

template<class T>
void Stack<T>::pop() {
    if (size == 0)
        return;

    auto del = head;
    head = head->next;

    delete del;
    size--;
}

template<class T>
StackResult<T> Stack<T>::peek() {
    StackResult<T> res;
    if (head == nullptr) {
        res.error = outOfRange;
        return res;
    }
    res.node = head;
    return res;
}

template<class T>
void Stack<T>::print(std::ostream &stream) {
    if (size == 0) {
        stream << "empty\n";
        return;
    }
    auto node = head;
    while (node != nullptr) {
        stream << node->data << ' ';
        node = node->next;
    }
    stream << '\n';
}

template<class T>
void Stack<T>::clear() {
    auto node = head;
    while (node != nullptr) {
        auto tmp = node->next;
        delete node;
        node = tmp;
    }
    head = nullptr;
    size = 0;
}

int mainStack() {
    using namespace std;
    Stack<string> stack;
    bool f = true;
    while (f) {
        cout << "a - add, c - clear, d - pop, e - exit, g - peek, p - print\n";
        char cmd;
        string s;
        cin >> cmd;
        switch (cmd) {
            case 'a':
                cout << "Enter value: ";
                cin >> s;
                stack.push(s);
                break;
            case 'c':
                stack.clear();
                break;
            case 'd':
                stack.pop();
                break;
            case 'e':
                f = false;
                break;
            case 'g': {
                auto peek = stack.peek();
                if (peek.error != 0) {
                    cout << "empty\n";
                    break;
                }
                cout << peek.node->data << '\n';
                break;
            }
            case 'p':
                stack.print(cout);
                break;
            default:
                cout << "command not found";
        }
    }
    stack.clear();
    return 0;
}
