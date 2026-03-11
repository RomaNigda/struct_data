#include <iostream>
#include "lab4.h"

using namespace std;

constexpr int PASSING_SCORE = 70;

struct Abiturient {
    string name;
    string gender;
    string spec;
    float exam[3]={0, 0, 0};



};

int countVowels(const Abiturient& a) {
    int count=0;
    for (char c : a.name) {
        c = tolower(c);
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y') {
            count++;
        }
    }
    return count;
}

void displayAbiturient (Abiturient& a) {
    cout<<"Name: "<<a.name<< " Specialty: " << a.spec << " ";
    cout << "Exams: ";
    for (int i = 0; i < 3; i++) {
        cout << a.exam[i] << " ";
    }
    cout << endl;
}

void displayAbiturients (Abiturient abiturients[], int size) {
    for (int i = 0; i < size; i++) {
        displayAbiturient(abiturients[i]);
    }
}

void displayAbiturientsWhereLessVowels(Abiturient abiturients[], int size) {
    for (int i=0; i<size; i++) {
        if (countVowels(abiturients[i]) <= 3) {
            displayAbiturient(abiturients[i]);
        }
    }
}

float countExams(Abiturient& a) {
    float sum=0;
    for (int e : a.exam) {
        sum += e;
    }

    return sum/3.0;
}

void displayAbiturientUnderScore (Abiturient abiturients[], int size) {
    int count = 0;
    for (int i=0; i<size; i++) {
        if (countExams(abiturients[i]) < PASSING_SCORE) {
            displayAbiturient(abiturients[i]);
            count++;
        }
    }
    if (count == 0) {
        cout << "all abiturients pass the exam" << endl;
    }
}

void inputAbiturients(Abiturient abiturients[], int size) {
    for (int i = 0; i < size; i++) {

        cout << "\nAbiturient #" << i + 1 << endl;

        cout << "Name: ";
        cin >> abiturients[i].name;

        cout << "Gender: ";
        cin >> abiturients[i].gender;

        cout << "Specialty: ";
        cin >> abiturients[i].spec;

        cout << "Enter 3 exam results: ";
        for (int j = 0; j < 3; j++) {
            cin >> abiturients[i].exam[j];
        }
    }
}

void deleteAbiturientsWithHighScore(Abiturient abiturients[], int* size) {
    int newSize = 0;

    for (int i = 0; i < *size; i++) {
        if (countExams(abiturients[i]) <= 90) {
            if (newSize != i) {
                abiturients[newSize] = abiturients[i];
            }
            newSize++;
        }
    }

    *size = newSize; // Оновлюємо розмір масиву
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




int lab4_task1(int sizeOfArray) {
    Abiturient abiturients[sizeOfArray];

    inputAbiturients(abiturients, sizeOfArray);

    cout << "\nAbiturients with <=3 vowels in surname:\n";

    displayAbiturientsWhereLessVowels(abiturients, sizeOfArray);

    cout << "\nAbiturients with bad exam score:\n";

    displayAbiturientUnderScore(abiturients, sizeOfArray);

    cout << "\nSorted abiturients:\n";

    displaySortedAbiturients(abiturients, sizeOfArray);

    cout << "\nDeleted abiturients:\n";
    deleteAbiturientsWithHighScore(abiturients, &sizeOfArray);
    displayAbiturients(abiturients, sizeOfArray);

    return 0;
}





