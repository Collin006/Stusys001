#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <string>

class StudentManager {
private:
    std::vector<Person*> students;
    std::vector<std::string> courseNames;
public:
    StudentManager();
    ~StudentManager();

    void addStudent();
    void showAll() const;
    int findById(const std::string& id) const;
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

    void displayAndSort(std::vector<Person*> results) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::vector<std::string> getCourseNames() const { return courseNames; }
    std::vector<Person*> getStudents() const { return students; }
};

#endif // STUDENTMANAGER_H
