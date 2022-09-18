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

        Node* at(int index);

        Node* before(int index);

        void cleanup();

    public:
        LinkedList() = default;

        LinkedList(std::initializer_list<T> list);

        ~LinkedList();

        T& front();
        T& back();

        bool is_empty() const;
        std::size_t size() const;
        std::size_t find(T value) const;

        void insert(int index, const T& value);
        void push_front(const T& value);
        void push_back(const T& value);

        T remove_at(int index);

        T pop_front();
        T pop_back();
        void reverse();

        T& operator[](int index);
    };
}

template<typename T>
typename DataStructures::LinkedList<T>::Node* DataStructures::LinkedList<T>::before(int index) {
    return (index - 1) < 0
        ? &head_
        : at(index - 1);
}

template<typename T>
typename DataStructures::LinkedList<T>::Node* DataStructures::LinkedList<T>::at(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index is out of range.");
    }

    int i = 0;
    Node* node = &head_;
    while (i <= index) {
        node = node->next;
        ++i;
    }

    return node;
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(std::initializer_list<T> list) {
    Node* node = &head_;
    try {
        for (const T& item : list) {
            node->next = new Node(item, node->next); // Can be thrown

            node = node->next;
            ++size_;
        }
    } catch (const std::bad_alloc&) {
        cleanup();
        throw;
    }
}

template<typename T>
void DataStructures::LinkedList<T>::cleanup() {
    while (size_ > 0) {
        pop_front();
    }
}

template<typename T>
DataStructures::LinkedList<T>::~LinkedList() {
    cleanup();
}

template<typename T>
void DataStructures::LinkedList<T>::insert(int index, const T& value) {
    Node* prev;
    if (index == 0) {
        prev = &head_;
    } else {
        prev = at(index - 1);
    }

    prev->next = new Node(value, prev->next);
    ++size_;
}

template<typename T>
void DataStructures::LinkedList<T>::push_front(const T& value) {
    insert(0, value);
}

template<typename T>
void DataStructures::LinkedList<T>::push_back(const T& value) {
    insert(size_, value);
}

template<typename T>
T DataStructures::LinkedList<T>::remove_at(int index) {
    Node* prev = before(index);
    Node* curr = prev->next;
    T removed = curr->data;

    prev->next = curr->next; // Required: doing it before deletion.

    delete curr;

    --size_;

    return removed;
}

template<typename T>
T DataStructures::LinkedList<T>::pop_front() {
    return remove_at(0);
}

template<typename T>
T DataStructures::LinkedList<T>::pop_back() {
    return remove_at(size_ - 1);
}

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

    int i = 0;
    while (node->next != nullptr) {
        if (node->next->data == value) {
            return i;
        }

        node = node->next;
        ++i;
    }

    return -1;
}

template<typename T>
T& DataStructures::LinkedList<T>::operator[](int index) {
    return at(index)->data;
}

template<typename T>
T& DataStructures::LinkedList<T>::front() {
    return (*this)[0];
}

template<typename T>
T& DataStructures::LinkedList<T>::back() {
    return (*this)[size_ - 1];
}

template<typename T>
void DataStructures::LinkedList<T>::reverse() {
    Node* prev = nullptr;
    Node* curr = head_.next;

    Node copy;
    while (curr != nullptr) {
        copy = *curr;
        curr->next = prev;
        prev = curr;
        curr = copy.next;
    }
    head_.next = prev;
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

        assert(container.remove_at(2) == "Bye...");
    }

    {
        DataStructures::LinkedList<char> chars;
        chars.push_front('a');
        chars.push_back('z');

        chars.insert(1, 'n');
        assert(chars.size() == 3);
        assert(chars.front() == 'a');
        assert(chars[1] == 'n');
        assert(chars.back() == 'z');

        assert(chars.pop_front() == 'a');
        assert(chars.size() == 2);
        assert(chars.pop_back() == 'z');
        assert(chars.size() == 1);
        assert(chars.pop_back() == 'n');
        assert(chars.is_empty());
    }

    {
        DataStructures::LinkedList<int> ints{0, 1, 2, 3, 4, 5};
        assert(ints.front() == 0);
        assert(ints.back() == 5);

        ints.reverse();
        assert(ints.front() == 5);
        assert(ints.back() == 0);
    }
}

void Tests::RUN() {
    Test_LinkedList();
}

int main() {
    Tests::RUN();
}