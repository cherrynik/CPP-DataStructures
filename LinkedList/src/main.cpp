#include <iostream>
#include <iterator>
#include <cassert>

template<class T>
class LinkedList {
    struct Node {
    public:
        T data_{};
        Node* next = nullptr;

        Node() = default;

        Node(T value, Node* next) : data_(value), next(next) {}
    };

    Node head_{};
    // Tail tail_;
    std::size_t size_ = 0;

    void cleanup() {
        /*
        while (size_ > 0) {
            pop_front();
        }
        */
    }

    Node** find_at(int index) {
        if (index < -1 || index > static_cast<int>(size_)) {
            throw std::out_of_range("Index is out of range.");
        }

        Node** node_addr = &(head_.next);
        for (int i = 0; i <= index; ++i) {
            node_addr = &((*node_addr)->next);
        }

        return node_addr;
    }

public:
    LinkedList() = default;

    /*
    LinkedList(std::initializer_list<T> list) : size_(0), head_() {
      Node** next_node = &(head_.next);

      try {
        for (const T& item : list) {
          *next_node = new Node(item, *next_node); // can throw bad_alloc
          next_node = &((*next_node)->next);
          ++size_;
        }
      } catch (std::bad_alloc) {
        cleanup();

        throw;
      }
    }
    */

    ~LinkedList() {
        cleanup();
    }

    void insert(T data, int index) {
        Node** elem_before = find_at(index - 1);

        *elem_before = new Node(data, *elem_before);

        ++size_;
    }

    void push_front(T value) {
        insert(value, 0);
    }

    void push_back(const T& value) {
        insert(value, size_);
    }

    T pop_front() {}

    T pop_back(T value) {}

    void remove(T value) {}

    void remove_at(size_t index) {}

    LinkedList<T> reverse(size_t index) {}

    // Returns index if found, else -1
    int find(const T& value) const noexcept {

    }

    // TODO: as iterators and getters
    T front() const noexcept {

    }

    T back() const noexcept {

    }

    std::size_t size() const noexcept {
        return size_;
    }

    bool is_empty() const noexcept {
        return size() == 0;
    }
};

int* test() {
    int* a = new int();
    *a = 200;
    return a;
}

int main() {
    LinkedList<std::string> a{};
    a.push_front("Hello!");
    a.push_back("Bye!");
}