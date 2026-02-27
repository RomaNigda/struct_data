#include "task1.h"

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
constexpr int countOfColumn = 4;


void showArray(float sp[], int len){
    for(int i = 0; i < len; i++){
        cout << sp[i] << " ";
    }
}

void createArray(float arr[], int len) {
    for(int i = 0; i < len; i++) {
        arr[i] = (rand() % 600 - 150) / 100.0;
    }
}

bool correctLenOfArray(int len){
    if (len % countOfColumn == 0){
        return true;
    }
    return false;
}

void createMatrix(float sp[], int len, float result[][countOfColumn]){
    if (len %countOfColumn != 0) return;
    int n = len / countOfColumn;
    for(int i = 0, k = 0; i < n; i++){
        for(int j = 0; j < countOfColumn; j++){
            result[i][j] = sp[k++];
        }
    }
}

void showMatrix(float mat[][countOfColumn], int n){
    for(int i = 0; i < n/countOfColumn; i++){
        for(int j = 0; j < countOfColumn; j++){
            cout << mat[i][j] << "\t";
        }
        cout << "\n";
    }
}

void sortMatrix(float result[][countOfColumn], int len) {
    for (int k = 0; k < len; k+=2) {
        for (int i = 0; i < countOfColumn; i++) {
            for (int j = i; j < countOfColumn; j++) {
                if (result[k][i] > result[k][j]) {
                    swap(result[k][i], result[k][j]);
                }
            }
        }
    }
    for (int k = 1; k < len; k+=2) {
        for (int i = 0; i < countOfColumn; i++) {
            for (int j = i; j < countOfColumn; j++) {
                if (result[k][i] < result[k][j]) {
                    swap(result[k][i], result[k][j]);
                }
            }
        }
    }
}

int findMaxValue(float arr[], int len) {
    float max = arr[0];
    for (int i = 1; i < len; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

int fullCycle(int lenOfArray, int count) {
    ofstream exitFile("result.txt", ios::app);
    float arr[lenOfArray];
    float matrix[lenOfArray][countOfColumn];

    // cout << "Enter length of array: ";
    // cin >> lenOfArray;

    if (!correctLenOfArray(lenOfArray)) {
        cout << "Invalid length of array!\n";
        return 1;
    }

    clock_t start = clock();

    createArray(arr, lenOfArray);
    showArray(arr, lenOfArray);

    cout << "\n\n";

    createMatrix(arr, lenOfArray, matrix);
    showMatrix(matrix, lenOfArray);

    cout << "\n\n";
    sortMatrix(matrix, lenOfArray);
    showMatrix(matrix, lenOfArray);
    clock_t end = clock();

    double resultTime = (double)(end - start) / CLOCKS_PER_SEC;

    long spaceNeeded = sizeof(arr[0]) * lenOfArray * 2;

    exitFile << "|-----|------|-----------------|------------------|\n";
    exitFile << "| "
        << count << " |  "
        << lenOfArray << "  |         "
        << resultTime << "     |    "
        << spaceNeeded << "     |\n";
    // exitFile << "|-----|------|-----------------|------------------|\n";
    exitFile.close();
    return 0;
}



int task1_lab1(){
    ofstream exitFile("result.txt", ios::trunc);
    exitFile.close();
    // int lenOfArray;
    // float arr[lenOfArray];
    // float matrix[lenOfArray][countOfColumn];

    int valueOfIterration[]={20, 100, 1000};

    for (int i = 0; i < sizeof(valueOfIterration)/sizeof(valueOfIterration[0]); i++) {
        fullCycle(valueOfIterration[i], i+1);
    }



    // // cout << "Enter length of array: ";
    // // cin >> lenOfArray;
    //
    // if (!correctLenOfArray(lenOfArray)) {
    //     cout << "Invalid length of array!\n";
    //     return 1;
    // }
    //
    // createArray(arr, lenOfArray);
    // showArray(arr, lenOfArray);
    //
    // cout << "\n\n";
    //
    // createMatrix(arr, lenOfArray, matrix);
    // showMatrix(matrix, lenOfArray);
    //
    // cout << "\n\n";
    // sortMatrix(matrix, lenOfArray);
    // showMatrix(matrix, lenOfArray);


















    return 0;
}



