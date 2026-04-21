// Stack class definition for a linked list based stack implementation

#ifndef ASSIGNMENT_2_STACK_H
#define ASSIGNMENT_2_STACK_H

#include <memory>
#include <optional>
#include <ostream>

// Stack class template definition
template <typename T>

// Linked List based stack implementation
class Stack {
  struct Node {
    T data;
    std::unique_ptr<Node> next {nullptr};
  };

  std::unique_ptr<Node> _top {nullptr};

public:
  // Pushes an element onto the stack
  void push(const T& value) {
    auto new_node = std::make_unique<Node>(value);
    new_node->next = std::move(_top);
    _top = std::move(new_node);
  }

  // Returns the top element (or nullopt if empty)
  [[nodiscard]] std::optional<T> top() const {
    if (_top == nullptr) return std::nullopt;
    return std::make_optional(_top->data);
  }

  // Removes the top element from the stack
  void pop() {
    _top = std::move(_top->next);
  }

  // Checks if the stack is empty
  [[nodiscard]] bool empty() const {
    return _top == nullptr;
  }

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Stack<U>& s);
};

// Prints all elements in the stack (top to bottom)
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
  auto current_node = s._top.get();
  while (current_node != nullptr) {
    os << current_node->data << std::endl;
    current_node = current_node->next.get();
  }
  return os;
}

#endif // ASSIGNMENT_2_STACK_H