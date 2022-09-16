#include <iostream>
#include <cassert>
// TODO: Appropriate CMakeList

namespace DataStructures {
    template<typename T>
    class LinkedList {
    private:
        struct Node {
            Node* next = nullptr;
            T data{};

            Node() = default;

            Node(T data, Node* next) : data(data), next(next) {
            }
        };

        Node head_{};
        std::size_t size_ = 0;



    public:
        LinkedList() = default;

        LinkedList(std::initializer_list<T> list);

        ~LinkedList();

        T& front();
        T& back();

        bool is_empty() const;
        std::size_t size() const;
        std::size_t find(T value) const;

        LinkedList<T> insert(int index, const T& value);
        LinkedList<T> push_front(const T& value);
        LinkedList<T> push_back(const T& value);

        LinkedList<T> remove(const T& value);
        LinkedList<T> remove_at(int index);

        T pop_front();
        T pop_back();
        LinkedList<T> reverse();

        T& operator[](int index);
    };
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(std::initializer_list<T> list) {
    Node* next_node = &head_;

    for (const T& item : list) {
        next_node->next = new Node(item, next_node->next);
        next_node = next_node->next;
        ++size_;
    }
}

template<typename T>
DataStructures::LinkedList<T>::~LinkedList() {}

template<typename T>
bool DataStructures::LinkedList<T>::is_empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t DataStructures::LinkedList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t DataStructures::LinkedList<T>::find(T value) const {
    const Node* node = &head_;
    if (node->next == nullptr) { // || size_ == 0
        return -1;
    }

    int index = 0;
    while (node->next != nullptr) {
        if (node->next->data == value) {
            return index;
        }

        node = node->next;
        ++index;
    }

    return -1;
}

template<typename T>
T& DataStructures::LinkedList<T>::operator[](int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index is out of range.");
    }

    Node* node = &head_;
    int i = 0;

    while (i <= index) {
        node = node->next;
        ++i;
    }

    return node->data;
}

template<typename T>
T& DataStructures::LinkedList<T>::front() {
    return (*this)[0];
}

template<typename T>
T& DataStructures::LinkedList<T>::back() {
    return (*this)[size_ - 1];
}

namespace Tests {
    void RUN();
    void Test_LinkedList();
}

void Tests::Test_LinkedList() {
    {
        DataStructures::LinkedList<int> empty{};
        assert(empty.is_empty());
        assert(empty.size() == 0);
        assert(empty.find(0) == -1);

        DataStructures::LinkedList<int> container{1, 2, 3};
        assert(container.find(1) == 0);
        assert(container.find(3) == 2);
        assert(container.find(0) == -1);

        assert(!container.is_empty());
        assert(container.size() == 3);
    }

    {
        DataStructures::LinkedList<std::string> container{
            "Hello!",
            "Just imagine... It might have been a game dialogue.",
            "Bye..."
        };

        assert(!container.is_empty());
        assert(container.size() == 3);

        assert(container.find("Hello!") == 0);
        assert(container.find("No way!") == -1);

        assert(container[0] == "Hello!");
        assert(container[container.size() - 1] == "Bye...");

        bool hasTrown = false;
        try {
            container[container.size()];
        } catch (std::out_of_range) {
            hasTrown = true;
        }
        assert(hasTrown);

        assert(container.front() == "Hello!");
        container.front() = "Hell";
        assert(container[0] == "Hell");
    }
}

void Tests::RUN() {
    Test_LinkedList();
}

int main() {
    Tests::RUN();
}