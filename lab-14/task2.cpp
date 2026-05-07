#include <iostream>
#include <map>
#include <string>
using namespace std;

int lab14_task2() {
    map<string, int> stock;
    int cmd;
    string name;
    int qty;

    while (true) {
        cout << "\n1-add 2-correct 3-delete 4-find 5-show all 0-exit\n";
        cin >> cmd;

        if (cmd == 0) break;

        if (cmd == 1) {
            cin >> name >> qty;
            stock[name] = qty;
        } else if (cmd == 2) {
            cin >> name >> qty;
            if (stock.find(name) != stock.end()) {
                stock[name] = qty;
            } else {
                cout << "Not find\n";
            }
        } else if (cmd == 3) {
            cin >> name;
            stock.erase(name);
        } else if (cmd == 4) {
            cin >> name;
            if (stock.find(name) != stock.end()) {
                cout << name << ": " << stock[name] << endl;
            } else {
                cout << "not find\n";
            }
        } else if (cmd == 5) {
            for (auto &p: stock) {
                cout << p.first << ": " << p.second << endl;
            }
        }
    }
    return 0;
}
