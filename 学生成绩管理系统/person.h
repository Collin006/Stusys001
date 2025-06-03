#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
using namespace std;
class Person {
public:
    string name;
    string gender;
    string nation;
    int age;
    string address;

    Person();
    Person(string _name, string _gender, string _nation, int _age, string _address);

    // 虚析构，保证多态删除安全
    virtual ~Person() {}

    // 虚函数
    virtual void displayInfo(const vector<string>& courseNames) const = 0;
};

#endif // PERSON_H

