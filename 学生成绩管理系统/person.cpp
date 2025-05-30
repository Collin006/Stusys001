#include "Person.h"

Person::Person() {}

Person::Person(std::string _name, std::string _gender, std::string _nation, int _age, std::string _address)
    : name(_name), gender(_gender), nation(_nation), age(_age), address(_address) {
}
