#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class ManoVektorius {

    private:
    T* data_;
    size_t size_;
    size_t capacity_;

    public:
    ManoVektorius();
    ManoVektorius(std::initializer_list<T> list) {
    size_ = list.size();
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(list.begin(), list.end(), data_);
}
    ~ManoVektorius();

    void push_back(const T& value);
    void pop_back();
    void reallocate(size_t new_capacity);
    T& operator[](size_t index);
    T& at(size_t index);
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
    void clear();
    void erase(size_t index);

    // 1. Add back() support
T& back() {
    return data_[size_ - 1];
}

const T& back() const {
    return data_[size_ - 1];
}

// 2. Add begin() and end() for range-based for-loops
T* begin() {
    return data_;
}

T* end() {
    return data_ + size_;
}

const T* begin() const {
    return data_;
}

const T* end() const {
    return data_ + size_;
}

// 3. Make operator[] work in const contexts

const T& operator[](size_t index) const {
    return data_[index];
}



};
 #endif