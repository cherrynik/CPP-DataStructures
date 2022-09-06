#pragma once

#include <iostream>

template<class T>
class LinkedList {
  private:
    std::size_t size_;

  public:
    LinkedList<T>() = default;
    LinkedList<T>(const std::initializer_list<T>& l) : size_(0) {
      std::cout << "1";
    }

    void push_front(T value);
    void push_back(T value);
    void pop_front(T value);
    void pop_back(T value);
    void insert(size_t index, T value);
    void remove(T value);
    void remove_at(size_t index);
    LinkedList<T> reverse(size_t index);
    std::size_t find(T value) const;
    T front() const;
    T back() const;
    bool is_empty() const;
    std::size_t size() const;
};

