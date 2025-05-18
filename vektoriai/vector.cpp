#include "vector.h"

template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}
//-----------------------------------------------------------------
template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}
//-----------------------------------------------------------------
template <typename T>
void pop_back(const T& value){
    
}
//-----------------------------------------------------------------
template <typename T>
void Vector<T>::reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i)
        new_data[i] = std::move(data_[i]);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}
//-----------------------------------------------------------------
template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}
//-----------------------------------------------------------------
template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) throw std::out_of_range("Index out of range");
    return data_[index];
}
//-----------------------------------------------------------------
template <typename T>
size_t Vector<T>::size() const noexcept {
    return size_;
}
//-----------------------------------------------------------------
template <typename T>
size_t Vector<T>::capacity() const noexcept {
    return capacity_;
}
//-----------------------------------------------------------------
template <typename T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}
