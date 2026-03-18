#include <iostream>

#include "lab3.h"

using namespace std;

enum Faculty {
    ComputerScience,
    Marketing,
    Economy
};

struct Student {
    string surname;
    int course;
    int averageGrade;
    Faculty faculty;

    void display() {
        cout << surname << " " << course << " " << averageGrade << " " << faculty << endl;
    }
};

float countAverageGrade(Student students[], int size) {
    float averageGrade = 0.0;
    for (int i = 0; i < size; i++) {
        averageGrade = averageGrade + (float) students[i].averageGrade;
    }
    return averageGrade / float(size);
}


int lab3_task2(int sizeOfArray) {
    Student students[sizeOfArray];

    for (int i = 0; i < sizeOfArray; i++) {
        students[i] = Student();
        string temp;

        cout << "enter student surname: ";
        cin >> students[i].surname;
        cout << "enter student course: ";
        cin >> students[i].course;
        cout << "enter student average grade: ";
        cin >> students[i].averageGrade;
        cout << "enter student faculty: ";
        cin >> temp;
        if (temp == "ComputerScience") {
            students[i].faculty = ComputerScience;
        } else if (temp == "Marketing") {
            students[i].faculty = Marketing;
        } else {
            students[i].faculty = Economy;
        }
    }

    for (int i = 0; i < sizeOfArray; i++) {
        if (students[i].faculty == ComputerScience) {
            students[i].display();
        }
    }


    cout << "average grade: " << countAverageGrade(students, sizeOfArray);


    return 0;
}


