#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

namespace lab16 {
    struct Student {
        string surname;
        int marks[3];
        double average;
    };

    // Функція для обчислення середнього балу
    double calculateAverage(int marks[3]) {
        return (marks[0] + marks[1] + marks[2]) / 3.0;
    }

    // Прямий пошук максимального середнього балу
    void findMaxAverage(const vector<Student> &students) {
        double maxAvg = students[0].average;

        // Знаходимо максимальний середній бал
        for (const auto &s: students) {
            if (s.average > maxAvg) {
                maxAvg = s.average;
            }
        }

        // Виводимо студентів з максимальним балом
        cout << "\nMax average score: " << maxAvg << endl;
        cout << "Students with max average:\n";

        for (int i = 0; i < students.size(); i++) {
            if (students[i].average == maxAvg) {
                cout << "Index: " << i << ", Surname: " << students[i].surname << endl;
                return;
            }
        }
    }

    // Бінарний пошук
    void binarySearch(vector<Student> &students, double target) {
        int left = 0, right = students.size() - 1;
        bool found = false;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (students[mid].average == target) {
                cout << "\nFound student(s) with average " << target << ":\n";

                // Вивід всіх однакових значень
                int i = mid;
                while (i >= 0 && students[i].average == target) {
                    cout << students[i].surname << endl;
                    i--;
                }

                i = mid + 1;
                while (i < students.size() && students[i].average == target) {
                    cout << students[i].surname << endl;
                    i++;
                }

                found = true;
                break;
            }
            if (students[mid].average < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (!found) {
            cout << "\nNo student found with this average.\n";
        }
    }

    int lab16_task1() {
        cout << "STARTING LAB16_TASK1" << endl;
        // int n;
        // cout << "Enter number of students: ";
        // cin >> n;

        vector<Student> students = {
            {"f", {3, 4, 5}, 0},
            {"s", {5, 6, 7}, 0}
        };

        // Обчислення середнього балу
        for (auto &s: students) {
            s.average = calculateAverage(s.marks);
        }

        // Ввід даних
        // for (int i = 0; i < n; i++) {
        //     cout << "\nStudent " << i + 1 << ":\n";
        //     cout << "Surname: ";
        //     cin >> students[i].surname;
        //
        //     cout << "Enter 3 marks: ";
        //     for (int j = 0; j < 3; j++) {
        //         cin >> students[i].marks[j];
        //     }
        //
        //     students[i].average = calculateAverage(students[i].marks);
        // }

        // Прямий пошук
        cout << "===========" << endl;
        findMaxAverage(students);

        cout << "===========" << endl;
        // Сортування для бінарного пошуку
        sort(students.begin(), students.end(), [](Student a, Student b) {
            return a.average < b.average;
        });
        cout << "===========" << endl;

        // Ввід для бінарного пошуку
        double target = 6.0;
        // cout << "\nEnter average to search: ";
        // cin >> target;

        binarySearch(students, target);

        return 0;
    }
}

int lab16_task1() {
    lab16::lab16_task1();
    return 0;
}


