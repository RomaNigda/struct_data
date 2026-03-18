#include <iostream>

#include "lab3.h"

using namespace std;

constexpr int YEAR = 2026;
constexpr int TAXES = 33;

struct Worker {
    string fullname;
    string position;
    int yearWhenStart;
    float salary;
};


int experience(const Worker &w, int year) {
    if (year < w.yearWhenStart) {
        return 0;
    }
    return YEAR - w.yearWhenStart;
}

float salary(Worker w) {
    return w.salary * (100 - TAXES) / 100.0;
}


int lab3_task1() {
    Worker w1("first", "junior", 2020, 20000);
    Worker w2("second", "junior", 2017, 30000);

    Worker Workers[2] = {w1, w2};

    for (Worker w: Workers) {
        cout << experience(w, 2026) << " " << salary(w) << endl;
    }


    return 0;
}







