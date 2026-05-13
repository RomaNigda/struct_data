#include <iostream>
#include <algorithm>
using namespace std;

int lab20_task1() {
    double volumePerKg[] = {1.0, 1.5, 2.0, 1.0};
    double caloriesPerKg[] = {1500, 5000, 5000, 4000};
    string productName[] = {"Meat", "Flour", "Milk", "Sugar"};

    double maxVolume = 45.0;
    double maxWeight = 35.0;


    double baseAmountPerUnit[] = {16.0, 8.0, 8.0, 1.0};


    double baseWeight = 0, baseVolume = 0;
    for (int i = 0; i < 4; i++) {
        baseWeight += baseAmountPerUnit[i];
        baseVolume += baseAmountPerUnit[i] * volumePerKg[i];
    }

    double scaleFactor = min(maxWeight / baseWeight, maxVolume / baseVolume);


    double amountKg[4];
    double totalWeight = 0, totalVolume = 0, totalCalories = 0;
    for (int i = 0; i < 4; i++) {
        amountKg[i] = baseAmountPerUnit[i] * scaleFactor;
        totalWeight += amountKg[i];
        totalVolume += amountKg[i] * volumePerKg[i];
        totalCalories += amountKg[i] * caloriesPerKg[i];
    }


    cout << "=== Result ===" << endl;
    for (int i = 0; i < 4; i++)
        cout << productName[i] << ": " << amountKg[i] << " kg" << endl;

    cout << "\nTotal weight:    " << totalWeight << " kg  (max " << maxWeight << ")" << endl;
    cout << "Total volume:    " << totalVolume << " dm3 (max " << maxVolume << ")" << endl;
    cout << "Total calories:  " << totalCalories << " kcal" << endl;


    double meatKg = amountKg[0];
    double flourKg = amountKg[1];
    double milkKg = amountKg[2];
    double sugarKg = amountKg[3];

    cout << "\n=======================" << endl;
    cout << "Meat  >= 2*Flour: " << meatKg << " >= " << 2 * flourKg << " -> " << (meatKg >= 2 * flourKg - 1e-9
            ? "OK"
            : "VIOLATED") << endl;
    cout << "Flour >= Milk:    " << flourKg << " >= " << milkKg << " -> " << (flourKg >= milkKg - 1e-9
                                                                                  ? "OK"
                                                                                  : "VIOLATED") << endl;
    cout << "Milk  >= 8*Sugar: " << milkKg << " >= " << 8 * sugarKg << " -> " << (milkKg >= 8 * sugarKg - 1e-9
            ? "OK"
            : "VIOLATED") << endl;

    return 0;
}
