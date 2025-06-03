#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>
#include <vector>

class Student : public Person {
public:
    string id;
    vector<double> grades;

    Student();
    Student(string _id, string _name, string _gender, string _nation, int _age, string _address, vector<double> _grades);

    void displayInfo(const vector<string>& courseNames) const override;
};

#endif // STUDENT_H
