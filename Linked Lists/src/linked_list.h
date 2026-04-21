// Editor to handle user commands and interact with LinkedList

#ifndef ASSIGNMENT1_LINKED_LIST_H
#define ASSIGNMENT1_LINKED_LIST_H

#include <iostream>
#include <string>

class LinkedList {
  struct Node {
    std::string data;
    Node* next {nullptr};
    explicit Node(const std::string& s) : data(s) {}
  };
  Node* _start {nullptr};
  int _current_line {1};

public:
  ~LinkedList();
  void add(const std::string& s);

  // File operations
  void load_from_file(const std::string& filename);
  void save_to_file(const std::string& filename);
  //
  void display_with_line_numbers() const;
  void display_line(int line_num);
  void display_range(int start, int end);
  // Editing operations
  void delete_line(int line_num);
  void delete_range(int start, int end);
  void insert_at_line(const std::string& text, int line_num);

  int get_current_line() const { return _current_line; }
  void set_current_line(int line) { _current_line = line; }
  int size() const;

  friend std::ostream& operator<<(std::ostream& os, const LinkedList& list);
};

#endif // ASSIGNMENT1_LINKED_LIST_H
