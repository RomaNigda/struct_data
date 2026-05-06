#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

void gnomeSort(vector<int> &arr) {
    int i = 0;
    int n = arr.size();
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) {
            i++;
        } else {
            swap(arr[i], arr[i - 1]);
            i--;
        }
    }
}


long long measureTime(void (*sortFunc)(vector<int> &), vector<int> data) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}


int lab15_task1() {
    srand(time(nullptr));

    vector<int> sizes = {1000, 10000, 100000};

    cout << "\n";
    cout << "================================================================================\n";
    cout << "   ПОРІВНЯЛЬНИЙ АНАЛІЗ ЧАСУ СОРТУВАННЯ (час у мілісекундах)\n";
    cout << "================================================================================\n";
    cout << left << setw(5) << "№"
            << setw(25) << "Алгоритм"
            << right << setw(15) << "n = 1000"
            << setw(15) << "n = 10000"
            << setw(15) << "n = 100000" << "\n";
    cout << "--------------------------------------------------------------------------------\n";

    for (int n: sizes) {
        vector<int> original(n);
        for (int i = 0; i < n; i++) {
            original[i] = rand() % 100000;
        }

        long long times[4];

        times[0] = measureTime(bubbleSort, original);

        times[1] = measureTime(insertionSort, original);

        times[2] = measureTime(selectionSort, original);

        times[3] = measureTime(gnomeSort, original);

        static bool headerPrinted = false;
        if (!headerPrinted) {
            cout << left << setw(5) << "1" << setw(25) << "Сортування бульбашкою"
                    << right << setw(15) << times[0] << setw(15) << "" << setw(15) << "" << "\n";
            cout << left << setw(5) << "2" << setw(25) << "Сортування вставками"
                    << right << setw(15) << times[1] << setw(15) << "" << setw(15) << "" << "\n";
            cout << left << setw(5) << "3" << setw(25) << "Сортування вибором"
                    << right << setw(15) << times[2] << setw(15) << "" << setw(15) << "" << "\n";
            cout << left << setw(5) << "4" << setw(25) << "Алгоритм гнома"
                    << right << setw(15) << times[3] << setw(15) << "" << setw(15) << "" << "\n";
            cout << "--------------------------------------------------------------------------------\n";
            headerPrinted = true;
        }
    }

    return 0;
}
