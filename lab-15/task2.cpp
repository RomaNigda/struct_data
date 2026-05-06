#include<iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Nested structure for time (hours, minutes)
struct Time {
    int hours;
    int minutes;

    // Convert time to minutes
    int toMinutes() const {
        return hours * 60 + minutes;
    }

    // Print time in HH:MM format
    void print() const {
        cout << hours << ":" << (minutes < 10 ? "0" : "") << minutes;
    }
};

// Main structure for Train
struct Train {
    int number; // train number
    string destination; // destination station
    int distance; // distance in km
    Time departure; // departure time
    Time arrival; // arrival time
    int travelTime; // travel time in minutes

    // Calculate travel time (if not set manually)
    void calculateTravelTime() {
        travelTime = arrival.toMinutes() - departure.toMinutes();
        if (travelTime < 0) {
            // if train goes past midnight
            travelTime += 24 * 60;
        }
    }

    // Print train information
    void print() const {
        cout << "Train #" << number << " -> " << destination;
        cout << " | Departure: ";
        departure.print();
        cout << " | Arrival: ";
        arrival.print();
        cout << " | Travel time: " << travelTime << " min" << endl;
    }
};

// ==================== SECTION A ====================
// Find train with longest travel time (simple linear search)
int findMaxTravelTimeIndex(const vector<Train> &trains) {
    int maxIndex = 0;
    for (size_t i = 1; i < trains.size(); i++) {
        if (trains[i].travelTime > trains[maxIndex].travelTime) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// ==================== SECTION B ====================
// SELECTION SORT algorithm (sorting by travel time in descending order)
void selectionSortByTravelTime(vector<Train> &trains) {
    int n = trains.size();

    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i; // assume current index has maximum

        // Find the actual maximum in the remaining array
        for (int j = i + 1; j < n; j++) {
            if (trains[j].travelTime > trains[maxIdx].travelTime) {
                maxIdx = j;
            }
        }

        // Swap if a new maximum was found
        if (maxIdx != i) {
            swap(trains[i], trains[maxIdx]);
        }
    }
}

// ==================== MAIN FUNCTION ====================
int lab15_task2() {
    // Initialize train schedule
    vector<Train> trains = {
        {101, "Kyiv", 450, {8, 0}, {14, 30}, 0},
        {205, "Lviv", 320, {9, 45}, {15, 15}, 0},
        {312, "Odesa", 280, {10, 30}, {16, 45}, 0},
        {157, "Kharkiv", 520, {7, 15}, {15, 45}, 0},
        {423, "Dnipro", 210, {12, 0}, {16, 30}, 0},
        {389, "Zaporizhzhia", 380, {13, 20}, {21, 10}, 0},
        {256, "Vinnytsia", 150, {15, 0}, {18, 45}, 0},
    };

    // Calculate travel time for each train
    for (auto &train: trains) {
        train.calculateTravelTime();
    }

    cout << "================================================================" << endl;
    cout << "                     TRAIN SCHEDULE" << endl;
    cout << "================================================================" << endl;
    for (const auto &train: trains) {
        train.print();
    }

    // ========== PART A ==========
    // Find train with longest travel time (simple search)
    cout << "\n================================================================" << endl;
    cout << "PART A: Finding train with longest travel time" << endl;
    cout << "================================================================" << endl;

    int maxIndex = findMaxTravelTimeIndex(trains);
    cout << "Train with longest travel time:" << endl;
    cout << "   Train number: " << trains[maxIndex].number << endl;
    cout << "   Destination: " << trains[maxIndex].destination << endl;
    cout << "   Travel time: " << trains[maxIndex].travelTime << " minutes" << endl;

    // ========== PART B ==========
    // Using SELECTION SORT to find and sort by travel time
    cout << "\n================================================================" << endl;
    cout << "PART B: Sorting by travel time using SELECTION SORT" << endl;
    cout << "================================================================" << endl;

    // Create a copy to sort (so original data is preserved)
    vector<Train> sortedTrains = trains;

    // Apply selection sort
    selectionSortByTravelTime(sortedTrains);

    // Display result - first element has maximum travel time
    cout << "\nAfter Selection Sort (descending order):" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Train with MAXIMUM travel time:" << endl;
    cout << "   Train number: " << sortedTrains[0].number << endl;
    cout << "   Destination: " << sortedTrains[0].destination << endl;
    cout << "   Travel time: " << sortedTrains[0].travelTime << " minutes" << endl;

    cout << "\nAll trains sorted by travel time (descending):" << endl;
    cout << "------------------------------------------------" << endl;
    for (const auto &train: sortedTrains) {
        cout << "   Train #" << train.number << " -> " << train.destination;
        cout << " | Travel time: " << train.travelTime << " min" << endl;
    }

    // ========== VERIFICATION ==========
    cout << "\n================================================================" << endl;
    cout << "VERIFICATION: Both methods give the same result?" << endl;
    cout << "================================================================" << endl;

    if (trains[maxIndex].number == sortedTrains[0].number &&
        trains[maxIndex].destination == sortedTrains[0].destination) {
        cout << "YES! Both methods identified the same train." << endl;
    } else {
        cout << "ERROR: Methods gave different results!" << endl;
    }

    return 0;
}
