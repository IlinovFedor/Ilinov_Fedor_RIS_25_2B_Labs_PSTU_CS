#include "../queue.h"
#include "../errors.h"
#include <iostream>

template<class T>
void Queue<T>::pushBack(T& data) {
    auto node = new QueueNode<T>;
    node->data = data;
    if (size == 0) {
        head = node;
        tail = node;
        size++;
        return;
    }

    tail->next = node;
    tail = node;
    size++;
}

template<class T>
void Queue<T>::popFront() {
    if (size == 0)
        return;

    auto del = head;
    head = head->next;

    if (head == nullptr)
        tail = nullptr;

    delete del;
    size--;
}

template<class T>
QueueResult<T> Queue<T>::insert(int idx, T & data) {
    QueueResult<T> res;
    if (idx == 0) {
        auto node = new QueueNode<T>;
        node->data = data;
        node->next = head;
        head = node;
        size++;
        return res;
    }

    if (!(0 < idx && idx < size)) {
        res.error = outOfRange;
        return res;
    }

    auto node = head;
    for (int i = 0; i < idx - 1; i++)
        node = node->next;

    auto newNode = new QueueNode<T>;
    newNode->data = data;
    newNode->next = node->next;
    node->next = newNode;

    res.node = newNode;
    size++;
    return res;
}

template<class T>
QueueResult<T> Queue<T>::peek() {
    QueueResult<T> res;
    if (head == nullptr) {
        res.error = outOfRange;
        return res;
    }
    res.node = head;
    return res;
}


template<class T>
void Queue<T>::print(std::ostream& stream) {
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
void Queue<T>::clear() {
    auto node = head;
    while (node != nullptr) {
        auto tmp = node->next;
        delete node;
        node = tmp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

int main() {
    using namespace std;
    Queue<string> stack;
    bool f = true;
    while (f) {
        cout << "a - add, c - clear, d - pop, e - exit, g - peek, i - insert before, p - print\n";
        char cmd;
        string s;
        cin >> cmd;
        switch (cmd) {
            case 'a':
                cout << "Enter value: ";
                cin >> s;
                stack.pushBack(s);
                break;
            case 'c':
                stack.clear();
                break;
            case 'd':
                stack.popFront();
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
            case 'i':
                int idx;
                cout << "Enter index: ";
                cin >> idx;
                cout << "Enter value: ";
                cin >> s;
                stack.insert(idx, s);
                break;
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
