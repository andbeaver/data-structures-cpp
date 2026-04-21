#ifndef ASSIGNMENT4_SORTING_LOGIC_H
#define ASSIGNMENT4_SORTING_LOGIC_H

#include "merge_sort.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class SortingLogic {
public:
    // Main entry point for sorting
    static bool execute_sorting(const std::string& filename, int field_no) {
        // Ensure output directory exists
        if (!std::filesystem::exists("output")) {
            std::filesystem::create_directory("output");
        }

        // Extract just the filename without path for output
        std::string base_filename = filename;
        size_t last_slash = base_filename.find_last_of("/\\");
        if (last_slash != std::string::npos) {
            base_filename = base_filename.substr(last_slash + 1);
        }

        // Remove extension and add field number
        size_t dot_pos = base_filename.find_last_of(".");
        if (dot_pos != std::string::npos) {
            base_filename = base_filename.substr(0, dot_pos);
        }

        // Create output filename in output folder with field number
        std::string output_filename = "output/sorted_" + base_filename + "_" + std::to_string(field_no) + ".txt";

        // Copy input to a working file
        std::ifstream src(filename);
        if (!src.is_open()) {
            std::cerr << "ERROR: Cannot open input file: " << filename << std::endl;
            return false;
        }

        std::ofstream dst(output_filename);
        if (!dst.is_open()) {
            std::cerr << "ERROR: Cannot create output file: " << output_filename << std::endl;
            return false;
        }

        // Copy input to output file
        dst << src.rdbuf();
        src.close();
        dst.close();

        // Sort the output file in-place
        MergeSort sorter(field_no);
        sorter.sort(output_filename);

        std::cout << "Sorting " << filename << " by field " << field_no << "..." << std::endl;
        std::cout << "Sort completed successfully!" << std::endl;
        std::cout << "Output written to: " << output_filename << std::endl;
        return true;
    }
};

#endif // ASSIGNMENT4_SORTING_LOGIC_H
