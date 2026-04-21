//
// Created by andre on 2026-04-05.
//

#ifndef ASSIGNMENT4_MERGE_SORT_H
#define ASSIGNMENT4_MERGE_SORT_H

#include <fstream>
#include <string>
#include <filesystem>
#include "employee.h"

// Merge sort implementation using temporary files
class MergeSort {
private:
    int sort_field;
    int temp_file_counter;

    std::string get_temp_filename() {
        return "./temp_" + std::to_string(temp_file_counter++) + ".txt";
    }

    // Split input file into two temporary files
    void split_file(const std::string& input_file, std::string& out_file1, std::string& out_file2) {
        std::ifstream infile(input_file);
        std::ofstream file1(out_file1), file2(out_file2);

        std::string line;
        bool write_to_first = true;

        // Read lines from input file and alternate writing to the two output files
        while (std::getline(infile, line)) {
            if (write_to_first) {
                file1 << line << "\n";
            } else {
                file2 << line << "\n";
            }
            write_to_first = !write_to_first;
        }

        infile.close();
        file1.close();
        file2.close();
    }

    // Merge two sorted files into output file
    void merge_files(const std::string& file1, const std::string& file2, const std::string& output_file) {
        std::ifstream in1(file1), in2(file2);
        std::ofstream out(output_file);

        std::string line1, line2;
        bool has_line1 = (bool)std::getline(in1, line1);
        bool has_line2 = (bool)std::getline(in2, line2);

        // Merge lines from both files based on the sort field
        while (has_line1 || has_line2) {
            if (has_line1 && has_line2) {
                Employee emp1 = Employee::parse(line1);
                Employee emp2 = Employee::parse(line2);

                if (emp1.less_than(emp2, sort_field)) {
                    out << line1 << "\n";
                    has_line1 = (bool)std::getline(in1, line1);
                } else {
                    out << line2 << "\n";
                    has_line2 = (bool)std::getline(in2, line2);
                }
            } else if (has_line1) {
                out << line1 << "\n";
                has_line1 = (bool)std::getline(in1, line1);
            } else if (has_line2) {
                out << line2 << "\n";
                has_line2 = (bool)std::getline(in2, line2);
            }
        }

        in1.close();
        in2.close();
        out.close();
    }

    // Recursively sort using merge sort
    void merge_sort_recursive(const std::string& input_file) {
        // Count lines to determine if we need to split
        std::ifstream infile(input_file);
        int line_count = 0;
        std::string line;
        while (std::getline(infile, line)) {
            line_count++;
        }
        infile.close();

        // 0 or 1 line, already sorted
        if (line_count <= 1) {
            return;
        }

        // Split into two files
        std::string temp1 = get_temp_filename();
        std::string temp2 = get_temp_filename();
        split_file(input_file, temp1, temp2);

        // Recursively sort both halves
        merge_sort_recursive(temp1);
        merge_sort_recursive(temp2);

        // Merge the sorted files
        merge_files(temp1, temp2, input_file);

        // Clean up temporary files
        std::filesystem::remove(temp1);
        std::filesystem::remove(temp2);
    }

public:
    // Constructor takes the field number to sort by
    MergeSort(int field) : sort_field(field), temp_file_counter(0) {}

    // Main entry point to sort the file
    void sort(const std::string& filename) {
        merge_sort_recursive(filename);
    }
};

#endif // ASSIGNMENT4_MERGE_SORT_H
