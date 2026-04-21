#ifndef ASSIGNMENT_3_BST_H
#define ASSIGNMENT_3_BST_H

#include <string>
#include <vector>
#include <ostream>
#include <iomanip>

// Binary Search Tree for strings
class BST {
    struct Node {
        std::string data;
        Node* left{nullptr};
        Node* right{nullptr};
        explicit Node(std::string val) : data(std::move(val)) {}
    };

    Node* _root{nullptr};

public:
    BST() = default;
    ~BST() { clear(_root); }

    // Prevent accidental double-delete from copy operations
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    // Insert a value into the tree
    void insert(const std::string& data) {
        insert(data, _root);
    }

    // Recursive search for a value in the tree
    [[nodiscard]] bool contains(const std::string& data) const {
        return contains(data, _root);
    }

    // Remove a value from the tree
    void remove(const std::string& data) {
        remove_node(data, _root);
    }

    // Clear the tree and reset root
    void clear() {
        clear(_root);
        _root = nullptr;
    }

    // Balance the tree using inorder traversal -> sorted vector -> rebuild
    void balance() {
        std::vector<std::string> sorted_words;
        to_vector(_root, sorted_words);
        clear(_root);
        _root = nullptr;
        build_balanced(sorted_words, 0, (int)sorted_words.size() - 1);
    }

    // Print the tree (sideways) using operator<<
    friend std::ostream& operator<<(std::ostream& os, const BST& bst) {
        bst.print_tree(os, bst._root, 0);
        return os;
    }

private:
    void insert(const std::string& data, Node*& node) {
        if (node == nullptr) {
            node = new Node(data);
        } else if (data < node->data) {
            //search left
            insert(data, node->left);
        } else if (data > node->data) {
            //search right
            insert(data, node->right);
        }
    }

    // Recursive search for a value in the tree
    bool contains(const std::string& data, Node* node) const {
        if (node == nullptr) return false;
        if (data < node->data) return contains(data, node->left);
        if (data > node->data) return contains(data, node->right);
        return true; // found
    }

    // Recursive remove using Node*& so we can adjust parent's pointer
    void remove_node(const std::string& data, Node*& node) {
        if (node == nullptr) return;
        if (data < node->data) {
            remove_node(data, node->left);
        } else if (data > node->data) {
            remove_node(data, node->right);
        } else {
            // found node
            if (node->left != nullptr && node->right != nullptr) {
                // two children: replace with predecessor (max in left subtree)
                Node* parent = node;
                Node* pred = node->left;
                while (pred->right != nullptr) {
                    parent = pred;
                    pred = pred->right;
                }
                node->data = pred->data; // copy value
                // remove predecessor node (which has at most a left child)
                if (parent->right == pred) {
                    // is right child of parent
                    parent->right = pred->left;
                } else {
                    // is left child of parent
                    parent->left = pred->left;
                }
                // pred is now disconnected, safe to delete
                delete pred;
            } else {
                // at most one child
                Node* old = node;
                node = (node->left != nullptr) ? node->left : node->right;
                delete old;
            }
        }
    }

    // Inorder traversal: collect all words in sorted order
    void to_vector(Node* node, std::vector<std::string>& out) const {
        if (node == nullptr) return;
        to_vector(node->left, out);
        out.push_back(node->data);
        to_vector(node->right, out);
    }

    // Build a balanced BST from a sorted vector by recursively inserting medians
    void build_balanced(const std::vector<std::string>& v, int lo, int hi) {
        if (lo > hi) return;
        int mid = lo + (hi - lo) / 2;
        insert(v[mid]);
        build_balanced(v, lo, mid - 1);
        build_balanced(v, mid + 1, hi);
    }

    // Print the tree sideways (right subtree at top, left subtree at bottom)
    void print_tree(std::ostream& os, Node* node, int indent) const {
        if (node != nullptr) {
            print_tree(os, node->right, indent + 8);
            os << std::setw(indent) << "" << node->data << std::endl;
            print_tree(os, node->left, indent + 8);
        }
    }

    // Recursively delete all nodes in the tree
    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

#endif // ASSIGNMENT_3_BST_H
