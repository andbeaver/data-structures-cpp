
#include "linked_list.h"

#include <fstream>
#include <iostream>

// Destructor to clean up nodes
LinkedList::~LinkedList() {
    auto cur = _start;
    while (cur) {
        auto nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}

// Overload << operator to print the linked list
std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
    auto curr = list._start;
    while (curr != nullptr) {
        os << curr->data << std::endl;
        curr = curr->next;
    }
    return os;
}

// Add a new string to the end of the linked list
void LinkedList::add(const std::string& s) {
    auto node = new Node {s};

    // First node in the list?
    if (_start == nullptr) {
        // Yes! it is the first node
        _start = node;
    } else {
        // No! Find end of list
        auto curr = _start;
        auto prev = (Node*)nullptr;

        // traverse the chain
        while (curr != nullptr) {
            prev = curr;
            // move to the next node
            curr = curr->next;
        }

        if (prev != nullptr) {
            // We have found the end of the chain
            // Lets add the new node to the end of the chain
            prev->next = node;
        }
    }
}

// Load file contents into list
void LinkedList::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    // Read file line by line
    std::string line;
    while (std::getline(file, line)) {
        add(line);
    }

    file.close();
}

// Save list contents to file
void LinkedList::save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }
    // Write each line to file
    auto curr = _start;
    while (curr != nullptr) {
        file << curr->data << std::endl;
        curr = curr->next;
    }

    file.close();
}
// Display all lines with line numbers
void LinkedList::display_with_line_numbers() const {
    auto curr = _start;
    int line_num = 1;

    while (curr != nullptr) {
        std::cout << line_num << ": " << curr->data << std::endl;
        curr = curr->next;
        line_num++;
    }
}

// Display single line at specified number
void LinkedList::display_line(int line_num) {
    if (line_num < 1 || line_num > size()) {
        std::cout << "Invalid line number" << std::endl;
        return;
    }
    // Traverse to specified line
    auto curr = _start;
    int current = 1;

    while (curr != nullptr && current < line_num) {
        curr = curr->next;
        current++;
    }

    if (curr != nullptr) {
        std::cout << line_num << ": " << curr->data << std::endl;
    }
}

// Display range of lines from start to end
void LinkedList::display_range(int start, int end) {
    if (start < 1 || end < start || end > size()) {
        std::cout << "Invalid range" << std::endl;
        return;
    }
    // Traverse to specified line
    auto curr = _start;
    int current = 1;

    // Move to start line
    while (curr != nullptr && current < start) {
        curr = curr->next;
        current++;
    }

    // Print from start to end
    while (curr != nullptr && current <= end) {
        std::cout << current << ": " << curr->data << std::endl;
        curr = curr->next;
        current++;
    }
}

// Delete single line from lis
void LinkedList::delete_line(int line_num) {
    if (line_num < 1 || line_num > size()) {
        std::cout << "Invalid line number" << std::endl;
        return;
    }

    auto curr = _start;
    auto prev = (Node*)nullptr;
    int current = 1;

    // Find the node to delete
    while (curr != nullptr && current < line_num) {
        prev = curr;
        curr = curr->next;
        current++;
    }

    if (curr != nullptr) {
        // Deleting first node
        if (prev == nullptr) {
            _start = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
}

// Delete range of lines
void LinkedList::delete_range(int start, int end) {
    if (start < 1 || end < start || end > size()) {
        std::cout << "Invalid range" << std::endl;
        return;
    }

    // Delete backwards to avoid line number shifting
    for (int i = end; i >= start; i--) {
        delete_line(i);
    }
}

// Insert text at specified line number
void LinkedList::insert_at_line(const std::string& text, int line_num) {
    if (line_num < 1 || line_num > size() + 1) {
        std::cout << "Invalid line number" << std::endl;
        return;
    }

    auto node = new Node{text};

    // Insert at the beginning
    if (line_num == 1) {
        node->next = _start;
        _start = node;
        return;
    }

    // Find the node before insertion point
    auto curr = _start;
    int current = 1;

    while (curr != nullptr && current < line_num - 1) {
        curr = curr->next;
        current++;
    }
    // Insert node
    if (curr != nullptr) {
        node->next = curr->next;
        curr->next = node;
    }
}

// Count total lines in list
int LinkedList::size() const {
    int count = 0;
    auto curr = _start;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

