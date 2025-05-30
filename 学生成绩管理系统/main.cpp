#include <iostream>
#include "StudentManager.h"
using namespace std;

void showMenu() {
    cout << "\n=== ѧ���ɼ�����ϵͳ ===\n";
    cout << "1. ���ѧ����Ϣ\n";
    cout << "2. ��ʾ����ѧ��\n";
    cout << "3. ��ѯѧ����Ϣ\n";
    cout << "4. ɾ��ѧ����Ϣ\n";
    cout << "5. �޸�ѧ����Ϣ\n";
    cout << "6. ���沢�˳�\n";
    cout << "��ѡ�����: ";
}

int main() {
    StudentManager manager;
    manager.loadFromFile("students.txt");
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: manager.addStudent(); break;
        case 2: manager.showAll(); break;
        case 3: manager.queryStudent(); break;
        case 4: manager.deleteStudent(); break;
        case 5: manager.modifyStudent(); break;
        case 6: manager.saveToFile("students.txt"); cout << "�����ѱ��棬�˳���\n"; return 0;
        default: cout << "��Чѡ��\n";
        }
    }
}
