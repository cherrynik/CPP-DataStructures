#include <iostream>

namespace DataStructures {
    template<typename T>
    class LinkedList {
    private:
        struct Node {
            Node* next = nullptr;
            T data{};

            Node() = default;
            Node(T data, Node& next) : data(data), next(next) {}
        };

        Node head_{};
        std::size_t size_ = 0;

    public:
        LinkedList() = default;
        LinkedList(std::initializer_list<T> l);

        ~LinkedList();

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
}

template<typename T>
DataStructures::LinkedList<T>::LinkedList(std::initializer_list<T> list) {
    std::cout << "It's happening..." << std::endl;
}

namespace Tests {
    void RUN();
    void Test_LinkedList_Constructing();
}

void Tests::Test_LinkedList_Constructing() {
    {
        DataStructures::LinkedList<std::string> empty;
        DataStructures::LinkedList<std::string>{};
        DataStructures::LinkedList<std::string>{"Hello!", "Bye!"};
    }

    {
        DataStructures::LinkedList<int> empty;
        DataStructures::LinkedList<int>{};
        DataStructures::LinkedList<int>{1, 2};
    }
}

void Tests::RUN() {
    Test_LinkedList_Constructing();
}

int main() {
    Tests::RUN();
}