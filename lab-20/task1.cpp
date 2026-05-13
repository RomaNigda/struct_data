#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

int lab20_task1() {
    // Product characteristics
    // Indices: 0=meat, 1=flour, 2=milk, 3=sugar
    double volumePerKg[] = {1.0, 1.5, 2.0, 1.0}; // volume (dm³/kg)
    double caloriesPerKg[] = {1500, 5000, 5000, 4000}; // calories (kcal/kg)
    string productName[] = {"Meat", "Flour", "Milk", "Sugar"};

    double maxVolume = 45.0; // dm³
    double maxWeight = 35.0; // kg

    // -------------------------------------------------------
    // Doctor's constraints:
    //   meat  >= 2 * flour
    //   flour >= milk
    //   milk  >= 8 * sugar
    //
    // Greedy strategy:
    //   Express all products through sugar = t (use equality in constraints
    //   to avoid wasting space/weight on less caloric products):
    //     milk = 8t,  flour = 8t,  meat = 16t
    //
    //   Base package (t = 1 kg of sugar):
    //     meat=16, flour=8, milk=8, sugar=1  -> 33 kg, 52 dm³
    //
    //   Scale t to fit within maxWeight and maxVolume.
    // -------------------------------------------------------

    double baseAmountPerUnit[] = {16.0, 8.0, 8.0, 1.0}; // base package at t=1

    // Calculate total weight and volume of the base package
    double baseWeight = 0, baseVolume = 0;
    for (int i = 0; i < 4; i++) {
        baseWeight += baseAmountPerUnit[i];
        baseVolume += baseAmountPerUnit[i] * volumePerKg[i];
    }

    // Find the maximum scale factor t within both constraints
    double scaleFactor = min(maxWeight / baseWeight, maxVolume / baseVolume);

    // Calculate the actual amount of each product
    double amountKg[4];
    double totalWeight = 0, totalVolume = 0, totalCalories = 0;
    for (int i = 0; i < 4; i++) {
        amountKg[i] = baseAmountPerUnit[i] * scaleFactor;
        totalWeight += amountKg[i];
        totalVolume += amountKg[i] * volumePerKg[i];
        totalCalories += amountKg[i] * caloriesPerKg[i];
    }

    // Print results
    cout << "=== Result ===" << endl;
    for (int i = 0; i < 4; i++)
        cout << productName[i] << ": " << amountKg[i] << " kg" << endl;

    cout << "\nTotal weight:    " << totalWeight << " kg  (max " << maxWeight << ")" << endl;
    cout << "Total volume:    " << totalVolume << " dm3 (max " << maxVolume << ")" << endl;
    cout << "Total calories:  " << totalCalories << " kcal" << endl;

    // Verify doctor's constraints
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
