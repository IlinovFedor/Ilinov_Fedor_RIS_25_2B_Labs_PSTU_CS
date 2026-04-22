#ifndef ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_FILE_WORK_H
#define ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_FILE_WORK_H

#include "gpt_cal/Pair.h"
#include <cstdio>
#include <fstream>
#include <iostream>

int make_file(const std::string &f_name) {
    std::fstream stream(f_name, std::ios::out | std::ios::trunc);
    if (!stream) return -1;

    int n;
    Pair p;
    std::cout << "N? ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> p;
        stream << p;
    }
    stream.close();
    return n;
}

int print_file(const std::string &f_name) {
    std::fstream stream(f_name, std::ios::in);
    if (!stream) {
        return -1;
    }
    Pair p;
    int i = 0;
    while (stream >> p) {
        std::cout << p << "\n";
        i++;
    }
    stream.close();
    return i;
}

int del_less(const std::string &f_name, const Pair &key) {
    std::fstream temp("temp", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) {
        return -1;
    }
    Pair p;
    int removed = 0;
    while (stream >> p) {
        if (p < key) {
            removed++;
            continue;
        }
        temp << p;
    }
    stream.close();
    temp.close();
    remove(f_name.c_str());
    rename("temp", f_name.c_str());
    return removed;
}

int inc_equal(const std::string &f_name, const Pair &key, double l, bool is_int) {
    std::fstream temp("temp", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) {
        return -1;
    }
    Pair p;
    int changed = 0;
    while (stream >> p) {
        if (p == key) {
            if (is_int) p = p + static_cast<int>(l);
            else p = p + l;

            changed++;
        }
        temp << p;
    }
    stream.close();
    temp.close();
    remove(f_name.c_str());
    rename("temp", f_name.c_str());
    return changed;
}

int add_after(const std::string &f_name, int n, int k) {
    std::fstream temp("temp", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) return -1;

    Pair p;
    int i = 0;
    int added = 0;
    while (stream >> p) {
        i++;
        temp << p;
        if (i == n) {
            for (int j = 0; j < k; j++) {
                Pair pp;
                std::cin >> pp;
                temp << pp;
                added++;
            }
        }
    }
    if (i < n) {
        for (int j = 0; j < k; j++) {
            Pair pp;
            std::cin >> pp;
            temp << pp;
            added++;
        }
    }
    stream.close();
    temp.close();
    remove(f_name.c_str());
    rename("temp", f_name.c_str());
    return added;
}

#endif //ILINOV_FEDOR_RIS_25_2B_LABS_PSTU_CS_FILE_WORK_H
