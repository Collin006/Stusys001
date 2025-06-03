#include "StudentManager.h"
#include "InputUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <algorithm>
using namespace std;

StudentManager::StudentManager() {
    courseNames = { "Math", "English", "CS" };
}

StudentManager::~StudentManager() {
    for (auto p : students) delete p;
}

void StudentManager::addStudent() {
    string id = getValidId();
    if (findById(id) != -1) {
        cout << "学号已存在，添加失败！" << endl;
        return;
    }
    string name = getValidName();
    string gender = getValidGender();
    string nation = getValidNation();
    int age = getValidAge();
    string address = getValidAddress(30);
    vector<double> grades(courseNames.size());
    for (size_t i = 0; i < courseNames.size(); ++i) {
        cout << courseNames[i];
        grades[i] = getValidGrade();
    }
    students.push_back(new Student(id, name, gender, nation, age, address, grades));
    cout << "添加成功！" << endl;
}

void StudentManager::showAll() const {
    if (students.empty()) {
        cout << "暂无学生信息。" << endl;
        return;
    }
    vector<Person*> results = students;
    // 排序菜单
    cout << "请选择排序方式：\n";
    cout << "1. 按学号 2. 按姓名 3. 按年龄";
    for (size_t i = 0; i < courseNames.size(); ++i)
        cout << " " << (i + 4) << ".按" << courseNames[i] << "成绩";
    cout << endl;
    int sc;
    cin >> sc;
    cout << "请选择排序顺序：1. 升序 2. 降序\n";
    int order;
    cin >> order;
    bool asc = (order == 1);

    switch (sc) {
    case 1:
        sort(results.begin(), results.end(),
            [asc](Person* a, Person* b) {
                Student* sa = dynamic_cast<Student*>(a);
                Student* sb = dynamic_cast<Student*>(b);
                return asc ? sa->id < sb->id : sa->id > sb->id;
            }); break;
    case 2:
        sort(results.begin(), results.end(),
            [asc](Person* a, Person* b) {
                return asc ? a->name < b->name : a->name > b->name;
            }); break;
    case 3:
        sort(results.begin(), results.end(),
            [asc](Person* a, Person* b) {
                return asc ? a->age < b->age : a->age > b->age;
            }); break;
    default:
        if (sc >= 4 && sc < 4 + (int)courseNames.size()) {
            int cid = sc - 4;
            sort(results.begin(), results.end(),
                [asc, cid](Person* a, Person* b) {
                    Student* sa = dynamic_cast<Student*>(a);
                    Student* sb = dynamic_cast<Student*>(b);
                    return asc ? sa->grades[cid] < sb->grades[cid] : sa->grades[cid] > sb->grades[cid];
                });
        }
        else {
            cout << "排序方式无效，默认不排序。\n";
        }
    }
    cout << left << setw(10) << "学号"
        << setw(10) << "姓名"
        << setw(6) << "性别"
        << setw(8) << "民族"
        << setw(4) << "年龄"
        << setw(15) << "地址";
    for (auto& cname : courseNames) cout << setw(8) << cname;
    cout << endl;
    for (const auto& stu : results) stu->displayInfo(courseNames);
}

int StudentManager::findById(const string& id) const {
    for (size_t i = 0; i < students.size(); ++i) {
        Student* s = dynamic_cast<Student*>(students[i]);
        if (s && s->id == id)
            return i; // 返回指针下标
    }
    return -1;
}

void StudentManager::deleteStudent() {
    string id = getValidId();
    int idx = findById(id);
    if (idx != -1) {
        delete students[idx];
        students.erase(students.begin() + idx); // vector.erase()只会把指针从容器中移除，但不会自动释放(delete)指针指向的那块内存。
        cout << "删除成功！" << endl;
    }
    else {
        cout << "未找到该学生。" << endl;
    }
}

