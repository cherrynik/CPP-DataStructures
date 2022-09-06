#include <iostream>

template<class T> 
class Node {
  private:
    Node<T> *next_;
    T data_;
  public:
    Node() : next_(nullptr), data_() {
      std::cout << "its address: " << this << " " << data_ << "\n";
    };

    Node(const T& value) : next_(nullptr), data_(value) {
    };
};

template<class T>
class LinkedList {
  private:
    Node<T> head_;
    std::size_t size_;

  public:
    LinkedList<T>() : size_(0) {}

    LinkedList<T>(const std::initializer_list<T>& l) : size_(0), head_() {
      std::cout << "header address: " << &head_ << "\n";
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

int main() {
  LinkedList<std::string> a{"a", "b"};
}