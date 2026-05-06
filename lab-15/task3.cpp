#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct TV {
    string brand; // manufacturer
    int screenSize; // screen size in inches (32, 45, 60)
    int price; // price in hryvnias

    void print() const {
        cout << brand << " | " << screenSize << "\" | " << price << " UAH" << endl;
    }
};

void gnomeSortByPrice(vector<TV> &tvs, int start, int end) {
    int i = start;
    while (i < end) {
        if (i == start || tvs[i].price <= tvs[i - 1].price) {
            i++;
        } else {
            swap(tvs[i], tvs[i - 1]);
            i--;
        }
    }
}

void insertionSortWithGnome(vector<TV> &tvs) {
    int n = tvs.size();

    for (int i = 1; i < n; i++) {
        TV key = tvs[i];
        int j = i - 1;

        while (j >= 0 && tvs[j].screenSize > key.screenSize) {
            tvs[j + 1] = tvs[j];
            j--;
        }
        tvs[j + 1] = key;
    }

    int start = 0;
    for (int i = 1; i <= n; i++) {
        if (i == n || tvs[i].screenSize != tvs[start].screenSize) {
            gnomeSortByPrice(tvs, start, i);
            start = i;
        }
    }
}

void insertionSortCombined(vector<TV> &tvs) {
    int n = tvs.size();

    for (int i = 1; i < n; i++) {
        TV key = tvs[i];
        int j = i - 1;

        while (j >= 0 && (tvs[j].screenSize > key.screenSize ||
                          (tvs[j].screenSize == key.screenSize && tvs[j].price < key.price))) {
            tvs[j + 1] = tvs[j];
            j--;
        }
        tvs[j + 1] = key;
    }
}

void displayTVs(const vector<TV> &tvs, const string &title) {
    cout << "\n" << title << endl;
    cout << "----------------------------------------" << endl;
    for (const auto &tv: tvs) {
        tv.print();
    }
}

int lab15_task3() {
    // Sample data
    vector<TV> televisions = {
        {"Samsung", 45, 25000},
        {"LG", 32, 15000},
        {"Sony", 60, 55000},
        {"Panasonic", 45, 22000},
        {"Philips", 32, 12000},
        {"Hisense", 60, 45000},
        {"Samsung", 60, 60000},
        {"LG", 45, 28000},
        {"Xiaomi", 32, 8000},
        {"Toshiba", 45, 20000},
    };

    displayTVs(televisions, "ORIGINAL DATA:");

    vector<TV> sortedTVs = televisions;

    insertionSortWithGnome(sortedTVs);

    displayTVs(sortedTVs, "SORTED DATA (by Screen Size ↑, then by Price ↓ within each size):");

    cout << "\n========================================" << endl;
    cout << "DETAILED RESULT BY GROUPS:" << endl;
    cout << "========================================" << endl;

    int currentSize = -1;
    for (const auto &tv: sortedTVs) {
        if (tv.screenSize != currentSize) {
            currentSize = tv.screenSize;
            cout << "\n--- " << currentSize << " inches TVs (sorted by price DESC) ---" << endl;
        }
        cout << "   " << tv.brand << " - " << tv.price << " UAH" << endl;
    }


    return 0;
}
