#include <iostream>
#include "StudentManager.h"
using namespace std;

void showMenu() {
    cout << "\n=== 学生成绩管理系统 ===\n";
    cout << "1. 添加学生信息\n";
    cout << "2. 显示所有学生\n";
    cout << "3. 查询学生信息\n";
    cout << "4. 删除学生信息\n";
    cout << "5. 修改学生信息\n";
    cout << "6. 保存并退出\n";
    cout << "请选择操作: ";
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
        case 6: manager.saveToFile("students.txt"); cout << "数据已保存，退出。\n"; return 0;
        default: cout << "无效选择！\n";
        }
    }
}
