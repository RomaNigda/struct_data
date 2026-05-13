#include <iostream>
#include <algorithm>
#include <vector>
#include <windows.h>
using namespace std;

struct Activity {
    int index;
    int startTime;
    int endTime;
};

int lab20_task2() {
    // Mock data: 9 activities (index, startTime, endTime)
    vector<Activity> activities = {
        {1, 1, 4},
        {2, 3, 5},
        {3, 0, 6},
        {4, 5, 7},
        {5, 3, 9},
        {6, 6, 10},
        {7, 8, 11},
        {8, 2, 13},
        {9, 4, 5}
    };
    int totalCount = activities.size();

    cout << "=== All Activities ===" << endl;
    cout << "Index | Start | End" << endl;
    for (int i = 0; i < totalCount; i++)
        cout << "  " << activities[i].index << "   |   " << activities[i].startTime << "   |   " << activities[i].
                endTime << endl;

    // Greedy algorithm:
    // 1) Sort activities by end time
    sort(activities.begin(), activities.end(), [](const Activity &a, const Activity &b) {
        return a.endTime < b.endTime;
    });

    // 2) Greedy selection: take activity if its startTime >= endTime of last selected
    vector<int> selectedIndexes;
    int lastEndTime = -1;

    for (int i = 0; i < totalCount; i++) {
        if (activities[i].startTime >= lastEndTime) {
            selectedIndexes.push_back(i);
            lastEndTime = activities[i].endTime;
        }
    }

    // Output result
    cout << "\n=== Result ===" << endl;
    cout << "Maximum number of activities: " << selectedIndexes.size() << endl;
    cout << "\nSelected activities:" << endl;
    cout << "Index | Start | End" << endl;
    for (int idx: selectedIndexes) {
        cout << "  " << activities[idx].index << "   |   " << activities[idx].startTime << "   |   " << activities[idx].
                endTime << endl;
    }

    return 0;
}
