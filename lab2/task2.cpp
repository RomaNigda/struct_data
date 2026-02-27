#include "lab2.h"

#include <iostream>
#include <ostream>
using namespace std;

static void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void clearArray(int arr[], int size, int maxValue) {
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= maxValue) {
            arr[newSize] = arr[i];
            newSize++;
        }
    }

    for (int i = newSize; i < size; i++) {
        arr[i] = 0;
    }
}

static void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int task2_lab2(int lenOfArray, int maxValue) {
    srand(time(NULL));
    int array[lenOfArray];
    clock_t end;
    clock_t start = clock();

    fillArray(array, lenOfArray);
    showArray(array, lenOfArray);
    cout << endl;
    clearArray(array, lenOfArray, maxValue);
    showArray(array, lenOfArray);

    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    auto space = sizeof(array);
    cout << "---------------\n\n" << time << " " << space << "\n\n---------------\n\n";





    return 0;
}








