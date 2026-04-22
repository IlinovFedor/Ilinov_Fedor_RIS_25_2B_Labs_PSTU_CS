#include "Magazine.h"

#include <iostream>

Magazine::Magazine() {
    title = "Unknown";
    pages = 5;
}

Magazine::Magazine(std::string name, std::string author, std::string subject, int pages) : Print(name, author) {
    this->title = subject;
    this->pages = pages;
}

Magazine::Magazine(Print p, std::string subject, int pages) : Print(p){
    this->title = subject;
    this->pages = pages;
}

Magazine::Magazine(Magazine & p) {
    title = p.title;
    pages = p.pages;
}

Magazine::~Magazine() {
    title = "Unknown";
    pages = 5;
}

std::string Magazine::getTitle() {
    return title;
}

void Magazine::setTitle(std::string s) {
    title = s;
}

int Magazine::getPages() {
    return pages;
}

void Magazine::setPages(int a) {
    pages = a;
}

Magazine &Magazine::operator=(Magazine &p) {
    this->setName(p.getName());
    this->setPages(p.getPages());
    title = p.title;
    pages = p.pages;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, Magazine &p) {
    std::cout << "Magazine:";
    std::cout << "\n\tPrint's name: " << p.getName();
    std::cout << "\n\tPrint's author: " << p.getAuthor();
    std::cout << "\n\tMagazine's title: " << p.getTitle();
    std::cout << "\n\tNumber of pages: " << p.getPages();
    return stream;
}

std::istream &operator>>(std::istream &stream, Magazine &p) {
    std::cout << "Name? ";
    std::string s;
    stream >> s;
    p.setName(s);
    std::cout << "Author? ";
    std::string a;
    stream >> a;
    p.setAuthor(a);
    std::cout << "Title? ";
    stream >> p.title;
    std::cout << "Pages? ";
    stream >> p.pages;
    return stream;
}

void Magazine::show() {
    std::cout << *this;
}

void Magazine::input() {
    std::cin >> *this;
}