void StudentManager::modifyStudent() {
    string id = getValidId();
    int idx = findById(id);
    if (idx == -1) {
        cout << "未找到该学生。" << endl;
        return;
    }
    cout << "重新输入该学生的信息：" << endl;
    string name = getValidName();
    string gender = getValidGender();
    string nation = getValidNation();
    int age = getValidAge();
    string address = getValidAddress(30);
    vector<double> grades(courseNames.size());
    for (size_t i = 0; i < courseNames.size(); ++i) {
        cout << courseNames[i];
        grades[i] = getValidGrade();
    }
    delete students[idx];
    students[idx] = new Student(id, name, gender, nation, age, address, grades);
    cout << "修改成功！" << endl;
}

// 查询入口
void StudentManager::queryStudent() const {
    int qchoice;
    cout << "请选择查询方式:\n";
    cout << "1. 按学号\n";
    cout << "2. 按姓名\n";
    cout << "3. 按性别\n";
    cout << "4. 按民族\n";
    cout << "5. 按年龄区间\n";
    cout << "6. 按某门课程成绩区间\n";
    cout << "请选择: ";
    cin >> qchoice;
    cin.ignore(1024, '\n');
    switch (qchoice) {
    case 1: queryById(); break;
    case 2: queryByName(); break;
    case 3: queryByGender(); break;
    case 4: queryByNation(); break;
    case 5: queryByAgeRange(); break;
    case 6: queryByCourseScore(); break;
    default: cout << "无效选择。\n";
    }
}

void StudentManager::queryById() const {
    string id = getValidId();
    int idx = findById(id);
    if (idx != -1) {
        // (只显示一个结果，无需排序)
        cout << left << setw(10) << "学号"
            << setw(10) << "姓名"
            << setw(6) << "性别"
            << setw(8) << "民族"
            << setw(4) << "年龄"
            << setw(15) << "地址";
        for (auto& cname : courseNames) cout << setw(8) << cname;
        cout << endl;
        students[idx]->displayInfo(courseNames);
    }
    else {
        cout << "未找到相关学生。\n";
    }
}

void StudentManager::queryByName() const {
    string name;
    cout << "请输入要查找的姓名：";
    getline(cin, name);
    vector<Person*> results;
    for (const auto& p : students) {
        if (p->name == name)
            results.push_back(p);
    }
    if (results.empty()) {
        cout << "未找到相关学生。\n";
    }
    else {
        cout << "共找到" << results.size() << "位同名学生：" << endl;
        cout << left << setw(10) << "学号"
            << setw(10) << "姓名"
            << setw(6) << "性别"
            << setw(8) << "民族"
            << setw(4) << "年龄"
            << setw(15) << "地址";
        for (auto& cname : courseNames) cout << setw(8) << cname;
        cout << endl;
        for (auto* p : results) p->displayInfo(courseNames);

        if (results.size() > 1) {
            cout << "注意：存在重名学生，如需进一步操作（如修改、删除），请使用学号。\n";
        }
    }
}

void StudentManager::queryByGender() const {
    string gender = getValidGender();
    vector<Person*> results;
    for (const auto& p : students) {
        if (p->gender == gender)
            results.push_back(p);
    }
    displayAndSort(results);
}

void StudentManager::queryByNation() const {
    set<string> allNations;
    for (const auto& p : students) allNations.insert(p->nation);
    cout << "当前系统已录入民族：";
    for (const auto& nation : allNations) cout << nation << " ";
    cout << endl;
    string nation;
    cout << "请输入要查询的民族：";
    cin >> nation;
    vector<Person*> results;
    for (const auto& p : students) {
        if (p->nation == nation)
            results.push_back(p);
    }
    displayAndSort(results);
}

void StudentManager::queryByAgeRange() const {
    int minAge, maxAge;
    cout << "请输入最小年龄: "; cin >> minAge;
    cout << "请输入最大年龄: "; cin >> maxAge;
    vector<Person*> results;
    for (const auto& p : students) {
        if (p->age >= minAge && p->age <= maxAge)
            results.push_back(p);
    }
    displayAndSort(results);
}

