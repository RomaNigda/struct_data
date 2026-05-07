#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    string name;
    string group;
    double avgGrade;
};

int lab14_task3() {
    vector<Student> students;
    int cmd;

    while (true) {
        cout << "\n1-add 2-delete 3-sort by grade 4-find by group 5-higher than 0-exit\n";
        cin >> cmd;

        if (cmd == 0) break;
        if (cmd == 1) {
            Student s;
            cin >> s.name >> s.group >> s.avgGrade;
            students.push_back(s);
        } else if (cmd == 2) {
            string name;
            cin >> name;
            auto it = remove_if(students.begin(), students.end(),
                                [&](Student &s) { return s.name == name; });
            students.erase(it, students.end());
        } else if (cmd == 3) {
            sort(students.begin(), students.end(),
                 [](Student &a, Student &b) { return a.avgGrade > b.avgGrade; });
            for (auto &s: students) {
                cout << s.name << ": " << s.avgGrade << endl;
            }
        } else if (cmd == 4) {
            string group;
            cin >> group;
            for (auto &s: students) {
                if (s.group == group) {
                    cout << s.name << endl;
                }
            }
        } else if (cmd == 5) {
            double minGrade;
            cin >> minGrade;
            for (auto &s: students) {
                if (s.avgGrade > minGrade) {
                    cout << s.name << ": " << s.avgGrade << endl;
                }
            }
        }
    }
    return 0;
}
