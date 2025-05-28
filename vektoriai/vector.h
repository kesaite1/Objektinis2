#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

template <typename T>
class ManoVektorius {

    private:
    T* data_;
    size_t size_;
    size_t capacity_;
    size_t realloc_count_ = 0; 

    public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    ManoVektorius();
    ManoVektorius(std::initializer_list<T> list) {
    size_ = list.size();
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(list.begin(), list.end(), data_);
}

ManoVektorius(const ManoVektorius& other);
ManoVektorius& operator=(const ManoVektorius& other);
ManoVektorius(ManoVektorius&& other) noexcept; //  move constructor
ManoVektorius& operator=(ManoVektorius&& other) noexcept; //  move assignment
~ManoVektorius();


size_t getReallocationCount() const {
    return realloc_count_;
}

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void reallocate(size_t new_capacity);
    void clear();
    void erase(size_t index);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
   
    const T* end() const;
    const T* begin() const;
    T* begin();
    T* end();
    T& back();
    const T& back() const;
};

template <typename T>
ManoVektorius<T>::ManoVektorius() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
ManoVektorius<T>::ManoVektorius(const ManoVektorius<T>& other)
    : size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
ManoVektorius<T>& ManoVektorius<T>::operator=(const ManoVektorius<T>& other) {
    if (this == &other) return *this;

    T* new_data = new T[other.capacity_];
    for (size_t i = 0; i < other.size_; ++i) {
        new_data[i] = other.data_[i];
    }

    delete[] data_; // istrinti sena atminti
    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}


template <typename T>
ManoVektorius<T>::ManoVektorius(ManoVektorius<T>&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
ManoVektorius<T>& ManoVektorius<T>::operator=(ManoVektorius<T>&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
ManoVektorius<T>::~ManoVektorius() {
    delete[] data_;
}
//-----------------------------------------------------
template <typename T>
void ManoVektorius<T>::push_back(const T& value) {
   // cout<<"push_back be move\n";
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
   // cout<<"push_back be move completed\n";
}

template <typename T>
void ManoVektorius<T>::push_back(T&& value) {
  //  cout<<"push_back su move\n";
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
   // cout<<"push_back su move completed\n";
}
//-----------------------------------------------------
template <typename T>
void ManoVektorius<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
void ManoVektorius<T>::reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i)
        new_data[i] = std::move(data_[i]);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    ++realloc_count_;
}

template <typename T>
void ManoVektorius<T>::clear() {
    size_ = 0;
}

template <typename T>
void ManoVektorius<T>::erase(std::size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of bounds");
    for (std::size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}
//-----------------------------------------------------
template <typename T>
T& ManoVektorius<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T& ManoVektorius<T>::operator[](size_t index) const {
    return data_[index];
}

template <typename T>
T& ManoVektorius<T>::at(size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}
//-----------------------------------------------------
template <typename T>
size_t ManoVektorius<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t ManoVektorius<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool ManoVektorius<T>::empty() const noexcept {
    return size_ == 0;
}
//-----------------------------------------------------
template <typename T>
T& ManoVektorius<T>::back() {
    return data_[size_ - 1];
}

template <typename T>
const T& ManoVektorius<T>::back() const {
    return data_[size_ - 1];
}

template <typename T>
T* ManoVektorius<T>::begin() {
    return data_;
}

template <typename T>
T* ManoVektorius<T>::end() {
    return data_ + size_;
}

template <typename T>
const T* ManoVektorius<T>::begin() const {
    return data_;
}

template <typename T>
const T* ManoVektorius<T>::end() const {
    return data_ + size_;
}

 #endif