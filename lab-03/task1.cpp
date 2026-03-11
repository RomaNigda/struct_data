#include <iostream>

#include "lab3.h"

using namespace std;

constexpr int YEAR = 2026;
constexpr int TAXES = 33;



struct worker {
    string fullname;
    string position;
    int yearWhenStart;
    float salary;


};


int experience(worker w) {
    return YEAR - w.yearWhenStart;
}

float salary(worker w) {
    return w.salary * (100 - TAXES)/100.0;
}



int lab3_task1() {
    worker w1("first", "junior", 2020, 20000);
    worker w2("second", "junior", 2017, 30000);

    worker workers[2] = {w1, w2};

    for (worker w : workers) {
        cout << experience(w) << " " << salary(w) << endl;
    }





    return 0;
}







