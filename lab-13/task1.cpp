#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

int lab13_task1() {
    map<string, int> m;
    string text, word;
    getline(cin, text);
    stringstream ss(text);
    while (ss >> word) {
        m[word]++;
    }
    for (auto &p: m) {
        cout << p.first << ": " << p.second << endl;
    }
    return 0;
}
