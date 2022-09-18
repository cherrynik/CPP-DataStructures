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

        void cleanup() noexcept;

    public:
        LinkedList() = default;

        LinkedList(std::initializer_list<T> list);

        ~LinkedList() noexcept;

        T& front() noexcept;
        T& back() noexcept;

        bool is_empty() const noexcept;
        std::size_t size() const noexcept;
        std::size_t find(T value) const noexcept;

        void insert(int index, const T& value);
        void push_front(const T& value);
        void push_back(const T& value);

        T remove_at(int index) noexcept;

        T pop_front() noexcept;
        T pop_back() noexcept;
        void reverse() noexcept;

        T& operator[](int index);
    };
}

template<typename T>
typename DataStructures::LinkedList<T>::Node* DataStructures::LinkedList<T>::before(int index) {
    return (index) == 0
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
void DataStructures::LinkedList<T>::cleanup() noexcept {
    while (size_ > 0) {
        pop_front();
    }
}

template<typename T>
DataStructures::LinkedList<T>::~LinkedList() noexcept {
    cleanup();
}

template<typename T>
void DataStructures::LinkedList<T>::insert(int index, const T& value) {
    Node* prev = before(index);
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
T DataStructures::LinkedList<T>::remove_at(int index) noexcept {
    Node* prev = before(index);
    Node* curr = prev->next;
    T removed = curr->data;

    prev->next = curr->next; // Required: doing it before deletion.
    delete curr;

    --size_;

    return removed;
}

template<typename T>
T DataStructures::LinkedList<T>::pop_front() noexcept {
    return remove_at(0);
}

template<typename T>
T DataStructures::LinkedList<T>::pop_back() noexcept {
    return remove_at(size_ - 1);
}

template<typename T>
bool DataStructures::LinkedList<T>::is_empty() const noexcept {
    return size_ == 0;
}

template<typename T>
std::size_t DataStructures::LinkedList<T>::size() const noexcept {
    return size_;
}

template<typename T>
std::size_t DataStructures::LinkedList<T>::find(T value) const noexcept {
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
T& DataStructures::LinkedList<T>::front() noexcept {
    return (*this)[0];
}

template<typename T>
T& DataStructures::LinkedList<T>::back() noexcept {
    return (*this)[size_ - 1];
}

template<typename T>
void DataStructures::LinkedList<T>::reverse() noexcept {
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

        bool hasThrown = false;
        try {
            container[container.size()];
        } catch (const std::out_of_range&) {
            hasThrown = true;
        }
        assert(hasThrown);

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
        DataStructures::LinkedList<int> ints{};
        ints.reverse();
    }

    {
        DataStructures::LinkedList<int> ints{0};
        assert(ints.front() == 0);

        ints.reverse();
        assert(ints.back() == 0);
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