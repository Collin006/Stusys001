#include "InputUtils.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

// �ж��ַ����Ƿ�ȫΪ���ú��֣�UTF-8��CJKͳһ���� 0x4E00~0x9FFF��
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
            // 2�ֽ��ַ�
            i += 2;
            count++;
        }
        else if ((c & 0xF0) == 0xE0) {
            // 3�ֽ��ַ�
            i += 3;
            count++;
        }
        else {
            // ����(����)
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
        cout << "������Ч����ȷ��Ϊ" << minCount << "-" << maxCount << "�����֡�\n";
    }
}

// ========== �������뺯������ ==========

// ѧ�ţ�8λ����
string getValidId() {
    string id;
    regex idPattern("\\d{8}");
    while (true) {
        cout << "������8λ����ѧ�ţ�";
        cin >> id;
        if (regex_match(id, idPattern)) {
            cin.ignore(1024, '\n'); // ��ֹ�� getline ���ó�ͻ
            return id;
        }
        cout << "ѧ�Ÿ�ʽ�������������룡" << endl;
    }
}

// ������1~8����
string getValidName() {
    return getChineseInput("������1-8�����֣���", 1, 8);
}

// �Ա���/Ů
string getValidGender() {
    string gender;
    while (true) {
        cout << "�Ա���/Ů����";
        cin >> gender;
        if (gender == "��" || gender == "Ů") {
            cin.ignore(1024, '\n');
            return gender;
        }
        cout << "�Ա��������������'��'��'Ů'��" << endl;
    }
}

// ���壺1~10����
string getValidNation() {
    return getChineseInput("���壨1-10�����֣���", 1, 10);
}

// ����
int getValidAge() {
    int age;
    while (true) {
        cout << "���䣨10~100����";
        cin >> age;
        if (cin.fail() || age < 10 || age > 100) {
            cout << "������Ч�����������룡" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else {
            cin.ignore(1024, '\n');
            return age;
        }
    }
}

// �ɼ�
double getValidGrade() {
    double grade;
    while (true) {
        cout << "�ɼ���0~100����";
        cin >> grade;
        if (cin.fail() || grade < 0 || grade > 100) {
            cout << "������Ч�����������룡" << endl;
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
        cout << "��ַ��������" << maxLength << "�ַ�����";
        cin >> address;
        if (address.size() <= (size_t)maxLength) return address;
        cout << "��ַ���������������룡" << endl;
    }
}
