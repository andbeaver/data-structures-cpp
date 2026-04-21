#ifndef ASSIGNMENT4_EMPLOYEE_H
#define ASSIGNMENT4_EMPLOYEE_H

#include <string>
#include <sstream>

// Employee struct with all 14 fields
struct Employee {
    std::string employee_id; // 0
    std::string last_name; // 1
    std::string first_name; // 2
    std::string address; // 3
    std::string city; // 4
    std::string province; // 5
    std::string postal_code; // 6
    std::string phone; // 7
    std::string gender; // 8
    int age; // 9
    int num_of_dependents; // 10
    std::string department_cat; // 11
    std::string union_member; // 12
    double hourly_rate; // 13

    // Parse a tab-separated employee record
    static Employee parse(const std::string& line) {
        Employee emp;
        std::istringstream iss(line);
        std::string field;

        std::getline(iss, emp.employee_id, '\t');
        std::getline(iss, emp.last_name, '\t');
        std::getline(iss, emp.first_name, '\t');
        std::getline(iss, emp.address, '\t');
        std::getline(iss, emp.city, '\t');
        std::getline(iss, emp.province, '\t');
        std::getline(iss, emp.postal_code, '\t');
        std::getline(iss, emp.phone, '\t');
        std::getline(iss, emp.gender, '\t');
        std::getline(iss, field, '\t');
        emp.age = std::stoi(field);
        std::getline(iss, field, '\t');
        emp.num_of_dependents = std::stoi(field);
        std::getline(iss, emp.department_cat, '\t');
        std::getline(iss, emp.union_member, '\t');
        std::getline(iss, field);
        emp.hourly_rate = std::stod(field);

        return emp;
    }


    // Compare employees based on field number
    // Fields: 0=id, 1=last_name, 2=first_name, 3=address, 4=city, 5=province,
    //         6=postal_code, 7=phone, 8=gender, 9=age, 10=dependents,
    //         11=department, 12=union, 13=hourly_rate
    bool less_than(const Employee& other, int field) const {
        switch (field) {
            case 0: return employee_id < other.employee_id;
            case 1: return last_name < other.last_name;
            case 2: return first_name < other.first_name;
            case 3: return address < other.address;
            case 4: return city < other.city;
            case 5: return province < other.province;
            case 6: return postal_code < other.postal_code;
            case 7: return phone < other.phone;
            case 8: return gender < other.gender;
            case 9: return age < other.age;
            case 10: return num_of_dependents < other.num_of_dependents;
            case 11: return department_cat < other.department_cat;
            case 12: return union_member < other.union_member;
            case 13: return hourly_rate < other.hourly_rate;
            default: return false;
        }
    }
};

#endif // ASSIGNMENT4_EMPLOYEE_H

