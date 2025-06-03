#include "Person.h"

Person::Person() {}

Person::Person(string _name, string _gender, string _nation, int _age, string _address)
    : name(_name), gender(_gender), nation(_nation), age(_age), address(_address) {
}
