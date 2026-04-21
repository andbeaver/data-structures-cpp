#include "spell_checker.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Check for required arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << "<dictionary_file><document_file><output_file>" << std::endl;
        std::cerr << std::endl;
        std::cerr << "Ex. dictionary.txt document.txt output/balanced_tree.txt" << std::endl;
        return 1;
    }

    std::string dict_file = argv[1];
    std::string doc_file = argv[2];
    std::string output_file = argv[3];

    std::cout << "Dictionary: " << dict_file << std::endl;
    std::cout << "Document: " << doc_file << std::endl;
    std::cout << "Output: " << output_file << std::endl << std::endl;

    // Create spell checker instance
    SpellChecker sc;

    // Load dictionary
    std::cout << "Loading dictionary..." << std::endl;
    if (!sc.load_dictionary(dict_file)) {
        std::cerr << "Failed to load dictionary. Exiting." << std::endl;
        return 1;
    }
    std::cout << std::endl;
    // flush output to ensure it appears before any potential errors
    std::cout.flush();

    // Balance the tree
    std::cout << "Balancing tree..." << std::endl;
    sc.balance_dictionary();
    std::cout << std::endl;
    std::cout.flush();

    // Check document for misspellings
    std::cout << "Checking document for misspellings..." << std::endl;
    auto misspelled = sc.check_document(doc_file);
    std::cout << std::endl;
    std::cout.flush();

    // Display results
    if (misspelled.empty()) {
        std::cout << "No misspellings found!" << std::endl;
    } else {
        std::cout << "Misspelled words found:" << std::endl;
        for (const auto& word : misspelled) {
            std::cout << " - " << word << std::endl;
        }
    }
    std::cout << std::endl;

    // Write balanced tree to file
    std::cout << "Writing balanced tree to output..." << std::endl;
    if (!sc.write_tree(output_file)) {
        std::cerr << "Failed to write balanced tree. Exiting." << std::endl;
        return 1;
    }
    std::cout << std::endl;

    return 0;
}
