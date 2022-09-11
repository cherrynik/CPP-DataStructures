#include <iostream>
#include <chrono>
#include <iterator>
#include <cassert>
#include <forward_list>

template<class T>
class LinkedList {
    struct Node {
    public:
        T data{};
        Node* next = nullptr;

        Node() = default;

        Node(T value, Node* next) : data(value), next(next) {}
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
    template<class ValueType>
    class ForwardIterator {
    private:
        Node* node_ = nullptr;
        friend class LinkedList;

        explicit ForwardIterator(Node* node) : node_(node) {};
    public:
        // using iterator_category = std::forward_iterator_tag;
        // using value_type = ValueType;
        // using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        ForwardIterator() = default;

        ForwardIterator(const ForwardIterator<T>& source) noexcept : node_(source.node_) {}

        ForwardIterator& operator=(const ForwardIterator& rhs) = default;

        bool operator==(const ForwardIterator<const T>& rhs) {
            return this->node_ == rhs.node_;
        };

        bool operator==(const ForwardIterator<T>& rhs) {
            return this->node_ == rhs.node_;
        };

        bool operator!=(const ForwardIterator<const T>& rhs) {
            return !(*this == rhs);
        };

        bool operator!=(const ForwardIterator<T>& rhs) {
            return !(*this == rhs);
        };

        ForwardIterator& operator++() {
            assert(node_ != nullptr);
            node_ = node_->next;
            return *this;
        }

        ForwardIterator operator++(int) noexcept {
            ForwardIterator old_value(*this);
            ++(*this);
            return old_value;
        }

        reference operator*() const noexcept {
            assert(node_ != nullptr);
            return node_->data;
        }

        pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return node_->data;
        }
    };

    using Iterator = ForwardIterator<T>;
    using ConstIterator = ForwardIterator<const T>;

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

    Iterator begin() const noexcept {
        return Iterator{head_.next};
    }

    Iterator end() const noexcept {
        return Iterator{};
    }

    ConstIterator cbegin() const noexcept {
        return ConstIterator{head_.next};
    }

    ConstIterator cend() const noexcept {
        return ConstIterator{};
    }

    void insert(const T& data, int index) {
        Node** elem_before = find_at(index - 1);

        *elem_before = new Node(data, *elem_before);

        ++size_;
    }

    void push_front(const T& value) {
        insert(value, 0);
    }

    void push_back(const T& value) {
        insert(value, size_);
    }

    T pop_front() {}

    T pop_back(T value) {}

    void remove(T value) {}

    void remove_at(int index) {}

    LinkedList reverse(size_t index) {}

    // Returns index if found, else -1
    int find(const T& value) const noexcept {

    }

    Node& front() const noexcept {
        return *(head_.next);
    }

    T& back() const noexcept {

    }

    std::size_t size() const noexcept {
        return size_;
    }

    bool is_empty() const noexcept {
        return size() == 0;
    }
};

struct test {
    int some_data = 10;
};

int main() {
    LinkedList<std::string> a{};
    a.push_front("Hey");
    a.push_front("Hey2");
    a.push_front("Hey5");
    a.push_back("bye...");

    for (const std::string& item : a) {
        std::cout << item << std::endl;
    }
    /*
    while (it != a.end()) {
        std::cout << *it << std::endl;
        ++it;
    }
     */
}