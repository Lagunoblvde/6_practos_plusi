#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Student {
private:
    std::string name;
    std::string group;
    std::vector<std::string> disciplines;
    int completedAssignments;
    int debts;

public:
    Student(const std::string& name, const std::string& group, const std::vector<std::string>& disciplines)
        : name(name), group(group), disciplines(disciplines), completedAssignments(0), debts(0) {}

    void submitAssignment() {
        completedAssignments++;
    }

    void addDebt() {
        debts++;
    }

    bool shouldRemoveFromGroup() const {
        return debts > 5;
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getGroup() const {
        return group;
    }
};


class Teacher {
private:
    std::string name;
    std::string discipline;
    std::vector<std::string> groups;

public:
    Teacher(const std::string& name, const std::string& discipline, const std::vector<std::string>& groups)
        : name(name), discipline(discipline), groups(groups) {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getDiscipline() const {
        return discipline;
    }

    const std::vector<std::string>& getGroups() const {
        return groups;
    }
};


class MoscowTechnicalCollege {
private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;

public:
    void addStudent(const std::string& name, const std::string& group, const std::vector<std::string>& disciplines) {
        students.emplace_back(name, group, disciplines);
    }

    void addTeacher(const std::string& name, const std::string& discipline, const std::vector<std::string>& groups) {
        teachers.emplace_back(name, discipline, groups);
    }

    void submitWork(const std::string& studentName) {
        auto it = std::find_if(students.begin(), students.end(),
            [&studentName](const Student& student) { return student.getName() == studentName; });
        if (it != students.end()) {
            it->submitAssignment();
        }
    }

    void addDebt(const std::string& studentName) {
        auto it = std::find_if(students.begin(), students.end(),
            [&studentName](const Student& student) { return student.getName() == studentName; });
        if (it != students.end()) {
            it->addDebt();
            if (it->shouldRemoveFromGroup()) {
                students.erase(it);
                std::cout << "Студент " << studentName << " исключен из группы из-за большого количества долгов.\n";
            }
        }
    }

    int countStudentsInGroup(const std::string& groupName) const {
        return std::count_if(students.begin(), students.end(),
            [&groupName](const Student& student) { return student.getGroup() == groupName; });
    }

    void displayCurrentState() const {
        std::cout << "Состояние МПТ:\n";
        std::cout << "Студенты:\n";
        for (const auto& student : students) {
            std::cout << "- " << student.getName() << ", Группа: " << student.getGroup() << "\n";
        }
        std::cout << "Преподаватели:\n";
        for (const auto& teacher : teachers) {
            std::cout << "- " << teacher.getName() << ", Дисциплина: " << teacher.getDiscipline() << "\n";
        }
    }
};


int main() {
    MoscowTechnicalCollege mpt;
    setlocale(LC_ALL, "RUS");
    mpt.addStudent("Иванов", "Группа А", { "Математика", "Физика" });
    mpt.addStudent("Петров", "Группа Б", { "Информатика", "Электротехника" });
    mpt.addTeacher("Сидоров", "Математика", { "Группа А" });
    mpt.addTeacher("Кузнецов", "Информатика", { "Группа Б" });


    mpt.submitWork("Иванов");
    mpt.addDebt("Петров");

    std::string groupName = "Группа А";
    int numStudents = mpt.countStudentsInGroup(groupName);
    std::cout << "Количество студентов в группе " << groupName << ": " << numStudents << "\n";

    mpt.displayCurrentState();

    return 0;
}
