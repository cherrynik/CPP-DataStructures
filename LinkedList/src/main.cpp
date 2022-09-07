#include <iostream>

template<class T>
class LinkedList {
  private:

    struct Head;
    struct Node;
    using Tail = Head;

    struct Head {
      public:
        Node* next;

        Head() : next(nullptr) {}

        Head(Node &node) : next(&node) {}
    };


    struct Node : public Head {
      private:
        T data_;

      public:
        Node() : Head(), data_() {
          std::cout << "its address: " << this << " " << data_ << "\n";
        };
    
        Node(const T &value) : Head(), data_(value) {
          std::cout << "its address: " << this << " " << data_ << "\n";
        };
  
        Node(const T &value, const Node &next) : Head(&next), data_(value) {
          std::cout << "its address: " << this << " " << data_ << "\n";
        }

        T data() {
          return data_;
        }
    };

    Head head_;
    Tail tail_;
    std::size_t size_;

  public:
    LinkedList<T>() : size_(0), head_(), tail_() {}

    LinkedList<T>(const std::initializer_list<T>& list) : size_(0), head_(), tail_() {
      Node **nextNode = &(head_.next); // currentNode = address of head.next

      for (const T& item : list) {
        *nextNode = new Node(item); // assign to the address of head.next new Node()
        nextNode = &(*nextNode)->next; // assign to currentNode address of the next Node from itself (= last node)

        // &(tail_.next) = 

        ++size_;
      }
    }

    void push_back(T value) {
      Node **nextNode = &(head_.next);

      while (&(*nextNode)->next != NULL) {
        nextNode = &(*nextNode)->next;
      }

      *nextNode = new Node(value);

      ++size_;
    }

    void pop_front(T value) {}

    void pop_back(T value) {}

    void insert(size_t index, T value) {}

    void remove(T value) {}

    void remove_at(size_t index) {}

    LinkedList<T> reverse(size_t index) {}

    // Returns index if found, else -1
    const int find(T value) {
      Node **nextNode = &(head_.next);
      int index = 0;

      while (&(*nextNode)->next != NULL) {
        if ((*nextNode)->data() == value) {
          return index;
        }

        nextNode = &(*nextNode)->next;
        ++index;
      }

      return -1;
    }

    const T front() const {
      return (*(head_.next)).data();
    }

    T back() {
      Node **nextNode = &(head_.next);

      while (&(*nextNode)->next != NULL) {
        nextNode = &(*nextNode)->next;
        std::cout << (*nextNode)->data() << " ";
      }

      std::cout << (*nextNode)->data() << "\n";

      return (*nextNode)->data();
    }

    bool is_empty() const {
      return size_ == 0;
    }

    std::size_t size() const {
      return size_;
    }
};

int main() {
  LinkedList<std::string> a{"a", "b"};
  // a.push_front("hey!");
  // std::cout << (*&a.front());

  a.push_back("c");

  std::cout << a.find("hey") << "\n";
  std::cout << "first elem: " << a.front() << "\n";
  std::cout << "last elem: " << a.back() << "\n";
  std::cout << "size: " << a.size() << "\n";
}