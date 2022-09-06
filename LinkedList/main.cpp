#include <iostream>

template<typename T>
class LinkedList {
  private:
  public:
    LinkedList<T>() = default;

    LinkedList<T>(const std::initializer_list<T>& list) {
      for (const T& d : list) {
        std::cout << d << "\n";
      }
    };
};

int main() {
  std::cout << "Hey!\n";
  LinkedList<int> a{1, 2};
  std::cout << "Bye!";
}