//
// Created by andre on 2026-01-24.
//

#ifndef ASSIGNMENT1_EDITOR_H
#define ASSIGNMENT1_EDITOR_H

#include "linked_list.h"
#include <string>

class Editor {
  LinkedList _list;
  std::string _filename;
  bool _modified {false};

public:
  // Main loop to run the editor
  void run(const std::string& filename);
  // Edit a file
  void edit_file(const std::string& filename);

private:
  // Command handlers
  void handle_insert(const std::string& args);
  void handle_delete(const std::string& args);
  void handle_list(const std::string& args);
  void handle_exit();

  // Parse and execute a command
  void parse_command(const std::string& input);
};

#endif // ASSIGNMENT1_EDITOR_H
