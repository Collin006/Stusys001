#include "Student.h"
#include <iostream>
#include <iomanip>
using namespace std;

Student::Student() : Person() {}

Student::Student(string _id, string _name, string _gender, string _nation, int _age, string _address, vector<double> _grades)
    : Person(_name, _gender, _nation, _age, _address), id(_id), grades(_grades) {
}

void Student::displayInfo(const vector<string>& courseNames) const {
    cout << left << setw(10) << id
        << setw(10) << name
        << setw(6) << gender
        << setw(8) << nation
        << setw(4) << age
        << setw(15) << address;
    for (size_t i = 0; i < grades.size(); ++i) {
        cout << setw(8) << grades[i];
    }
    cout << endl;
}
