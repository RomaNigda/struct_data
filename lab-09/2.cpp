// #include <iostream>
// #include <fstream>
// #include <string>
// #include <limits> // Додано для numeric_limits
// #include <queue>
//
// using namespace std;
//
// struct Node {
//     int code;
//     string name;
//     float price;
//     Node *left;
//     Node *right;
// } *root;
//
// void addNode(Node *&r, int c, string n, float p) {
//     if (r == 0) {
//         Node *newNode = new Node;
//         newNode->code = c;
//         newNode->name = n;
//         newNode->price = p;
//         newNode->left = 0;
//         newNode->right = 0;
//         r = newNode;
//         return;
//     }
//     if (c < r->code) {
//         addNode(r->left, c, n, p);
//     } else if (c > r->code) {
//         addNode(r->right, c, n, p);
//     }
// }
//
// void calculateAvg(Node *r, float &sum, int &count) {
//     if (r == 0) return;
//     sum += r->price;
//     count++;
//     calculateAvg(r->left, sum, count);
//     calculateAvg(r->right, sum, count);
// }
//
// void countLevels(Node *r, int level, int levels[]) {
//     if (r == 0) return;
//     levels[level]++;
//     countLevels(r->left, level + 1, levels);
//     countLevels(r->right, level + 1, levels);
// }
//
// Node *findNode(Node *r, int c) {
//     if (r == 0) return 0;
//     if (r->code == c) return r;
//     if (c < r->code) return findNode(r->left, c);
//     return findNode(r->right, c);
// }
//
// void deleteTree(Node *&r) {
//     if (r != 0) {
//         deleteTree(r->left);
//         deleteTree(r->right);
//         delete r;
//         r = 0;
//     }
// }
//
// static void calculateNodesPerLevel(Node *root) {
//     if (!root) return;
//
//     queue<Node *> q;
//     q.push(root);
//
//     int level = 0;
//
//     while (!q.empty()) {
//         int size = q.size();
//         cout << "Level " << level << ": " << size << " nodes\n";
//
//         for (int i = 0; i < size; i++) {
//             Node *current = q.front();
//             q.pop();
//
//             if (current->left) q.push(current->left);
//             if (current->right) q.push(current->right);
//         }
//
//         level++;
//     }
// }
//
// int lab9_task3() {
//     root = 0;
//
//     string filename = "../lab-09/data.txt";
//     ifstream file(filename);
//
//     if (!file.is_open()) {
//         cout << "Failure: file " << filename << " not find!\n";
//         return -1;
//     }
//
//     int code;
//     string name;
//     float price;
//     while (file >> code >> name >> price) {
//         addNode(root, code, name, price);
//     }
//     file.close();
//
//     float sum = 0;
//     int count = 0;
//     calculateAvg(root, sum, count);
//
//     if (count > 0) {
//         cout << "Average price: " << sum / count << '\n';
//     }
//
//     // int levels[20];
//     // for (int & level : levels) level = 0;
//     // countLevels(root, 0, levels);
//     //
//     // cout << "\nKilkist vuzliv na rivniakh:\n";
//     // for (int i = 0; i < 20; i++) {
//     //     if (levels[i] > 0) {
//     //         cout << "Riven " << i << ": " << levels[i] << '\n';
//     //     }
//     // }
//
//     cout << "\nNodes per level:\n";
//     calculateNodesPerLevel(root);
//
//     int searchCode;
//     cout << "\nEnter element code to delete next elements: ";
//
//     while (!(cin >> searchCode)) {
//         cout << "Failure: entered wrong data!\n";
//
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         cout << "Enter code again: ";
//     }
//
//     Node *target = findNode(root, searchCode);
//     if (target != 0) {
//         deleteTree(target->left);
//         deleteTree(target->right);
//         cout << "Elements deleted.\n";
//     } else {
//         cout << "Technic not find.\n";
//     }
//
//     deleteTree(root);
//     return 0;
// }
