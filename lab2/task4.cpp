#include <iostream>
#include <ostream>
#include <vector>

#include "lab2.h"

using namespace std;

static void fillMatrix(vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

static void showMatrix(vector<vector<int>>& matrix) {
    cout << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

static void findMaxValue(int& x, int& y, vector<vector<int>>& matrix) {
    int max = matrix[0][0];
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] > max) {
                x = i;
                y = j;
                max = matrix[i][j];
            }
        }
    }
    cout << "max value: ";
    cout << x << " " << y << " " << matrix[x][y] << endl;
}

void deleteMainDiagonalMatrix(vector<vector<int>>& matrix, int size) {
    vector<vector<int>> newMatrix;
    for (int i = 0; i < size; i++) {
        vector<int> row;

        for (int j = 0; j < size; j++) {
            if (i==j) continue;
            row.push_back(matrix[i][j]);
        }
        newMatrix.push_back(row);
    }

    matrix = newMatrix;
}

void deleteRowMatrix(vector<vector<int>>& matrix, int row) {
    matrix.erase(matrix.begin() + row);
}



void fullCycle(int sizeOfMatrix) {
    vector<vector<int>> matrix(sizeOfMatrix, vector<int>(sizeOfMatrix));

    fillMatrix(matrix);
    showMatrix(matrix);

    deleteMainDiagonalMatrix(matrix, sizeOfMatrix);
    showMatrix(matrix);

    int x = 0, y = 0;
    findMaxValue(x, y, matrix);
    deleteRowMatrix(matrix, x);

    showMatrix(matrix);
}


int lab2_task4(int sizeOfMatrix) {
    srand(time(NULL));
    fullCycle(sizeOfMatrix);



    return 0;
}

