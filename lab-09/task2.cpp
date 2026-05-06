#include <iostream>
#include <fstream>
#include <string>
#include <limits> // Додано для numeric_limits

using namespace std;

struct CompNode {
    int code;
    string name;
    float price;
    CompNode *left;
    CompNode *right;
} *root;


void addNode(CompNode *&r, int c, string n, float p) {
    if (r == 0) {
        CompNode *newNode = new CompNode;
        newNode->code = c;
        newNode->name = n;
        newNode->price = p;
        newNode->left = 0;
        newNode->right = 0;
        r = newNode;
        return;
    }
    if (c < r->code) {
        addNode(r->left, c, n, p);
    } else if (c > r->code) {
        addNode(r->right, c, n, p);
    }
}

void calcAvg(CompNode *r, float &sum, int &count) {
    if (r == 0) return;
    sum += r->price;
    count++;
    calcAvg(r->left, sum, count);
    calcAvg(r->right, sum, count);
}

void countLevels(CompNode *r, int level, int levels[]) {
    if (r == 0) return;
    levels[level]++;
    countLevels(r->left, level + 1, levels);
    countLevels(r->right, level + 1, levels);
}

CompNode *findNode(CompNode *r, int c) {
    if (r == 0) return 0;
    if (r->code == c) return r;
    if (c < r->code) return findNode(r->left, c);
    return findNode(r->right, c);
}

void deleteTree(CompNode *&r) {
    if (r != 0) {
        deleteTree(r->left);
        deleteTree(r->right);
        delete r;
        r = 0;
    }
}

static void showInorder(CompNode *root) {
    if (!root) return;
    showInorder(root->left);
    cout << root->code << " " << root->name << " " << root->price << endl;
    showInorder(root->right);
}


int lab9_task2_1() {
    root = 0;

    string filename = "../lab-09/data.txt";
    ifstream file(filename);

    while (!file.is_open()) {
        cout << "Failure: file " << filename << " not find!\n";
        return -1;
    }

    int code;
    string name;
    float price;
    while (file >> code >> name >> price) {
        addNode(root, code, name, price);
    }
    file.close();

    showInorder(root);

    float sum = 0;
    int count = 0;
    calcAvg(root, sum, count);

    if (count > 0) {
        cout << "Average price: " << sum / count << '\n';
    }

    int levels[20];
    for (int i = 0; i < 20; i++) levels[i] = 0;
    countLevels(root, 0, levels);

    cout << "\nNodes per level:\n";
    for (int i = 0; i < 20; i++) {
        if (levels[i] > 0) {
            cout << "Level " << i << ": " << levels[i] << '\n';
        }
    }

    int searchCode;
    cout << "\nEnter element code to delete next elements: ";

    while (!(cin >> searchCode)) {
        cout << "Failure: entered wrong data!\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter code again: ";
    }

    CompNode *target = findNode(root, searchCode);
    if (target != 0) {
        deleteTree(target->left);
        deleteTree(target->right);
        cout << "Elements deleted.\n";
    } else {
        cout << "Technic not find.\n";
    }

    showInorder(root);

    deleteTree(root);
    return 0;
}
