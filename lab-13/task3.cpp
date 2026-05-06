#include <iostream>
#include <map>
#include <string>
using namespace std;

void changeGrade(map<string, int> &m, string name, int grade) {
    m[name] = grade;
}

int lab13_task3() {
    map<string, int> students = {
        {"Ivan", 85},
        {"Maria", 90}
    };
    string name;
    int grade;
    cin >> name >> grade;
    changeGrade(students, name, grade);
    for (auto &p: students) {
        cout << p.first << ": " << p.second << endl;
    }
    return 0;
}
