#include <iostream>
#include <ostream>

#include "lab2.h"

using namespace std;

static void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

static void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

static void fillMatrix(int matrix[][5], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

static void showMatrix(int matrix[][5], int size) {
    cout << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void findMaxValue(int& x, int& y, int matrix[][5], int size) {
    int max = matrix[0][0];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] > max) {
                x = i;
                y = j;
            }
        }
    }
    cout << "max value: ";
    cout << x << " " << y << " " << matrix[x][y] << endl;
}

void swapColumn(int column, int matrix[][5], int size) {
    for (int i = 0; i < size; i++) {
        swap(matrix[i][0], matrix[i][column]);
    }
    showMatrix(matrix, size);
}
void swapRow(int row, int matrix[][5], int size) {
    for (int i = 0; i < size; i++) {
        swap(matrix[row][i], matrix[0][i]);
    }
    showMatrix(matrix, size);
}


void transformMatrix(int matrix[][5], int size) {
    int x, y;
    findMaxValue(x, y, matrix, size);
    swapColumn(y, matrix, size);
    swapRow(x, matrix, size);

}




int task3_lab2() {
    int matrix[5][5];
    srand(time(NULL));
    clock_t end;
    clock_t start = clock();


    fillMatrix(matrix, 5);
    showMatrix(matrix, 5);
    transformMatrix(matrix, 5);

    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "---------------\n\n" << time << "\n\n---------------\n\n";








    return 0;
}


