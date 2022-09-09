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

        Node(const T& value, Node* next) : data_(value), next(next) {}
    };

    Node head_;
    // Tail tail_;
    std::size_t size_;

    void cleanup() {
      while (size_ > 0) {
        pop_front();
      }
    }

  public:
    // LinkedList<T>() : size_(0), head_(), tail_() {}
    LinkedList() = default;

    LinkedList(std::initializer_list<T> list) : size_(0), head_() {
      Node** nextNode = &(head_.next); // currentNode = address of head.next

      try {
        for (T item : list) {
          *nextNode = new Node(item, *nextNode); // assign to the address of head.next new Node()
          nextNode = &((*nextNode)->next); // assign to currentNode address of the next Node from itself (= last node)
  
          // &(tail_.next) = 
  
          ++size_;
        }
      } catch (std::bad_alloc) {
        std::cout << "Bad!\n";
        delete *nextNode;
        delete nextNode;

        throw;
      }
    }

    ~LinkedList() {
      cleanup();
    }

    void push_front(const T& value) {
      head_.next = new Node(value, head_.next);

      ++size_;
    }

    void push_back(const T& value) {
      Node** nextNode = &(head_.next); // currentNode = address of head.next

      // std::cout << (*nextNode) << "\n";
      while ((*nextNode)->next != nullptr) {
        nextNode = &(*nextNode)->next;
      }

      // std::cout << "reached";
      *nextNode = new Node(value, *nextNode);

      ++size_;
    }

    void pop_front() {
      Node** next_node = &(head_.next);

      delete head_.next;
      head_.next = *next_node;

      --size_;
    }

    void pop_back(T value) {}

    void insert(size_t index, T value) {}

    void remove(T value) {}

    void remove_at(size_t index) {}

    LinkedList<T> reverse(size_t index) {}

    // Returns index if found, else -1
    const int find(T value) {
      Node *nextNode = head_.next;
      int index = 0;

      while (nextNode->next != NULL) {
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
  /*
  int a = 1;

  int* b = &a;
  int* c = b;

  int** d = &b;
  int** e = d;

  std::cout << b << " " << c << " " << d << " " << e;*/

  LinkedList<std::string> a{"a"};
  a.push_back("dfkajs;");

  // assert(a.size() == 2);
  // a.push_front("hey!");

  // std::cout << std::to_string(a.size()) << "\n";

  // std::cout << (*&a.front());

  /*
  a.push_back("c");

  std::cout << a.find("hey") << "\n";
  std::cout << "first elem: " << a.front() << "\n";
  std::cout << "last elem: " << a.back() << "\n";
  std::cout << "size: " << a.size() << "\n";
  */
}