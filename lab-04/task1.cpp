#include <iostream>
#include <string>

#include "lab4.h"

using namespace std;

constexpr int PASSING_SCORE = 70;

struct Abiturient {
    string name;
    string gender;
    string spec;
    float exam[3] = {0, 0, 0};
};

int countVowels(const Abiturient &a) {
    int count = 0;
    string vowels = "aeiouy";
    for (char c: a.name) {
        c = tolower(c);
        if (vowels.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

void displayAbiturient(Abiturient &a) {
    cout << "Name: " << a.name << " Specialty: " << a.spec << " ";
    cout << "Exams: ";
    for (int i = 0; i < 3; i++) {
        cout << a.exam[i] << " ";
    }
    cout << endl;
}

void displayAbiturients(Abiturient abiturients[], int size) {
    for (int i = 0; i < size; i++) {
        displayAbiturient(abiturients[i]);
    }
}

void displayAbiturientsWhereLessVowels(Abiturient abiturients[], int size) {
    for (int i = 0; i < size; i++) {
        if (countVowels(abiturients[i]) <= 3) {
            displayAbiturient(abiturients[i]);
        }
    }
}

float countExams(Abiturient &a, float numberOfExams) {
    float sum = 0;
    for (int e: a.exam) {
        sum += e;
    }

    return sum / numberOfExams;
}

void displayAbiturientUnderScore(Abiturient abiturients[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (countExams(abiturients[i], 3.0) < PASSING_SCORE) {
            displayAbiturient(abiturients[i]);
            count++;
        }
    }
    if (count == 0) {
        cout << "all abiturients pass the exam" << endl;
    }
}

void deleteAbiturientsWithHighScore(Abiturient abiturients[], int *size) {
    int newSize = 0;

    for (int i = 0; i < *size; i++) {
        if (countExams(abiturients[i], 3.0) <= 90) {
            if (newSize != i) {
                abiturients[newSize] = abiturients[i];
            }
            newSize++;
        }
    }

    *size = newSize;
}

void displaySortedAbiturients(Abiturient abiturients[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (abiturients[i].name > abiturients[j].name) {
                swap(abiturients[i], abiturients[j]);
            }
        }
    }
    displayAbiturients(abiturients, size);
}

void inputAbiturients(Abiturient abiturients[], int size) {
    Abiturient a1;
    a1.name = "first";
    a1.spec = "comp science";
    a1.gender = "male";
    a1.exam[0] = 30;
    a1.exam[1] = 40;
    a1.exam[2] = 50;

    Abiturient a2;
    a2.name = "asecondee";
    a2.spec = "econom";
    a2.gender = "female";
    a2.exam[0] = 92;
    a2.exam[1] = 93;
    a2.exam[2] = 94;

    abiturients[0] = a1;
    abiturients[1] = a2;


    // for (int i = 0; i < size; i++) {
    //
    //     cout << "\nAbiturient #" << i + 1 << endl;
    //
    //     cout << "Name: ";
    //     cin >> abiturients[i].name;
    //
    //     cout << "Gender: ";
    //     cin >> abiturients[i].gender;
    //
    //     cout << "Specialty: ";
    //     cin >> abiturients[i].spec;
    //
    //     cout << "Enter 3 exam results: ";
    //     for (int j = 0; j < 3; j++) {
    //         cin >> abiturients[i].exam[j];
    //     }
    // }
}


int lab4_task1(int sizeOfArray) {
    Abiturient abiturients[sizeOfArray];


    inputAbiturients(abiturients, sizeOfArray);

    cout << "\nAll Abiturients:\n";
    displayAbiturients(abiturients, sizeOfArray);

    cout << "\nAbiturients with <=3 vowels in surname:\n";

    displayAbiturientsWhereLessVowels(abiturients, sizeOfArray);

    cout << "\nAbiturients with bad exam score:\n";

    displayAbiturientUnderScore(abiturients, sizeOfArray);

    cout << "\nSorted abiturients:\n";

    displaySortedAbiturients(abiturients, sizeOfArray);

    cout << "\nAbiturients after delete:\n";
    deleteAbiturientsWithHighScore(abiturients, &sizeOfArray);
    displayAbiturients(abiturients, sizeOfArray);

    return 0;
}





