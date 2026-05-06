#include <iostream>
#include <map>
#include <string>
using namespace std;

int lab13_task2() {
    map<string, string> dir;
    int cmd;
    string name, tel;
    while (true) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> name >> tel;
            dir[name] = tel;
        } else if (cmd == 2) {
            cin >> name;
            cout << dir[name] << endl;
        } else if (cmd == 3) {
            cin >> name;
            dir.erase(name);
        } else break;
    }
    return 0;
}
