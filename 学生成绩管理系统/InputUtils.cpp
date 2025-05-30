#include "InputUtils.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

// 判断字符串是否全为常用汉字（UTF-8，CJK统一汉字 0x4E00~0x9FFF）
bool isAllChinese(const string& str) {
    if (str.empty()) return false;
    for (unsigned char c : str) {
        if (c <= 0x7F) // ASCII
            return false;
    }
    return true;
}

int countChineseChars(const string& str) {
    int count = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = str[i];
        if (c <= 0x7F) {
            // ascii
            i++;
        }
        else if ((c & 0xE0) == 0xC0) {
            // 2字节字符
            i += 2;
            count++;
        }
        else if ((c & 0xF0) == 0xE0) {
            // 3字节字符
            i += 3;
            count++;
        }
        else {
            // 其它(容忍)
            i++;
            count++;
        }
    }
    return count;
}

string getChineseInput(const string& prompt, int minCount, int maxCount) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        int count = countChineseChars(input);
        if (isAllChinese(input) && count >= minCount && count <= maxCount)
            return input;
        cout << "输入无效！请确保为" << minCount << "-" << maxCount << "个汉字。\n";
    }
}

// ========== 其他输入函数不变 ==========

// 学号：8位数字
string getValidId() {
    string id;
    regex idPattern("\\d{8}");
    while (true) {
        cout << "请输入8位数字学号：";
        cin >> id;
        if (regex_match(id, idPattern)) {
            cin.ignore(1024, '\n'); // 防止与 getline 混用冲突
            return id;
        }
        cout << "学号格式错误，请重新输入！" << endl;
    }
}

// 姓名：1~8汉字
string getValidName() {
    return getChineseInput("姓名（1-8个汉字）：", 1, 8);
}

// 性别：男/女
string getValidGender() {
    string gender;
    while (true) {
        cout << "性别（男/女）：";
        cin >> gender;
        if (gender == "男" || gender == "女") {
            cin.ignore(1024, '\n');
            return gender;
        }
        cout << "性别输入错误，请输入'男'或'女'！" << endl;
    }
}

// 民族：1~10汉字
string getValidNation() {
    return getChineseInput("民族（1-10个汉字）：", 1, 10);
}

// 年龄
int getValidAge() {
    int age;
    while (true) {
        cout << "年龄（10~100）：";
        cin >> age;
        if (cin.fail() || age < 10 || age > 100) {
            cout << "输入无效，请重新输入！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else {
            cin.ignore(1024, '\n');
            return age;
        }
    }
}

// 成绩
double getValidGrade() {
    double grade;
    while (true) {
        cout << "成绩（0~100）：";
        cin >> grade;
        if (cin.fail() || grade < 0 || grade > 100) {
            cout << "输入无效，请重新输入！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else {
            cin.ignore(1024, '\n');
            return grade;
        }
    }
}

string getValidAddress(int maxLength) {
    string address;
    while (true) {
        cout << "地址（不超过" << maxLength << "字符）：";
        cin >> address;
        if (address.size() <= (size_t)maxLength) return address;
        cout << "地址过长，请重新输入！" << endl;
    }
}
