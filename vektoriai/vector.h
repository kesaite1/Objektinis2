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
#include "my.h"
#include "code.h"

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
    ManoVektorius(size_t n);
    ManoVektorius(std::initializer_list<T> list) {
    size_ = list.size();
    capacity_ = size_;
    data_ = new T[capacity_];
    copy(list.begin(), list.end(), data_);
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
    void reserve(size_t new_cap);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
    void resize(size_t new_size);
    void shrink_to_fit();
   
    const T* end() const;
    const T* begin() const;
    T* begin();
    T* end();
    T& back();
    const T& back() const;
    void insert(size_t index, const T& value);
    T& front(); 
    const T& front() const; 
    void swap(ManoVektorius<T>& other);
};

template <typename T>
ManoVektorius<T>::ManoVektorius() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
ManoVektorius<T>::ManoVektorius(size_t n) 
    : data_(static_cast<T*>(::operator new[](n * sizeof(T)))), size_(n), capacity_(n) 
{
    for (std::size_t i = 0; i < n; ++i)
        new (&data_[i]) T();  // default-initialize
}

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
        new_data[i] = move(data_[i]);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    ++realloc_count_;
}

template <typename T>
void ManoVektorius<T>::clear() {
    for (size_t i = 0; i < size_; ++i) {
        data_[i].~T();  // iskviecia destruktoriu
    }
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

template <typename T>
void ManoVektorius<T>::reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        reallocate(new_cap);
    }
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
bool operator==(const ManoVektorius<T>& lhs, const ManoVektorius<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (size_t i = 0; i < lhs.size(); ++i)
        if (lhs[i] != rhs[i]) return false;
    return true;
}

template <typename T>
bool operator!=(const ManoVektorius<T>& lhs, const ManoVektorius<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
T& ManoVektorius<T>::at(size_t index) {
    if (index >= size_) throw out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
const T& ManoVektorius<T>::at(size_t index) const {
    if (index >= size_) throw out_of_range("Index out of range");
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

template <typename T>
void ManoVektorius<T>::resize(size_t new_size) {
    if (new_size > capacity_) {
        reserve(new_size);
    }
    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i)
            data_[i] = T(); 
    }
    size_ = new_size;
}

template <typename T>
void ManoVektorius<T>::shrink_to_fit() {
    if (capacity_ == size_) return;

    T* new_array = static_cast<T*>(::operator new[](size_ * sizeof(T)));

    for (size_t i = 0; i < size_; ++i) {
        new (&new_array[i]) T(move(data_[i]));
        data_[i].~T();
    }

    ::operator delete[](data_);
    data_ = new_array;
    capacity_ = size_;
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

template <typename T>
void ManoVektorius<T>::insert(size_t index, const T& value) {
    if (index > size_) throw out_of_range("Indeksas uz ribu");
    if (size_ == capacity_) reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    for (size_t i = size_; i > index; --i) {
        data_[i] = move(data_[i - 1]);
    }
    data_[index] = value;
    ++size_;
}

template <typename T>
T& ManoVektorius<T>::front() {
    return data_[0];
}

template <typename T>
const T& ManoVektorius<T>::front() const {
    return data_[0];
}

template <typename T>
void ManoVektorius<T>::swap(ManoVektorius<T>& other) {
    swap(data_, other.data_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
    swap(realloc_count_, other.realloc_count_);
}

 #endif