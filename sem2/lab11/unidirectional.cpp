#include <iostream>

using namespace std;

#ifndef STRING_SIZE
#define STRING_SIZE 256
#endif

struct UniNode {
    char* data;
    UniNode* next = nullptr;
};

struct UniList {
    UniNode* head = nullptr;

    void pushBack(char*);
    void popBack();

    void pushFront(char*);
    void popFront();

    void insert(int, char*);
    void remove(int);
    char* get(int);
    int find(char*);

    void print();
    void clear();
};

void UniList::pushBack(char * data) {
    auto newNode = new UniNode;
    newNode->data = data;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    auto node = head;
    while (node->next != nullptr)
        node = node->next;
    
    node->next = newNode;
}

void UniList::popBack() {
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete[] head->data;
        delete head;
        head = nullptr;
        return;
    }

    auto node = head;
    auto prev = head;
    while (node->next != nullptr) {
        prev = node;
        node = node->next;
    }

    prev->next = nullptr;
    delete[] node->data;
    delete node;
}


void UniList::pushFront(char * data) {
    auto newNode = new UniNode;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

void UniList::popFront() {
    if (head == nullptr)
        return;
    auto tmp = head;
    head = head->next;
    delete[] tmp->data;
    delete tmp;
}

void UniList::insert(int idx, char * data) {
    if (idx == 0) {
        pushFront(data);
        return;
    }

    auto newNode = new UniNode;
    newNode->data = data;

    auto node = head;
    int i = 0;
    while (node->next != nullptr && i != idx - 1) {
        node = node->next;
        i++;
    }
    if (i != idx - 1) {
        cout << "out of range\n";
        delete newNode;
        return;
    }

    auto tmp = node->next;
    node->next = newNode;
    newNode->next = tmp;
}

void UniList::remove(int idx) {
    if (head == nullptr) {
        cout << "cannot remove: empty\n";
        return;
    }

    auto node = head;
    auto prev = head;
    int i = 0;
    while (node->next != nullptr && i != idx) {
        prev = node;
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


    prev->next = node->next;
    delete[] node->data;
    delete node;
}

char *UniList::get(int idx) {
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

int UniList::find(char * s) {
    int i = 0;
    auto node = head;
    if (node == nullptr) {
        cout << "cannot find: empty\n";
        return -1;
    }
    while (node->next != nullptr) {
        bool f = true;
        for (int j = 0; j < STRING_SIZE && f; j++) {
            if (node->data[j] != s[j])
                f = false;
        }
        if (f)
            return i;
        i++;
        node = node->next;
    }
    return -1;
}

void UniList::print() {
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

void UniList::clear() {
    while (head != nullptr)
        popBack();
}