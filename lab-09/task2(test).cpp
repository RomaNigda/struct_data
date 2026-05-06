#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

struct Node {
    int code;
    string name;
    double price;
    Node *left;
    Node *right;

    Node(int c, string n, double p) {
        code = c;
        name = n;
        price = p;
        left = right = nullptr;
    }
};

static Node *insertInTree(Node *root, int code, string name, double price) {
    if (!root) return new Node(code, name, price);

    if (code < root->code)
        root->left = insertInTree(root->left, code, name, price);
    else if (code > root->code)
        root->right = insertInTree(root->right, code, name, price);

    return root;
}

static void showInorder(Node *root) {
    if (!root) return;
    showInorder(root->left);
    cout << root->code << " " << root->name << " " << root->price << endl;
    showInorder(root->right);
}

void calculateSumAndCount(Node *root, double &sum, int &count) {
    if (!root) return;
    sum += root->price;
    count++;
    calculateSumAndCount(root->left, sum, count);
    calculateSumAndCount(root->right, sum, count);
}

static void calculateNodesPerLevel(Node *root) {
    if (!root) return;

    queue<Node *> q;
    q.push(root);

    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        cout << "Level " << level << ": " << size << " nodes\n";

        for (int i = 0; i < size; i++) {
            Node *current = q.front();
            q.pop();

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        level++;
    }
}

static Node *searchNode(Node *root, int key) {
    if (root == nullptr) return nullptr;
    if (root->code == key) {
        cout << "find key = " << key << endl;
        return root;
    }

    if (key < root->code)
        return searchNode(root->left, key);

    return searchNode(root->right, key);
}


static void deleteTree(Node *&root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

static Node *findNode(Node *node, int value) {
    if (node == nullptr) return nullptr;
    if (node->code == value) return node;
    if (value < node->code) return findNode(node->left, value);
    return findNode(node->right, value);
}


void removeSubtree(Node *root, int key) {
    Node *current = findNode(root, key);
    if (current != nullptr) {
        deleteTree(current->left);
        deleteTree(current->right);
        current->right = nullptr;
        current->left = nullptr;
    }
}


int lab9_task2() {
    Node *root = nullptr;

    ifstream file("../lab-09/data.txt");
    if (!file) {
        cout << "File not found!\n";
        return 0;
    }

    int code;
    string name;
    double price;

    while (file >> code >> name >> price) {
        root = insertInTree(root, code, name, price);
    }

    file.close();

    cout << "BST (inorder):\n";
    showInorder(root);

    double sum = 0;
    int count = 0;
    calculateSumAndCount(root, sum, count);

    if (count > 0)
        cout << "\nAverage price: " << sum / count << endl;

    cout << "\nNodes per level:\n";
    calculateNodesPerLevel(root);

    int key;
    cout << "\nEnter code to remove subtree: ";
    cin >> key;

    removeSubtree(root, key); //!!!!!!!!!!!!!!!!!!!!!!!!!!

    cout << "\nTree after deletion:\n";
    showInorder(root);

    deleteTree(root);

    return 0;
}
