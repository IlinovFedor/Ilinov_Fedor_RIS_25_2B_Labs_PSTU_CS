#include "Human.h"

#include <ios>
#include <random>

std::string Human::createRandomName() {
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghjklmnpqrstvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distVowels(0, vowels.size() - 1);
    std::uniform_int_distribution<> distConsonants(0, consonants.size() - 1);
    std::uniform_int_distribution<> distNameLen(3, 6);
    std::uniform_int_distribution<> distSurnameLen(4, 9);

    std::string n;
    int nameLen = distNameLen(gen);
    std::string s;
    int surnameLen = distSurnameLen(gen);

    for (int i = 0; i < nameLen; i++) {
        if (i & 1) n += vowels[distVowels(gen)];
        else n += consonants[distConsonants(gen)];
    }
    for (int i = 0; i < surnameLen; i++) {
        if (i & 1) s += vowels[distVowels(gen)];
        else s += consonants[distConsonants(gen)];
    }

    n[0] = std::toupper(n[0]);
    s[0] = std::toupper(s[0]);
    return n + " " + s;
}

std::string Human::createRandomBirthday() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distYear(1970, 2026);
    std::uniform_int_distribution<> distMonth(1, 12);
    std::uniform_int_distribution<> distDay(1, 28);

    int year = distYear(gen);
    int month = distMonth(gen);
    int day = distDay(gen);

    return std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
}

std::string Human::createRandomPassportNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distLetter('A', 'Z');
    std::uniform_int_distribution<> distNumber(100000000, 999999999);


    char firstLetter = distLetter(gen);
    char secondLetter = distLetter(gen);
    int num = distNumber(gen);

     return std::string(1, firstLetter)
          + std::string(1, secondLetter)
          + std::to_string(num);}

int Human::dateToNumber(const std::string &s) const {
    std::string digits;
    digits.reserve(s.size());
    for (char ch : s) {
        if (ch >= '0' && ch <= '9')
            digits.push_back(ch);
    }
    if (digits.empty())
        return 0;
    try {
        return std::stoi(digits);
    } catch (...) {
        return 0;
    }
}

Human::Human() {
    name = createRandomName();
    birthday = createRandomBirthday();
    passportNumber = createRandomPassportNumber();
}

std::ostream& operator<<(std::ostream& stream, const Human& h) {
    stream << h.name << " | " << h.birthday << " | " << h.passportNumber;
    return stream;
}

std::istream& operator>>(std::istream& stream, Human& h) {
    std::string nameInput;
    std::string birthdayInput;
    std::string passportInput;

    if (!std::getline(stream >> std::ws, nameInput, '|')) {
        return stream;
    }
    if (!std::getline(stream >> std::ws, birthdayInput, '|')) {
        return stream;
    }
    if (!std::getline(stream >> std::ws, passportInput)) {
        return stream;
    }

    while (!nameInput.empty() && nameInput.back() == ' ') {
        nameInput.pop_back();
    }
    while (!birthdayInput.empty() && birthdayInput.back() == ' ') {
        birthdayInput.pop_back();
    }
    while (!passportInput.empty() && passportInput.back() == ' ') {
        passportInput.pop_back();
    }

    h.name = nameInput;
    h.birthday = birthdayInput;
    h.passportNumber = passportInput;
    return stream;
}
