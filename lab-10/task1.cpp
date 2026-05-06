#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

static void showGraph(const vector<vector<int> > &matrix) {
    for (const auto &row: matrix) {
        for (const auto col: row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

bool isGraphFull(vector<vector<int> > matrix) {
    int counter = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (i == j) {
                continue;
            }
            if (matrix[i][j] != 0) {
                counter++;
            }
        }
    }
    int edges = (matrix.size() * (matrix.size() - 1)) / 2;
    return edges == counter ? true : false;
}


static void createListOf(vector<vector<int> > &matrix, vector<vector<int> > &list) {
    for (int i = 0; i < matrix.size(); i++) {
        list.push_back({});
        cout << "Vevel " << i + 1 << ": ";
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != 0) {
                list[i].push_back(j + 1);
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
}

float countAverageDistance(vector<vector<int> > &matrix) {
    float sum = 0;
    int counter = 0;
    for (const auto &row: matrix) {
        for (const auto col: row) {
            if (col != 0) {
                sum += col;
                counter++;
            }
        }
    }
    return (sum / counter);
}

void showNearestCityToIsolated(vector<vector<int> > &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == accumulate(matrix[i].begin(), matrix[i].end(), 0)) {
                cout << "City " << i + 1 << " is isolated" << endl;
                cout << "Nearest city is " << j + 1 << " in " << matrix[i][j] << "km." << endl;
            }
        }
    }
}

static bool containsValue(const vector<int> &list, const int value) {
    for (const int i: list) {
        if (i == value) {
            return true;
        }
    }
    return false;
}

static void showVector(const vector<int> v) {
    for (auto i: v) {
        cout << i << " ";
    }
}


static void testFunction(const vector<vector<int> > &matrix,
                         int currentVevel,
                         vector<int> visitedVevel,
                         int needEdge,
                         int currentSum,
                         int &maxSum,
                         vector<int> &lastVariant) {
    visitedVevel.push_back(currentVevel);
    if (visitedVevel.size() - 1 == needEdge) {
        maxSum = currentSum;
        lastVariant = visitedVevel;
    }


    for (int j = 0; j < matrix.size(); j++) {
        if (!containsValue(visitedVevel, j) && matrix[currentVevel][j] != 0) {
            currentSum += matrix[currentVevel][j];
            cout << j << " " << currentSum << endl;


            testFunction(
                matrix,
                j,
                visitedVevel,
                needEdge,
                currentSum,
                maxSum,
                lastVariant);
            cout << "reverse" << endl;
            currentSum -= matrix[currentVevel][j];
        }
    }
}


static void findLongestRout(const vector<vector<int> > &matrix, int edges) {
    if (edges > matrix.size() - 1) {
        cout << "Incorrect number of edges" << endl;
        return;
    }
    vector<int> lastVariant = {};
    int maxSum = 0;
    vector<int> v = {};


    for (int i = 0; i < matrix.size(); i++) {
        cout << "next vevel: " << i << endl;
        testFunction(
            matrix,
            i,
            v,
            edges,
            0,
            maxSum,
            lastVariant);
    }

    cout << "\n\n============================\n\n";
    cout << "Max sum = " << maxSum << endl;
    cout << "Vector: ";
    showVector(lastVariant);
    cout << endl;
}

int lab10_task1() {
    vector<vector<int> > matrix = {
        {0, 0, 2, 0, 8, 0,},
        {0, 0, 6, 4, 0, 0,},
        {2, 6, 0, 0, 0, 9,},
        {0, 4, 0, 0, 4, 0,},
        {8, 0, 0, 4, 0, 0,},
        {0, 0, 9, 0, 0, 0,},
    };
    vector<vector<int> > list = {};
    showGraph(matrix);
    if (isGraphFull(matrix)) {
        cout << "Graph is Full" << endl;
    } else {
        cout << "Graph is not Full" << endl;
    }

    cout << "=================" << endl;
    createListOf(matrix, list);

    cout << "=================" << endl;
    cout << "Average distance is " << countAverageDistance(matrix) << endl;

    cout << "=================" << endl;
    showNearestCityToIsolated(matrix);


    cout << "\n\n================" << endl;

    findLongestRout(matrix, 2);

    return 0;
}
