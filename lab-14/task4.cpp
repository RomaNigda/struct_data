#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

int lab14_task4() {
    multimap<int, string> mm;
    string text, word;
    getline(cin, text);
    stringstream ss(text);

    while (ss >> word) {
        mm.insert({word.length(), word});
    }

    int currentLen = -1;
    int count = 0;

    for (auto &p: mm) {
        if (p.first != currentLen) {
            if (currentLen != -1) {
                cout << "(sum: " << count << ")\n";
            }
            currentLen = p.first;
            count = 0;
            cout << "\nLenght " << currentLen << ": ";
        }
        cout << p.second << " ";
        count++;
    }
    if (currentLen != -1) {
        cout << "(sum: " << count << ")\n";
    }

    return 0;
}
