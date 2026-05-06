#include <iostream>
#include <vector>
using namespace std;

namespace lab16_task2_name {
    struct Eat {
        string name;
        int kbgu[3];
        int calories;

        void calculateCalories() {
            calories = kbgu[0] * 4 + kbgu[1] * 9 + kbgu[2] * 4;
        }
    };


    vector<int> countProductWithMaxCalories(vector<Eat> eats) {
        int maxCalories = 0;
        vector<int> indexes = {};

        for (auto &eat: eats) {
            maxCalories = max(maxCalories, eat.calories);
        }

        for (int i = 0; i < eats.size(); i++) {
            if (eats[i].calories == maxCalories) {
                indexes.push_back(i);
            }
        }
        return indexes;
    }


    bool productFromRange(vector<Eat> eats, int min, int max) {
        bool flag = false;
        for (auto &eat: eats) {
            if (eat.calories <= max && eat.calories >= min) {
                cout << eat.name << " : " << eat.calories << endl;
                flag = true;
            }
        }
        return flag;
    }

    void showVector(vector<Eat> eats) {
        for (auto &eat: eats) {
            cout << eat.name << " | " << eat.calories << endl;
        }
    }

    int lab16_task2() {
        vector<Eat> eats = {
            {"first", {4, 5, 6}, 0},
            {"second", {3, 9, 4}, 0}
        };

        for (auto &eat: eats) {
            eat.calculateCalories();
        }
        showVector(eats);


        vector<int> indexes = countProductWithMaxCalories(eats);
        cout << "Product with max calories: " << indexes.size() << endl;
        for (auto i: indexes) {
            cout << i + 1 << " " << eats[i].name << " | ";
        }
        cout << endl;
        if (!productFromRange(eats, 10, 90)) {
            cout << "product from that range not finded" << endl;
        }

        return 0;
    }
}

int lab16_task2() {
    lab16_task2_name::lab16_task2();
    return 0;
}
