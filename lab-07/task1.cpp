#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <utility>
using namespace std;

struct TemperatureData {
    string date;
    double temp;
};

struct Node {
    TemperatureData data;
    Node *prev;
    Node *next;

    Node(TemperatureData d) : data(std::move(d)), prev(nullptr), next(nullptr) {
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

static void append(ListInfo *list, TemperatureData data) {
    Node *newNode = new Node(std::move(data));

    if (list->head == nullptr) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

static TemperatureData removeFirst(ListInfo *list) {
    if (list->head == nullptr) {
        TemperatureData emptyData = {"", 0.0};
        cout << "List is empty!" << endl;
        return emptyData;
    }

    Node *temp = list->head;
    TemperatureData value = temp->data;
    list->head = list->head->next;

    if (list->head != nullptr) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }

    delete temp;
    return value;
}

void mergeLists(ListInfo *list1, ListInfo *list2) {
    if (list2->head == nullptr) {
        return;
    }

    if (list1->head == nullptr) {
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
    }

    list2->head = nullptr;
    list2->tail = nullptr;
}

void findMinMax(ListInfo *list, double &minTemp, double &maxTemp) {
    if (list->head == nullptr) {
        cout << "List is empty!" << endl;
        minTemp = maxTemp = 0;
        return;
    }

    Node *current = list->head;
    minTemp = current->data.temp;
    maxTemp = current->data.temp;

    while (current != nullptr) {
        if (current->data.temp < minTemp) {
            minTemp = current->data.temp;
        }
        if (current->data.temp > maxTemp) {
            maxTemp = current->data.temp;
        }
        current = current->next;
    }
}

static void showList(ListInfo *list) {
    if (list->head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    Node *current = list->head;
    cout << "List elements:" << endl;

    while (current != nullptr) {
        cout << "| " << current->data.date << " | "
                << current->data.temp << " |" << endl;
        current = current->next;
    }
    cout << "----------------------------------------" << endl;
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

void fillList(ListInfo *list, int numberOfMonth) {
    int numElements;

    cout << "Enter the number of temperature records for month " << numberOfMonth << ": ";
    cin >> numElements;

    for (int i = 0; i < numElements; i++) {
        TemperatureData data;


        data.date = to_string(i + 1) + ".01.2026";
        if (i + 1 < 10) {
            data.date = "0" + data.date;
        }

        data.temp = -20 + (rand() % 500) / 10.0;

        append(list, data);
        // cout << "Added: " << data.date << " - " << data.temp << " C" << endl;
    }
}


int lab7_task1() {
    srand(time(nullptr));

    ListInfo *list1 = createList();
    ListInfo *list2 = createList();

    cout << "\nCreating first list (Month 1):" << endl;
    fillList(list1, 1);

    cout << "\nCreating second list (Month 2):" << endl;
    fillList(list2, 2);


    cout << "\n========================================" << endl;
    cout << "First list (Month 1):" << endl;
    showList(list1);

    cout << "\nSecond list (Month 2):" << endl;
    showList(list2);


    cout << "\nMerging lists (adding month 2 to the end of month 1)..." << endl;
    mergeLists(list1, list2);

    cout << "\nMerged list (chronological order):" << endl;
    showList(list1);
    double minTemp, maxTemp;
    findMinMax(list1, minTemp, maxTemp);

    cout << "\nTemperature results:" << endl;
    cout << "Minimum temperature: " << minTemp << "  C" << endl;
    cout << "Maximum temperature: " << maxTemp << "  C" << endl;


    deleteList(list1);
    deleteList(list2);
    return 0;
}
