#include <iostream>
#include <string>

using namespace std;

struct Car {
    string name;
    int year;
    int mileage;
};

struct Node {
    Car data;
    Node *next;
};

// Function to create a new node
Node *createNode(string name, int year, int mileage) {
    Node *newNode = new Node;
    newNode->data = {name, year, mileage};
    newNode->next = nullptr;
    return newNode;
}

// Insert first element
void insertFirst(Node *&head) {
    string name;
    int year, mileage;

    cout << "Enter car name: ";
    cin >> name;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter mileage: ";
    cin >> mileage;

    head = createNode(name, year, mileage);
}

// Insert at beginning
void insertAtBeginning(Node *&head) {
    string name;
    int year, mileage;

    cout << "Enter car name: ";
    cin >> name;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter mileage: ";
    cin >> mileage;

    Node *newNode = createNode(name, year, mileage);
    newNode->next = head;
    head = newNode;
}

// Insert at end
void insertAtEnd(Node *&head) {
    string name;
    int year, mileage;

    cout << "Enter car name: ";
    cin >> name;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter mileage: ";
    cin >> mileage;

    Node *newNode = createNode(name, year, mileage);

    if (!head) {
        head = newNode;
        return;
    }

    Node *temp = head;
    while (temp->next)
        temp = temp->next;

    temp->next = newNode;
}

// Insert after given name
void insertAfter(Node *head) {
    if (!head) return;

    string target;
    cout << "Enter car name to insert after: ";
    cin >> target;

    Node *temp = head;
    while (temp && temp->data.name != target)
        temp = temp->next;

    if (!temp) {
        cout << "Car not found!\n";
        return;
    }

    string name;
    int year, mileage;

    cout << "Enter new car name: ";
    cin >> name;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter mileage: ";
    cin >> mileage;

    Node *newNode = createNode(name, year, mileage);
    newNode->next = temp->next;
    temp->next = newNode;
}

// Insert before given name
void insertBefore(Node *&head) {
    if (!head) return;

    string target;
    cout << "Enter car name to insert before: ";
    cin >> target;

    if (head->data.name == target) {
        insertAtBeginning(head);
        return;
    }

    Node *prev = nullptr;
    Node *curr = head;

    while (curr && curr->data.name != target) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Car not found!\n";
        return;
    }

    string name;
    int year, mileage;

    cout << "Enter new car name: ";
    cin >> name;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter mileage: ";
    cin >> mileage;

    Node *newNode = createNode(name, year, mileage);
    prev->next = newNode;
    newNode->next = curr;
}

// Search by name
void search(Node *head) {
    string name;
    cout << "Enter car name to search: ";
    cin >> name;

    Node *temp = head;
    while (temp) {
        if (temp->data.name == name) {
            cout << "Car with name " << name << " is in the list.\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Car with name " << name << " is NOT in the list.\n";
}

// Delete nodes with year < value
void deleteByYear(Node *&head) {
    int yearLimit;
    cout << "Enter year limit: ";
    cin >> yearLimit;

    while (head && head->data.year < yearLimit) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    Node *curr = head;
    while (curr && curr->next) {
        if (curr->next->data.year < yearLimit) {
            Node *temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
}

// Display list
void display(Node *head) {
    if (!head) {
        cout << "List is empty.\n";
        return;
    }

    Node *temp = head;
    while (temp) {
        cout << temp->data.name << " | "
                << temp->data.year << " | "
                << temp->data.mileage << " km\n";
        temp = temp->next;
    }
}

// Menu
int lab12_task2() {
    Node *head = nullptr;
    int choice;

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Insert first element\n";
        cout << "2. Insert at beginning\n";
        cout << "3. Insert at end\n";
        cout << "4. Insert after element\n";
        cout << "5. Insert before element\n";
        cout << "6. Search by name\n";
        cout << "7. Delete by year\n";
        cout << "8. Display list\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertFirst(head);
                break;
            case 2: insertAtBeginning(head);
                break;
            case 3: insertAtEnd(head);
                break;
            case 4: insertAfter(head);
                break;
            case 5: insertBefore(head);
                break;
            case 6: search(head);
                break;
            case 7: deleteByYear(head);
                break;
            case 8: display(head);
                break;
            case 9: cout << "Exiting...\n";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 9);

    return 0;
}