void StudentManager::queryByCourseScore() const {
    cout << "可选课程：";
    for (size_t i = 0; i < courseNames.size(); ++i)
        cout << i + 1 << "." << courseNames[i] << " ";
    cout << "\n请选择课程编号: ";
    int cid; cin >> cid;
    if (cid < 1 || cid >(int)courseNames.size()) {
        cout << "课程编号无效。\n"; return;
    }
    double minScore, maxScore;
    cout << "请输入最低分: "; cin >> minScore;
    cout << "请输入最高分: "; cin >> maxScore;
    vector<Person*> results;
    for (const auto& p : students) {
        Student* s = dynamic_cast<Student*>(p);
        if (s) {
            double score = s->grades[cid - 1];
            if (score >= minScore && score <= maxScore)
                results.push_back(p);
        }
    }
    displayAndSort(results);
}

void StudentManager::displayAndSort(vector<Person*> results) const {
    if (results.empty()) {
        cout << "未找到相关学生。\n";
        return;
    }
    cout << "请选择排序方式：\n";
    cout << "1. 按学号 2. 按姓名 3. 按年龄";
    for (size_t i = 0; i < courseNames.size(); ++i)
        cout << " " << (i + 4) << ".按" << courseNames[i] << "成绩";
    cout << endl;
    int sc;
    cin >> sc;
    cout << "请选择排序顺序：1. 升序 2. 降序\n";
    int order;
    cin >> order;
    bool asc = (order == 1);

    switch (sc) {
    case 1:
        sort(results.begin(), results.end(),
            [asc](Person* a, Person* b) {
                Student* sa = dynamic_cast<Student*>(a);
                Student* sb = dynamic_cast<Student*>(b);
                return asc ? sa->id < sb->id : sa->id > sb->id;
            }); break;
    case 2:
        sort(results.begin(), results.end(),
            [asc](Person* a, Person* b) {
                return asc ? a->name < b->name : a->name > b->name;
            }); break;
    case 3:
        sort(results.begin(), results.end(),
            [asc](Person* a, Person* b) {
                return asc ? a->age < b->age : a->age > b->age;
            }); break;
    default:
        if (sc >= 4 && sc < 4 + (int)courseNames.size()) {
            int cid = sc - 4;
            sort(results.begin(), results.end(),
                [asc, cid](Person* a, Person* b) {
                    Student* sa = dynamic_cast<Student*>(a);
                    Student* sb = dynamic_cast<Student*>(b);
                    return asc ? sa->grades[cid] < sb->grades[cid] : sa->grades[cid] > sb->grades[cid];
                });
        }
        else {
            cout << "排序方式无效，默认不排序。\n";
        }
    }
    cout << left << setw(10) << "学号"
        << setw(10) << "姓名"
        << setw(6) << "性别"
        << setw(8) << "民族"
        << setw(4) << "年龄"
        << setw(15) << "地址";
    for (auto& cname : courseNames) cout << setw(8) << cname;
    cout << endl;
    for (const auto& p : results) p->displayInfo(courseNames);
}

// 文件存取 
void StudentManager::saveToFile(const string& filename) const {
    ofstream fout(filename);
    for (const auto& p : students) {
        Student* s = dynamic_cast<Student*>(p);
        if (s) {
            fout << s->id << " " << s->name << " " << s->gender << " " << s->nation << " "
                << s->age << " " << s->address;
            for (auto g : s->grades) fout << " " << g;
            fout << endl;
        }
    }
    fout.close();
}

void StudentManager::loadFromFile(const string& filename) {
    for (auto p : students) delete p;
    students.clear();
    ifstream fin(filename);
    if (!fin) return;
    while (!fin.eof()) {
        string id, name, gender, nation, address;
        int age;
        vector<double> grades(courseNames.size());
        fin >> id >> name >> gender >> nation >> age >> address;
        for (size_t i = 0; i < courseNames.size(); ++i)
            fin >> grades[i];
        if (!id.empty())
            students.push_back(new Student(id, name, gender, nation, age, address, grades));
    }
    fin.close();
}
