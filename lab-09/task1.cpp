#include <iostream>
using namespace std;

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

static Node *insertIntoTree(Node *root, int value) {
    if (!root) return new Node(value);

    if (value < root->data)
        root->left = insertIntoTree(root->left, value);
    else if (value > root->data)
        root->right = insertIntoTree(root->right, value);

    return root;
}

static bool isKeyInTree(Node *root, int key) {
    if (!root) return false;
    if (root->data == key) return true;

    if (key < root->data)
        return isKeyInTree(root->left, key);

    return isKeyInTree(root->right, key);
}

static void showInorder(Node *root) {
    if (!root) return;
    showInorder(root->left);
    cout << root->data << " ";
    showInorder(root->right);
}

static int depthOfTree(Node *root) {
    if (!root) return 0;
    return 1 + max(depthOfTree(root->left), depthOfTree(root->right));
}


static void splitTree(Node *root, Node *&evenTree, Node *&oddTree) {
    if (!root) return;

    if (root->data % 2 == 0)
        evenTree = insertIntoTree(evenTree, root->data);
    else
        oddTree = insertIntoTree(oddTree, root->data);

    splitTree(root->left, evenTree, oddTree);
    splitTree(root->right, evenTree, oddTree);
}


static void deleteTree(const Node *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int lab9_task1() {
    Node *root = nullptr;
    Node *evenTree = nullptr;
    Node *oddTree = nullptr;

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    int choice;
    cout << "1 - Manual input, 2 - Random generation: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter elements:\n";
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            root = insertIntoTree(root, x);
        }
    } else {
        int a, b;
        cout << "Enter range [a, b]: ";
        cin >> a >> b;

        if (n > (b - a + 1)) {
            cout << "Error: n is greater than number of possible values!\n";
            return 0;
        }

        srand(time(0));
        for (int i = 0; i < n; i++) {
            int x = a + rand() % (b - a + 1);
            cout << x << " ";
            root = insertIntoTree(root, x);
        }
        cout << endl;
    }



    cout << "\nTree (inorder): ";
    showInorder(root);
    cout << endl;

    int key;
    cout << "Enter value to search: ";
    cin >> key;

    if (isKeyInTree(root, key))
        cout << "Element found\n";
    else
        cout << "Element not found\n";




    splitTree(root, evenTree, oddTree);

    cout << "\nEven elements: ";
    showInorder(evenTree);

    cout << "\nOdd elements: ";
    showInorder(oddTree);

    cout << "\n\nMain tree depth: " << depthOfTree(root);
    cout << "\nEven tree depth: " << depthOfTree(evenTree);
    cout << "\nOdd tree depth: " << depthOfTree(oddTree);

    deleteTree(root);
    deleteTree(evenTree);
    deleteTree(oddTree);

    return 0;
}


