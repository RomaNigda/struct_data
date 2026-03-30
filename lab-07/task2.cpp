#include <iostream>
using namespace std;

struct EmployeeData {
    string name;
    string department;
    double salary{};
};

struct Node {
    EmployeeData data;
    Node *next;
    Node *prev;

    Node(EmployeeData d) : data(std::move(d)), next(nullptr), prev(nullptr) {
    }
};

struct ListInfo {
    Node *head;
    Node *tail;

    ListInfo() : head(nullptr), tail(nullptr) {
    }
};

static ListInfo *createList() {
    return new ListInfo();
}

static void append(ListInfo *list, EmployeeData data) {
    auto newNode = new Node(std::move(data));


    if (list->head == nullptr) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

static EmployeeData removeFirst(ListInfo *list) {
    if (list->head == nullptr) {
        EmployeeData emptyData = {"", "", 0.0};
        cout << "List is empty" << endl;
        return emptyData;
    }
    Node *temp = list->head;
    EmployeeData data = temp->data;

    list->head = list->head->next;

    if (list->head == nullptr) {
        list->tail = nullptr;
    } else {
        list->head->prev = nullptr;
    }

    delete temp;
    return data;
}


static void showNode(Node *node) {
    cout << "| " << node->data.name << " | " << node->data.department
            << " | " << node->data.salary << " |" << endl;
}

static void showList(ListInfo *list, bool reverseOrder = false) {
    if (list->head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    if (!reverseOrder) {
        auto current = list->head;
        while (current != nullptr) {
            showNode(current);
            current = current->next;
        }
    } else {
        auto current = list->tail;
        while (current != nullptr) {
            showNode(current);
            current = current->prev;
        }
    }
}

static void fillList(ListInfo *list) {
    int numberOfEmployees;
    cout << "Enter the number of employees to be added: ";
    cin >> numberOfEmployees;

    for (int i = 0; i < numberOfEmployees; i++) {
        EmployeeData data;
        cout << "Enter the employee name: ";
        cin >> data.name;
        cout << "Enter the department: ";
        cin >> data.department;
        cout << "Enter the salary: ";
        cin >> data.salary;
        append(list, data);
    }
}

static bool isEmpty(ListInfo *list) {
    return list->head == nullptr;
}

static void deleteList(ListInfo *list) {
    while (!isEmpty(list)) {
        removeFirst(list);
    }
    delete list;
}

void splitListBySalary(ListInfo *list, ListInfo *listBelow, ListInfo *listAbove, double thresholdValue) {
    if (isEmpty(list)) {
        cout << "List is empty" << endl;
        return;
    }

    Node *current = list->head;

    while (current != nullptr) {
        if (current->data.salary > thresholdValue) {
            append(listAbove, current->data);
        } else {
            append(listBelow, current->data);
        }
        current = current->next;
    }
}


void addNewEmployeeWithoutData(ListInfo *list) {
    EmployeeData data;
    cout << "Enter the employee name: ";
    cin >> data.name;
    cout << "Enter the department: ";
    cin >> data.department;
    cout << "Enter the salary: ";
    cin >> data.salary;
    append(list, data);
}

int lab7_task2() {
    ListInfo *list = createList();

    ListInfo *listBelowThreshold = createList();
    ListInfo *listAboveThreshold = createList();
    fillList(list);


    cout << "===========================" << endl;
    cout << "Created list: " << endl;
    showList(list);


    splitListBySalary(list, listBelowThreshold, listAboveThreshold, 10000);

    cout << "---------------------------" << endl;
    cout << "List below threshold: " << endl;
    cout << "Direct oreder: " << endl;
    showList(listBelowThreshold);
    cout << "--------" << endl;
    cout << "Reverse order: " << endl;
    showList(listBelowThreshold, true);

    cout << "---------------------------" << endl;
    cout << "List above threshold: " << endl;
    cout << "Direct order: " << endl;
    showList(listAboveThreshold);
    cout << "--------" << endl;
    cout << "Reverse order: " << endl;
    showList(listAboveThreshold, true);

    cout << "Adding new employee: " << endl;
    addNewEmployeeWithoutData(listAboveThreshold);


    deleteList(list);
    deleteList(listBelowThreshold);
    deleteList(listAboveThreshold);
    return 0;
}
