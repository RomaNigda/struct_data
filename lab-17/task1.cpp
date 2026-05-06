#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

namespace lab17 {
    struct Student {
        string name;
        int group;
        int mark[4];
        float averageMark = 0.0;

        void calculateAverageMark() {
            averageMark = (mark[0] + mark[1] + mark[2] + mark[3]) / 4.0;
        }

        void show() {
            cout << name << " " << averageMark << " " << group << endl;
        }
    };

    void calculateAverageInVector(vector<Student> &students) {
        for (auto &student: students) {
            student.calculateAverageMark();
        }
    }

    void showVector(vector<Student> &students) {
        for (auto &student: students) {
            student.show();
        }
    }

    void bubbleSortByMark(vector<Student> &students) {
        for (int i = 0; i < students.size() - 1; i++) {
            for (int j = 0; j < students.size() - i - 1; j++) {
                if (students[j].averageMark > students[j + 1].averageMark) {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }

    void insertionSort(vector<Student> &students) {
        int n = students.size();
        for (int i = 1; i < n; i++) {
            Student key = students[i];
            int j = i - 1;
            while (j >= 0 && students[j].group < key.group) {
                students[j + 1] = students[j];
                j--;
            }
            students[j + 1] = key;
        }
    }

    void binarySearchByMark(vector<Student> &students, float targetMark) {
        vector<int> indexes = {};
        int n = students.size();
        int left = 0;
        int right = n - 1;
        bool flag = false;
        int mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (students[mid].averageMark == targetMark) {
                flag = true;
                break;
            }
            if (students[mid].averageMark < targetMark) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (flag) {
            indexes.push_back(mid);

            int i = mid - 1;
            while (i >= 0 && students[i].averageMark == targetMark) {
                indexes.push_back(i);
                i--;
            }

            int j = mid + 1;
            while (j < n && students[j].averageMark == targetMark) {
                indexes.push_back(j);
                j++;
            }
            sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
                return a.averageMark < b.averageMark;
            });
            for (auto i: indexes) {
                students[i].show();
            }
        } else {
            cout << "Students with this target mark not found" << endl;
        }
    }


    int lab17_task1() {
        vector<Student> students = {
            {"first", 144, {80, 90, 85, 92}, 0.0},
            {"second", 146, {85, 97, 82, 98}, 0.0},
            {"third", 147, {70, 80, 75, 92}, 0.0},
            {"fourth", 154, {84, 93, 88, 90}, 0.0},
            {"five", 147, {83, 87, 87, 91}, 0.0},
            {"six", 123, {88, 99, 85, 70}, 0.0},
        };

        cout << "\nOriginal vector" << endl;
        calculateAverageInVector(students);
        showVector(students);

        cout << "\n=====================" << endl;
        cout << "Bubble sort by mark" << endl;
        bubbleSortByMark(students);
        showVector(students);

        cout << "\n=====================" << endl;
        cout << "Insertion sort by group" << endl;
        auto students2 = students;
        insertionSort(students2);
        showVector(students2);

        cout << "\n=====================" << endl;
        cout << "Binary search by mark" << endl;
        binarySearchByMark(students, 87);

        return 0;
    }
}

int lab17_task1() {
    lab17::lab17_task1();

    return 0;
}
