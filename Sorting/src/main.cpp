#include <iostream>
#include <string>
#include "sorting_logic.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        // Print instructions if args are missing or incorrect
        cout << "Usage: " << argv[0] << " <filename> -field=<fieldno>" << endl;
        cout << "Field numbers: 0=ID, 1=Last Name, 2=First Name, 3=Address, 4=City," << endl;
        cout << "               5=Province, 6=Postal Code, 7=Phone, 8=Gender, 9=Age," << endl;
        cout << "               10=Dependents, 11=Department, 12=Union, 13=Hourly Rate" << endl;
        return 1;
    }

    string filename = argv[1];
    string field_arg = argv[2];

    // Parse the field number from the argument
    if (field_arg.substr(0, 7) != "-field=") {
        cout << "Invalid argument format. Use -field=<fieldno>" << endl;
        return 1;
    }

    int field_no = stoi(field_arg.substr(7));

    // Validate field number is valid
    if (field_no < 0 || field_no > 13) {
        cout << "Field number must be between 0 and 13." << endl;
        return 1;
    }

    // Execute the sorting logic
    return SortingLogic::execute_sorting(filename, field_no) ? 0 : 1;
}
