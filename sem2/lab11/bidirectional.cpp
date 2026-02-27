#include <iostream>

using namespace std;

#ifndef STRING_SIZE
#define STRING_SIZE 256
#endif

struct BiNode {
    BiNode* prev = nullptr;
    char* data;
    BiNode* next = nullptr;
};

struct BiList {
    BiNode* head = nullptr;
    BiNode* tail = nullptr;

    void pushBack(char*);
    void popBack();

    void pushFront(char*);
    void popFront();

    void insert(int, char*);
    void remove(int);
    char* get(int);
    int find(char *);

    void print();
    void clear();
};

void BiList::pushBack(char * data) {
    auto newNode = new BiNode;
    newNode->data = data;

    if (head == nullptr || tail == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

void BiList::popBack() {
    if (tail == nullptr)
        return;
    if (tail == head) {
        delete[] tail->data;
        delete tail;
        tail = nullptr;
        head = nullptr;
        return;
    }

    auto tmp = tail->prev;
    tmp->next = nullptr;
    delete[] tail->data;
    delete tail;
    tail = tmp;
}


void BiList::pushFront(char * data) {
    auto newNode = new BiNode;
    newNode->data = data;

    if (head == nullptr || tail == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    head->prev = newNode;
    newNode->next = head;
    head = newNode;
}

void BiList::popFront() {
    if (head == nullptr)
        return;
    if (tail == head) {
        delete[] tail->data;
        delete tail;
        tail = nullptr;
        head = nullptr;
        return;
    }

    auto tmp = head->next;
    tmp->prev = nullptr;
    delete[] head->data;
    delete head;
    head = tmp;
}

void BiList::insert(int idx, char * data) {
    if (idx == 0) {
        pushFront(data);
        return;
    }

    auto newNode = new BiNode;
    newNode->data = data;

    auto node = head;
    int i = 0;
    while (node->next != nullptr && i != idx) {
        node = node->next;
        i++;
    }
    if (i + 1 == idx) {
        pushBack(data);
        return;
    }
    if (i != idx) {
        cout << "out of range\n";
        delete newNode;
        return;
    }


    newNode->prev = node->prev;
    newNode->next = node;
    node->prev->next = newNode;
    node->prev = newNode;
}

void BiList::remove(int idx) {
    if (head == nullptr) {
        cout << "cannot remove: empty\n";
        return;
    }

    auto node = head;
    int i = 0;
    while (node->next != nullptr && i != idx) {
        node = node->next;
        i++;
    }
    if (i != idx) {
        cout << "cannot remove: out of range\n";
        return;
    }
    if (i == 0) {
        popFront();
        return;
    }
    if (node->next == nullptr) {
        popBack();
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete[] node->data;
    delete node;
}

char *BiList::get(int idx) {
    if (head == nullptr) {
        cout << "cannot get: empty\n";
        return nullptr;
    }

    auto node = head;
    int i = 0;
    while (node->next != nullptr && i != idx) {
        node = node->next;
        i++;
    }
    if (i != idx) {
        cout << "cannot get: out of range\n";
        return nullptr;
    }

    return node->data;
}


int BiList::find(char * s) {
    int i = 0;
    auto node = head;
    if (node == nullptr) {
        cout << "cannot find: empty\n";
        return -1;
    }
    while (node->next != nullptr) {
        bool f = true;
        for (int j = 0; j < STRING_SIZE && f; j++) {
            if (node->data[j] != '\0' && s[j] != '\0') {
                if (node->data[j] != s[j])
                    f = false;
            }
        }
        if (f)
            return i;
        i++;
        node = node->next;
    }
    bool f = true;
    for (int j = 0; j < STRING_SIZE && f; j++) {
        if (node->data[j] != '\0' && s[j] != '\0') {
            if (node->data[j] != s[j])
                f = false;
        }
    }
    if (f)
        return i;

    return -1;
}

void BiList::print() {
    auto node = head;
    if (node == nullptr) {
        cout << "empty\n";
        return;
    }

    while (node->next != nullptr) {
        cout << node->data << ' ';
        node = node->next;
    }
    cout << node->data << '\n';
}

void BiList::clear() {
    while (head != nullptr)
        popFront();
}
