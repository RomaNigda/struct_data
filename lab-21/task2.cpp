#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <climits>

using namespace std;

int lab21_task2() {
    vector<int> supply = {1500, 1900, 1600};

    vector<int> demand = {1800, 1200, 2000};

    vector<vector<int> > cost = {
        {8, 7, 2},
        {1, 4, 3},
        {5, 1, 6}
    };

    int numWarehouses = supply.size();
    int numStores = demand.size();

    vector<vector<int> > alloc(numWarehouses, vector<int>(numStores, 0));

    vector<int> sup = supply;
    vector<int> dem = demand;

    {
        vector<int> s = supply;
        vector<int> d = demand;
        vector<vector<int> > nw(numWarehouses, vector<int>(numStores, 0));

        int i = 0, j = 0;
        while (i < numWarehouses && j < numStores) {
            int qty = min(s[i], d[j]);
            nw[i][j] = qty;
            s[i] -= qty;
            d[j] -= qty;
            if (s[i] == 0) i++;
            else j++;
        }

        int totalCost = 0;
        for (int r = 0; r < numWarehouses; r++)
            for (int c = 0; c < numStores; c++)
                totalCost += nw[r][c] * cost[r][c];

        cout << "\n=== North-West Corner Method ===\n\n";
        cout << left << setw(6) << " ";
        for (int c = 0; c < numStores; c++)
            cout << "| " << setw(5) << ("M" + to_string(c + 1));
        cout << "|\n";

        cout << string(6 + numStores * 8, '-') << "\n";

        for (int r = 0; r < numWarehouses; r++) {
            cout << setw(6) << ("S" + to_string(r + 1));
            for (int c = 0; c < numStores; c++)
                cout << "| " << setw(5) << nw[r][c];
            cout << "|\n";
        }

        cout << "\nMinimum total delivery cost (NW): " << totalCost << " units.\n";
    }

    {
        vector<int> s = supply;
        vector<int> d = demand;
        vector<vector<int> > mc(numWarehouses, vector<int>(numStores, 0));

        while (true) {
            int bestCost = INT_MAX, bi = -1, bj = -1;
            for (int i = 0; i < numWarehouses; i++) {
                if (s[i] == 0) continue;
                for (int j = 0; j < numStores; j++) {
                    if (d[j] == 0) continue;
                    if (cost[i][j] < bestCost) {
                        bestCost = cost[i][j];
                        bi = i;
                        bj = j;
                    }
                }
            }
            if (bi == -1) break; // done

            int qty = min(s[bi], d[bj]);
            mc[bi][bj] = qty;
            s[bi] -= qty;
            d[bj] -= qty;
        }

        int totalCost = 0;
        for (int r = 0; r < numWarehouses; r++)
            for (int c = 0; c < numStores; c++)
                totalCost += mc[r][c] * cost[r][c];

        cout << "\n=== Minimum Cost Method ===\n\n";
        cout << left << setw(6) << " ";
        for (int c = 0; c < numStores; c++)
            cout << "| " << setw(5) << ("M" + to_string(c + 1));
        cout << "|\n";

        cout << string(6 + numStores * 8, '-') << "\n";

        for (int r = 0; r < numWarehouses; r++) {
            cout << setw(6) << ("S" + to_string(r + 1));
            for (int c = 0; c < numStores; c++)
                cout << "| " << setw(5) << mc[r][c];
            cout << "|\n";
        }

        cout << "\nMinimum total delivery cost (MC): " << totalCost << " units.\n\n";
    }

    return 0;
}
