#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> l) {
    std::cout << "Template constructor" << std::endl;
}