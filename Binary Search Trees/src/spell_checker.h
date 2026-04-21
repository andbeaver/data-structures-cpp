#ifndef ASSIGNMENT_3_SPELL_CHECKER_H
#define ASSIGNMENT_3_SPELL_CHECKER_H

#include "bst.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class SpellChecker {
private:
    BST dictionary;

    // Normalize a word: lowercase and keep only alphabetic characters
    static std::string normalize_word(const std::string& raw) {
        std::string result;
        for (char c : raw) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
            }
        }
        return result;
    }

public:
    SpellChecker() = default;

    // Load dictionary from file, one word per line
    // Returns true if file opened successfully
    bool load_dictionary(const std::string& dict_path) {
        std::ifstream in(dict_path);
        if (!in.is_open()) {
            std::cerr << "Error: Could not open dictionary file: " << dict_path << std::endl;
            return false;
        }

        std::string line;
        int count = 0;
        // Read each line, normalize it, and insert into the dictionary tree
        while (std::getline(in, line)) {
            std::string word = normalize_word(line);
            if (!word.empty()) {
                dictionary.insert(word);
                count++;
            }
        }

        in.close();
        // Report how many words were loaded
        std::cout << "Loaded " << count << " words from dictionary." << std::endl;
        return true;
    }

    // Balance the dictionary tree
    void balance_dictionary() {
        dictionary.balance();
        std::cout << "Dictionary tree balanced." << std::endl;
    }

    // Check a document for misspelled words
    // Returns a vector of misspelled words (in order encountered, duplicates included)
    std::vector<std::string> check_document(const std::string& doc_path) {
        std::ifstream in(doc_path);
        if (!in.is_open()) {
            // If the document can't be opened, return an empty list and print an error
            std::cerr << "Error: Could not open document file: " << doc_path << std::endl;
            return {};
        }

        std::vector<std::string> misspelled;
        std::string word;
        char ch;

        // Read the document character by character, building words from sequences of alphabetic chars
        while (in.get(ch)) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                word.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
            } else {
                // Non-alphabetic character ends the word
                if (!word.empty()) {
                    if (!dictionary.contains(word)) {
                        misspelled.push_back(word);
                    }
                    word.clear();
                }
            }
        }

        // Check the last word if the document ended with an alphabetic character
        if (!word.empty()) {
            if (!dictionary.contains(word)) {
                misspelled.push_back(word);
            }
        }

        in.close();
        return misspelled;
    }

    // Write the balanced tree to a file
    // Returns true if file write was successful
    bool write_tree(const std::string& output_path) {
        std::ofstream out(output_path);
        if (!out.is_open()) {
            // If the output file can't be opened, print an error and return false
            std::cerr << "Error: Could not open output file: " << output_path << std::endl;
            return false;
        }

        out << dictionary;
        out.close();
        // Report that the tree was written successfully
        std::cout << "Balanced tree written to: " << output_path << std::endl;
        return true;
    }
};

#endif // ASSIGNMENT_3_SPELL_CHECKER_H
