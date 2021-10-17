#include "Array.h"

Array::Array(int input_size) : size_(0), min_size_(16) {
  if (input_size < 1) {
    throw std::invalid_argument("Size of array cannot be less than 1.");
  }
                                                                       
  capacity_     = Array::CalculateSpaceAmortized(input_size);
  allocated_at_ = (value_type_*) malloc(capacity_);
}

Array::~Array() {
  free(allocated_at_);
}

inline size_t Array::CalculateSpaceAmortized(int size) const {
  return (size < min_size_) ?
    min_size_ :
    std::pow(2, ceil(log2(size)));
}

size_t Array::capacity() const {
  return capacity_;
}


size_t Array::size() const {
  return size_;
}

bool Array::is_empty() const {
  return size_ == 0;
}
