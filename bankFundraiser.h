#ifndef __BANK_FUNDRAISER_H__
#define __BANK_FUNDRAISER_H__

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace ICS45C {
namespace BankFundraiser {

// Struct
template <typename T>
struct RankedNode {
  std::string name;
  T value;
  struct RankedNode* next;
};

// Class
template <typename T>
class FundraiserRank {
 private:
  std::string competition_name;
  bool ascending;
  RankedNode<T>* head;

 public:
  FundraiserRank(std::string name);
  FundraiserRank(std::string name, bool ascending);
  ~FundraiserRank();
  bool isAscending();
  unsigned int add(std::string name, T value);
  bool isEmpty();
  bool exists(T value);
  unsigned int length();
  RankedNode<T>* find(std::string name);
  RankedNode<T>* get(int pos);
  bool remove(std::string name);
  void reverse();
  std::string printTop(unsigned int N);
  RankedNode<T>* operator[](int pos);
  void operator+(int value);
  friend std::ostream& operator<<(std::ostream& os, const FundraiserRank& ll) {
    RankedNode<T>* current_node = ll.head;
    unsigned int i = 1;
    os << "Results for '" << ll.competition_name << "'\n--------------------\n";
    while (current_node) {
      os << i << ": " << current_node->name << " (" << std::fixed
         << std::setprecision(2) << current_node->value << ")\n";
      current_node = current_node->next;
      i++;
    }
    os << "--------------------\n";

    return os;
  };
};

// Class Function Implementation
template <typename T>
FundraiserRank<T>::FundraiserRank(std::string name)
    : FundraiserRank(name, true) {}

template <typename T>
FundraiserRank<T>::FundraiserRank(std::string name, bool ascending)
    : competition_name(name), ascending(ascending), head(nullptr) {}

template <typename T>
FundraiserRank<T>::~FundraiserRank() {
  RankedNode<T>* temp_node;
  while (head) {
    temp_node = head;
    head = head->next;
    delete temp_node;
  }
}

template <typename T>
bool FundraiserRank<T>::isAscending() {
  return ascending;
}

template <typename T>
unsigned int FundraiserRank<T>::add(std::string name, T value) {
  RankedNode<T>* new_node = new RankedNode<T>;
  new_node->name = name;
  new_node->value = value;
  unsigned int i = 0;

  RankedNode<T>* current_node = head;
  RankedNode<T>* previous_node = nullptr;

  if (ascending) {
    while (current_node && current_node->value < value) {
      previous_node = current_node;
      current_node = current_node->next;
      i++;
    }
  } else {
    while (current_node && current_node->value > value) {
      previous_node = current_node;
      current_node = current_node->next;
      i++;
    }
  }

  if (previous_node) {
    new_node->next = current_node;
    previous_node->next = new_node;
  } else {
    new_node->next = current_node;
    head = new_node;
  }

  return i;
}

template <typename T>
bool FundraiserRank<T>::isEmpty() {
  if (head) {
    return false;
  } else {
    return true;
  }
}

template <typename T>
bool FundraiserRank<T>::exists(T value) {
  RankedNode<T>* current_node = head;
  while (current_node) {
    if (current_node->value == value) {
      return true;
    }
    current_node = current_node->next;
  }
  return false;
}

template <typename T>
unsigned int FundraiserRank<T>::length() {
  unsigned int length = 0;
  RankedNode<T>* current_node = head;
  while (current_node) {
    current_node = current_node->next;
    length++;
  }
  return length;
}

template <typename T>
RankedNode<T>* FundraiserRank<T>::find(std::string name) {
  RankedNode<T>* current_node = head;
  while (current_node) {
    if (current_node->name == name) {
      return current_node;
    }
    current_node = current_node->next;
  }
  return nullptr;
}

template <typename T>
RankedNode<T>* FundraiserRank<T>::get(int pos) {
  if (pos < 0) {
    pos = (int)FundraiserRank<T>::length() + pos;
  }

  RankedNode<T>* current_node = head;

  for (int i = 0; i <= pos && current_node; i++) {
    if (i == pos) {
      return current_node;
    }
    current_node = current_node->next;
  }
  return nullptr;
}

template <typename T>
bool FundraiserRank<T>::remove(std::string name) {
  RankedNode<T>* current_node = head;
  RankedNode<T>* previous_node = nullptr;

  while (current_node) {
    if (current_node->name == name) {
      if (previous_node) {
        previous_node->next = current_node->next;
      } else if (head->next) {
        head = head->next;
      } else {
        head = nullptr;
      }
      delete current_node;
      return true;
    }
    previous_node = current_node;
    current_node = current_node->next;
  }
  return false;
}

template <typename T>
void FundraiserRank<T>::reverse() {
  RankedNode<T>*current_node = head, *previous = nullptr, *next = nullptr;

  while (current_node) {
    next = current_node->next;
    current_node->next = previous;
    previous = current_node;
    current_node = next;
  }
  head = previous;

  ascending = !ascending;
}

template <typename T>
std::string FundraiserRank<T>::printTop(unsigned int N) {
  RankedNode<T>* current_node = head;
  std::stringstream stream;
  for (unsigned int i = 0; i < N && current_node; i++) {
    stream << current_node->name << " (" << std::fixed << std::setprecision(2)
           << current_node->value << ") -> ";
    current_node = current_node->next;
  }
  stream << "\n";
  return stream.str();
}

template <typename T>
RankedNode<T>* FundraiserRank<T>::operator[](int pos) {
  return this->get(pos);
}

template <typename T>
void FundraiserRank<T>::operator+(int value) {
  RankedNode<T>* current_node = head;
  while (current_node) {
    current_node->value += value;
    current_node = current_node->next;
  }
}

}  // namespace BankFundraiser
}  // namespace ICS45C

#endif  // __BANK_FUNDRAISER_H__
