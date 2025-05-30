#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>
#include <vector>

class Student : public Person {
public:
    std::string id;
    std::vector<double> grades;

    Student();
    Student(std::string _id, std::string _name, std::string _gender, std::string _nation, int _age, std::string _address, std::vector<double> _grades);

    void displayInfo(const std::vector<std::string>& courseNames) const override;
};

#endif // STUDENT_H
