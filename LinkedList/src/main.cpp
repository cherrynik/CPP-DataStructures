#include <iostream>

template<class T>
class LinkedList {
  private:

    struct Head;
    struct Node;

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
    std::size_t size_;

  public:
    LinkedList<T>() : size_(0), head_() {}

    LinkedList<T>(const std::initializer_list<T>& list) : size_(0), head_() {
      Node **currentNode = &(head_.next); // currentNode = address of head.next

      for (const T& item : list) {
        *currentNode = new Node(item); // assign to the address of head.next new Node()
        currentNode = &(*currentNode)->next; // assign to currentNode address of the next Node from itself (= last node)
      }
/*
      std::cout << "header: " << &*(head_.next_) << ", first: " << &**currentNode << "\n";

      std::cout << "header: " << &*(head_.next_) << ", second: " << &*currentNode;*/

      // *currentNode = new Node();

/*
      for (const T& item : list) {
        *currentNode = new Node(item);
        // (*currentNode).set_next(currentNode);
        // currentNode = (*currentNode).next();
        currentNode.next_ = &*currentNode;

        ++size_;
      }*/


/*
      auto node = head_.next_;
      while (node != NULL) {
        std::cout << node->data() << "\n";
        node = node->next_;
      }*/


      // temp = "132";
      // std::cout << (*a).data() << "\n";

/*
      std::cout << "header address: " << &head_ << "\n";
      std::cout << "pointer to by address: " << &a << "\n";
      std::cout << "node address: " << &*a << "\n";
      head_.set_next(a);
*/
    }

    void push_front(T value) {
      /*
      Node temp = new Node(value);
      head_.set_next(&temp);
      ++size_;
      */
    }

    void push_back(T value);
    void pop_front(T value);
    void pop_back(T value);
    void insert(size_t index, T value);
    void remove(T value);
    void remove_at(size_t index);
    LinkedList<T> reverse(size_t index);
    std::size_t find(T value) const;

    T front() const {
      return (*(head_.next)).data();
    };

    T back() const;
    bool is_empty() const;
    std::size_t size() const;
};

int main() {
  LinkedList<std::string> a{"a", "b"};
  // a.push_front("hey!");
  // std::cout << (*&a.front());
  std::cout << a.front();
}