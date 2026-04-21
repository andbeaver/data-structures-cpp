
#include "editor.h"
#include <iostream>
#include <sstream>

// Main loop to run the editor
void Editor::run(const std::string& filename) {
  edit_file(filename);
}

// Initialize editor and start command loop
void Editor::edit_file(const std::string& filename) {
  _filename = filename;
  _list.load_from_file(filename);
  _modified = false;

  // Main command loop
  std::string input;
  while (true) {
    // display prompt and process input
    std::cout << _list.get_current_line() << "> ";
    std::getline(std::cin, input);
    parse_command(input);
  }
}

// Route input to appropriate command handler or treat as text
void Editor::parse_command(const std::string& input) {
  if (input.empty()) return;

  char cmd = std::toupper(input[0]);

  // Check if input is a command (I, D, L, E followed by space or end)
  bool isCommand = (input.length() == 1 || input[1] == ' ') &&
                   (cmd == 'I' || cmd == 'D' || cmd == 'L' || cmd == 'E');

  if (isCommand) {
    // Get command arguments
    std::string args = input.length() > 2 ? input.substr(2) : "";

    switch (cmd) {
    case 'I': handle_insert(args); break;
    case 'D': handle_delete(args); break;
    case 'L': handle_list(args); break;
    case 'E': handle_exit(); break;
    default: break;
    }
  } else {
    // Not a command - treat as text to insert
    int line = _list.get_current_line();
    _list.insert_at_line(input, line);
    _list.set_current_line(line + 1);
    _modified = true;
  }
}

// Insert text at specified line or current line
void Editor::handle_insert(const std::string& args) {
  std::istringstream iss(args);
  int line_num;

  // Use specified line number or default to current line
  if (!(iss >> line_num)) {
    line_num = _list.get_current_line();
  } else {
    // Parameter provided: insert before that line
    _list.set_current_line(line_num);
  }

  // Read multiple lines until empty line entered
  std::string text;
  bool last_was_empty = false;
  while (true) {
    std::cout << line_num << "> ";
    std::getline(std::cin, text);

    // Two consecutive empty lines exits insert mode
    if (text.empty()) {
      if (last_was_empty) {
        break;
      }
      last_was_empty = true;
    } else {
      last_was_empty = false;
    }

    _list.insert_at_line(text, line_num);
    line_num++;
    _modified = true;
  }

  _list.set_current_line(line_num);
}

// Delete lines based on parameters
void Editor::handle_delete(const std::string& args) {
  std::istringstream iss(args);
  int start, end;

  // If no parameters then delete current line
  if (!(iss >> start)) {
    int cur = _list.get_current_line();
    if (cur > 1) {
      _list.delete_line(cur - 1);
      // current line stays the same after deleting previous line
      _list.set_current_line(cur - 1);
    } else {
      std::cout << "Cannot delete before line 1\n";
    }
    _modified = true;
    return;
  }

  // One parameter: delete that line
  if (!(iss >> end)) {
    _list.delete_line(start);
    // Adjust current line if we deleted beyond the end
    if (_list.get_current_line() > _list.size()) {
      _list.set_current_line(_list.size() + 1);
    }
    _modified = true;
    return;
  }

  // Two parameters: delete range
  _list.delete_range(start, end);
  _modified = true;
}

// Display lines based on parameters
void Editor::handle_list(const std::string& args) {
    std::istringstream iss(args);
    int start, end;

    // No parameters: list all lines
    if (!(iss >> start)) {
        _list.display_with_line_numbers();
        return;
    }

    // One parameter: list that line
    if (!(iss >> end)) {
        _list.display_line(start);
        _list.set_current_line(start + 1);
        return;
    }

    // Two parameters: list range
    _list.display_range(start, end);
    _list.set_current_line(end + 1);
}

// Save file and exit program
void Editor::handle_exit() {
  _list.save_to_file(_filename);
  std::cout << "File saved. Exiting...\n";
  exit(0);
}