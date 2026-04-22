#ifndef PSTU_TEACHING_ERRORS_H
#define PSTU_TEACHING_ERRORS_H
#include <stdexcept>
#include <string>

class ListSizeError : public std::length_error {
public:
    ListSizeError(int requestedSize, int maxSize)
            : std::length_error("BiList(int): requested size " + std::to_string(requestedSize) +
                                " exceeds max_size " + std::to_string(maxSize)) {}
};

class ListIndexError : public std::out_of_range {
public:
    ListIndexError(int index, int currentSize)
            : std::out_of_range("BiList::operator[]: index " + std::to_string(index) +
                                " is out of range [0 ; " + std::to_string(currentSize) + ')') {}
};

class IteratorPlusRangeError : public std::out_of_range {
public:
    IteratorPlusRangeError(int shift)
            : std::out_of_range("Iterator::operator+: invalid shift " + std::to_string(shift) +
             " (shift moves iterator past end)") {}
};

class ListMultiplySizeError : public std::invalid_argument {
public:
    ListMultiplySizeError(int leftSize, int rightSize)
            : std::invalid_argument("BiList::operator*: size mismatch (left=" + std::to_string(leftSize) +
                                    ", right=" + std::to_string(rightSize) + ")") {}
};

#endif //PSTU_TEACHING_ERRORS_H
