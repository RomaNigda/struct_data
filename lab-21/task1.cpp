#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Structure to describe a position
struct Position {
    string name; // Position name
    int A; // Coefficient A
    int B; // Coefficient B
    int count; // Number of employees
};

int lab21_task1() {
    // ===== Input data =====
    const double TOTAL_FUND = 380000.0; // Total monthly salary fund (UAH)

    // Vector of positions: { name, A, B, count }
    vector<Position> positions = {
        {"Orderly", 1, 1, 7},
        {"Nurse", 6, 5, 10},
        {"Doctor", 8, 5, 10},
        {"Head of Pharmacy", 9, 5, 1},
        {"Head of Dept.", 2, 1, 3},
        {"Chief Doctor", 12, 5, 1},
        {"Head of Economy", 13, 5, 1},
        {"Head of Hospital", 3, 1, 1},
    };

    // ===== Step 1: Calculate tariff coefficients K = A / B =====
    // and the total weighted coefficient for the entire staff
    // Total salary = S_orderly * sum(Ki * count_i)
    // => S_orderly = TOTAL_FUND / sum(Ki * count_i)

    double sum_K = 0.0;
    for (const auto &p: positions) {
        double K = static_cast<double>(p.A) / p.B;
        sum_K += K * p.count;
    }

    // ===== Step 2: Find the base salary (orderly) =====
    double salary_base = TOTAL_FUND / sum_K;

    // ===== Step 3: Print the results table =====
    cout << "\n====== LABORATORY WORK #21 ======\n";
    cout << "Topic: Implementation of Dynamic Programming Algorithms\n\n";

    cout << fixed << setprecision(2);

    // Table header
    cout << left
            << setw(22) << "Position"
            << setw(6) << "A"
            << setw(6) << "B"
            << setw(10) << "K=A/B"
            << setw(14) << "Salary"
            << setw(10) << "Count"
            << setw(18) << "Total Salary"
            << setw(16) << "Orderly Salary"
            << "\n";

    cout << string(102, '-') << "\n";

    double total_salary = 0.0;

    for (const auto &p: positions) {
        double K = static_cast<double>(p.A) / p.B;
        double salary = salary_base * K;
        double total = salary * p.count;
        total_salary += total;

        cout << left
                << setw(22) << p.name
                << setw(6) << p.A
                << setw(6) << p.B
                << setw(10) << K
                << setw(14) << salary
                << setw(10) << p.count
                << setw(18) << total
                << setw(16) << salary_base
                << "\n";
    }

    cout << string(102, '-') << "\n";
    cout << left
            << setw(64) << "Total"
            << setw(18) << total_salary
            << "\n\n";

    // ===== Summary =====
    cout << "Weighted sum of coefficients: " << sum_K << "\n";
    cout << "Orderly base salary:          " << salary_base << " UAH\n";
    cout << "Target fund:                  " << TOTAL_FUND << " UAH\n";
    cout << "Calculated fund:              " << total_salary << " UAH\n";
    cout << "Difference:                   " << abs(TOTAL_FUND - total_salary) << " UAH\n";

    return 0;
}
