#include <iostream>
#include <map>
#include <string>
using namespace std;

int lab14_task1() {
    map<char, int> m;
    string s;
    getline(cin, s);

    for (char c: s) m[c]++;

    char mostFreq;
    int maxCount = 0;

    for (auto &p: m) {
        cout << "'" << p.first << "': " << p.second << endl;
        if (p.second > maxCount) {
            maxCount = p.second;
            mostFreq = p.first;
        }
    }

    cout << "Найчастіше: '" << mostFreq << "' (" << maxCount << " разів)" << endl;
    return 0;
}
