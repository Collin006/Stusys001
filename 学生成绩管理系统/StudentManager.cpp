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
        cout << "ѧ���Ѵ��ڣ����ʧ�ܣ�" << endl;
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
    cout << "��ӳɹ���" << endl;
}

void StudentManager::showAll() const {
    if (students.empty()) {
        cout << "����ѧ����Ϣ��" << endl;
        return;
    }
    vector<Person*> results = students;
    // ����˵�
    cout << "��ѡ������ʽ��\n";
    cout << "1. ��ѧ�� 2. ������ 3. ������";
    for (size_t i = 0; i < courseNames.size(); ++i)
        cout << " " << (i + 4) << ".��" << courseNames[i] << "�ɼ�";
    cout << endl;
    int sc;
    cin >> sc;
    cout << "��ѡ������˳��1. ���� 2. ����\n";
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
            cout << "����ʽ��Ч��Ĭ�ϲ�����\n";
        }
    }
    cout << left << setw(10) << "ѧ��"
        << setw(10) << "����"
        << setw(6) << "�Ա�"
        << setw(8) << "����"
        << setw(4) << "����"
        << setw(15) << "��ַ";
    for (auto& cname : courseNames) cout << setw(8) << cname;
    cout << endl;
    for (const auto& stu : results) stu->displayInfo(courseNames);
}

int StudentManager::findById(const string& id) const {
    for (size_t i = 0; i < students.size(); ++i) {
        Student* s = dynamic_cast<Student*>(students[i]);
        if (s && s->id == id)
            return i; // ����ָ���±�
    }
    return -1;
}

void StudentManager::deleteStudent() {
    string id = getValidId();
    int idx = findById(id);
    if (idx != -1) {
        delete students[idx];
        students.erase(students.begin() + idx); // vector.erase()ֻ���ָ����������Ƴ����������Զ��ͷ�(delete)ָ��ָ����ǿ��ڴ档
        cout << "ɾ���ɹ���" << endl;
    }
    else {
        cout << "δ�ҵ���ѧ����" << endl;
    }
}

void StudentManager::modifyStudent() {
    string id = getValidId();
    int idx = findById(id);
    if (idx == -1) {
        cout << "δ�ҵ���ѧ����" << endl;
        return;
    }
    cout << "���������ѧ������Ϣ��" << endl;
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
    cout << "�޸ĳɹ���" << endl;
}

// ��ѯ���
void StudentManager::queryStudent() const {
    int qchoice;
    cout << "��ѡ���ѯ��ʽ:\n";
    cout << "1. ��ѧ��\n";
    cout << "2. ������\n";
    cout << "3. ���Ա�\n";
    cout << "4. ������\n";
    cout << "5. ����������\n";
    cout << "6. ��ĳ�ſγ̳ɼ�����\n";
    cout << "��ѡ��: ";
    cin >> qchoice;
    cin.ignore(1024, '\n');
    switch (qchoice) {
    case 1: queryById(); break;
    case 2: queryByName(); break;
    case 3: queryByGender(); break;
    case 4: queryByNation(); break;
    case 5: queryByAgeRange(); break;
    case 6: queryByCourseScore(); break;
    default: cout << "��Чѡ��\n";
    }
}

void StudentManager::queryById() const {
    string id = getValidId();
    int idx = findById(id);
    if (idx != -1) {
        // (ֻ��ʾһ���������������)
        cout << left << setw(10) << "ѧ��"
            << setw(10) << "����"
            << setw(6) << "�Ա�"
            << setw(8) << "����"
            << setw(4) << "����"
            << setw(15) << "��ַ";
        for (auto& cname : courseNames) cout << setw(8) << cname;
        cout << endl;
        students[idx]->displayInfo(courseNames);
    }
    else {
        cout << "δ�ҵ����ѧ����\n";
    }
}

void StudentManager::queryByName() const {
    string name;
    cout << "������Ҫ���ҵ�������";
    getline(cin, name);
    vector<Person*> results;
    for (const auto& p : students) {
        if (p->name == name)
            results.push_back(p);
    }
    if (results.empty()) {
        cout << "δ�ҵ����ѧ����\n";
    }
    else {
        cout << "���ҵ�" << results.size() << "λͬ��ѧ����" << endl;
        cout << left << setw(10) << "ѧ��"
            << setw(10) << "����"
            << setw(6) << "�Ա�"
            << setw(8) << "����"
            << setw(4) << "����"
            << setw(15) << "��ַ";
        for (auto& cname : courseNames) cout << setw(8) << cname;
        cout << endl;
        for (auto* p : results) p->displayInfo(courseNames);

        if (results.size() > 1) {
            cout << "ע�⣺��������ѧ���������һ�����������޸ġ�ɾ��������ʹ��ѧ�š�\n";
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
    cout << "��ǰϵͳ��¼�����壺";
    for (const auto& nation : allNations) cout << nation << " ";
    cout << endl;
    string nation;
    cout << "������Ҫ��ѯ�����壺";
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
    cout << "��������С����: "; cin >> minAge;
    cout << "�������������: "; cin >> maxAge;
    vector<Person*> results;
    for (const auto& p : students) {
        if (p->age >= minAge && p->age <= maxAge)
            results.push_back(p);
    }
    displayAndSort(results);
}

void StudentManager::queryByCourseScore() const {
    cout << "��ѡ�γ̣�";
    for (size_t i = 0; i < courseNames.size(); ++i)
        cout << i + 1 << "." << courseNames[i] << " ";
    cout << "\n��ѡ��γ̱��: ";
    int cid; cin >> cid;
    if (cid < 1 || cid >(int)courseNames.size()) {
        cout << "�γ̱����Ч��\n"; return;
    }
    double minScore, maxScore;
    cout << "��������ͷ�: "; cin >> minScore;
    cout << "��������߷�: "; cin >> maxScore;
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
        cout << "δ�ҵ����ѧ����\n";
        return;
    }
    cout << "��ѡ������ʽ��\n";
    cout << "1. ��ѧ�� 2. ������ 3. ������";
    for (size_t i = 0; i < courseNames.size(); ++i)
        cout << " " << (i + 4) << ".��" << courseNames[i] << "�ɼ�";
    cout << endl;
    int sc;
    cin >> sc;
    cout << "��ѡ������˳��1. ���� 2. ����\n";
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
            cout << "����ʽ��Ч��Ĭ�ϲ�����\n";
        }
    }
    cout << left << setw(10) << "ѧ��"
        << setw(10) << "����"
        << setw(6) << "�Ա�"
        << setw(8) << "����"
        << setw(4) << "����"
        << setw(15) << "��ַ";
    for (auto& cname : courseNames) cout << setw(8) << cname;
    cout << endl;
    for (const auto& p : results) p->displayInfo(courseNames);
}

// �ļ���ȡ 
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
