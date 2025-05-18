#include "vector.h"

template <typename T>
ManoVektorius<T>::ManoVektorius() : data(nullptr), size(0), capacity(0) {}

template <typename T>
ManoVektorius<T>::~Vector() {
    delete[] data;
}
//-----------------------------------------------------------------
template <typename T>
void ManoVektorius<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}
//-----------------------------------------------------------------
template <typename T>
void ManoVektorius<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}
//-----------------------------------------------------------------
template <typename T>
void ManoVektorius<T>::reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i)
        new_data[i] = move(data_[i]);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}
//-----------------------------------------------------------------
template <typename T>
T& ManoVektorius<T>::operator[](size_t index) {
    return data_[index];
}
//-----------------------------------------------------------------
template <typename T>
T& ManoVektorius<T>::at(size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}
//-----------------------------------------------------------------
template <typename T>
size_t ManoVektorius<T>::size() const noexcept {
    return size_;
}
//-----------------------------------------------------------------
template <typename T>
size_t ManoVektorius<T>::capacity() const noexcept {
    return capacity_;
}
//-----------------------------------------------------------------
template <typename T>
bool ManoVektorius<T>::empty() const noexcept {
    return size_ == 0;
}
//-----------------------------------------------------------------
template <typename T>
void ManoVektorius<T>::clear() {
    size_ = 0;
}
//-----------------------------------------------------------------
template <typename T>
void ManoVektorius<T>::erase(size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");

    for (std::size_t i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
}
