#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>
std::string getChineseInput(const std::string& prompt, int minCount, int maxCount);

std::string getValidId();
std::string getValidName();
std::string getValidGender();
std::string getValidNation();
int getValidAge();
double getValidGrade();
std::string getValidAddress(int maxLength = 50);

#endif // INPUTUTILS_H
