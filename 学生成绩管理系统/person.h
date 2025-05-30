#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

class Person {
public:
    std::string name;
    std::string gender;
    std::string nation;
    int age;
    std::string address;

    Person();
    Person(std::string _name, std::string _gender, std::string _nation, int _age, std::string _address);

    // 虚析构，保证多态删除安全
    virtual ~Person() {}

    // 虚函数
    virtual void displayInfo(const std::vector<std::string>& courseNames) const = 0;
};

#endif // PERSON_H

