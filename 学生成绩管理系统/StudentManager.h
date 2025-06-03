#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;    

class StudentManager {
private:
    vector<Person*> students;
    vector<string> courseNames;
public:
    StudentManager();
    ~StudentManager();

    void addStudent();
    void showAll() const;
    int findById(const string& id) const;
    void deleteStudent();
    void modifyStudent();
    // ...其它查询和排序声明（同你原来的即可）...
    // 查询相关
    void queryStudent() const;
    void queryById() const;
    void queryByName() const;
    void queryByGender() const;
    void queryByNation() const;
    void queryByAgeRange() const;
    void queryByCourseScore() const;

    void displayAndSort(vector<Person*> results) const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    vector<string> getCourseNames() const { return courseNames; }
    vector<Person*> getStudents() const { return students; }
};

#endif // STUDENTMANAGER_H
