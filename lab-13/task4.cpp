#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

int lab13_task4() {
    multimap<char, string> mm;
    string text, word;
    getline(cin, text);
    stringstream ss(text);
    while (ss >> word) {
        mm.insert({word[0], word});
    }
    for (auto &p: mm) {
        cout << p.first << ": " << p.second << endl;
    }
    return 0;
}
