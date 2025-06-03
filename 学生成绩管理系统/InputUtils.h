#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>
using namespace std;	

string getChineseInput(const string& prompt, int minCount, int maxCount);

string getValidId();
string getValidName();
string getValidGender();
string getValidNation();
int getValidAge();
double getValidGrade();
string getValidAddress(int maxLength = 50);

#endif // INPUTUTILS_H
