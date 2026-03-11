#include "lab2.h"

#include <iostream>
#include <ostream>
using namespace std;

static void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

int countEven(int arr[], int size) {
    int even = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            even++;
        }
    }
    return even;
}

void sortEvenOdd(int arr[], int size) {
    int result[size];
    int index = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            result[index++] = arr[i];
        }
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[index++] = arr[i];
        }
    }

    for (int i = 0; i < size; i++) {
        arr[i] = result[i];
    }
}

void sortSequence(int arr[], int size, int even) {
    for (int i = 0; i < even; i++) {
        for (int j = i; j < even; j++) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
    for (int i = even; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (arr[i] < arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

void putOnTheirPlaces(int arr[], int size) {
    sortEvenOdd(arr, size);
    int even = countEven(arr, size);
    sortSequence(arr, size, even);
}

static void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}



int lab2_task1(int lenOfArray) {
    srand(time(NULL));
    int array[lenOfArray];

    clock_t start = clock();


    fillArray(array, lenOfArray);

    // cout << "task1_lab2()" << endl;

    showArray(array, lenOfArray);

    cout << "---------------" << endl;

    putOnTheirPlaces(array, lenOfArray);
    showArray(array, lenOfArray);

    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "---------------\n\n" << time << "\n\n---------------\n\n";


    return 0;
}
