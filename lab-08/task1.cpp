#include <iostream>
#include <string>
using namespace std;

struct BookData {
    string title;
    string author;
    int year;
};

struct Node {
    BookData data;
    Node *next;
    Node *prev;

    Node(BookData d) : data(d), next(nullptr), prev(nullptr) {
    }
};

struct ListInfo {
    Node *head;
    Node *tail;

    ListInfo() : head(nullptr), tail(nullptr) {
    }
};

ListInfo *createList() {
    return new ListInfo();
}

void append(ListInfo *list, BookData data) {
    Node *newNode = new Node(std::move(data));

    if (list->head == nullptr) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

BookData removeFirst(ListInfo *list) {
    if (list->head == nullptr) {
        BookData emptyData = {"", "", 0};
        cout << "List is empty" << endl;
        return emptyData;
    }

    Node *temp = list->head;
    BookData data = temp->data;
    list->head = list->head->next;

    if (list->head == nullptr) {
        list->tail = nullptr;
    } else {
        list->head->prev = nullptr;
    }

    delete temp;
    return data;
}

void showNode(Node *node) {
    cout << "| " << node->data.title << " | "
            << node->data.author << " | "
            << node->data.year << " |" << endl;
}

void showList(ListInfo *list, bool reverseOrder = false) {
    if (list->head == nullptr) {
        cout << "Список порожній" << endl;
        return;
    }

    if (!reverseOrder) {
        Node *current = list->head;
        while (current != nullptr) {
            showNode(current);
            current = current->next;
        }
    } else {
        Node *current = list->tail;
        while (current != nullptr) {
            showNode(current);
            current = current->prev;
        }
    }
}

void fillList(ListInfo *list, const string &listName) {
    int numBooks;
    cout << "Enter number of books in list " << listName << ": ";
    cin >> numBooks;
    cin.ignore();

    for (int i = 0; i < numBooks; i++) {
        BookData data;
        cout << "\nBook " << i + 1 << ":" << endl;
        cout << "  Name: ";
        getline(cin, data.title);
        cout << "  Author: ";
        getline(cin, data.author);
        cout << "  Year of published: ";
        cin >> data.year;
        cin.ignore();
        append(list, data);
    }
}

bool isEmpty(ListInfo *list) {
    return list->head == nullptr;
}

void deleteList(ListInfo *list) {
    while (!isEmpty(list)) {
        removeFirst(list);
    }
    delete list;
}

void mergeLists(ListInfo *list1, ListInfo *list2, ListInfo *result) {
    if (isEmpty(list1) && isEmpty(list2)) {
        cout << "Both lists are empty" << endl;
        return;
    }

    if (!isEmpty(list1)) {
        result->head = list1->head;
        result->tail = list1->tail;


        if (!isEmpty(list2)) {
            result->tail->next = list2->head;
            list2->head->prev = result->tail;
            result->tail = list2->tail;
        }
    } else if (!isEmpty(list2)) {
        result->head = list2->head;
        result->tail = list2->tail;
    }
    list1->head = nullptr;
    list1->tail = nullptr;
    list2->head = nullptr;
    list2->tail = nullptr;
}

int lab8_task1() {
    cout << "==========================" << endl;

    ListInfo *list1 = createList();
    ListInfo *list2 = createList();

    fillList(list1, "1");
    fillList(list2, "2");

    cout << "\nList 1: " << endl;
    cout << "Direct order:" << endl;
    showList(list1);
    cout << "\nReverse order:" << endl;
    showList(list1, true);

    cout << "------------------------" << endl;
    cout << "\nList 2:" << endl;
    cout << "Direct order:" << endl;
    showList(list2);
    cout << "\nReverse order:" << endl;
    showList(list2, true);

    ListInfo *mergedList = createList();
    mergeLists(list1, list2, mergedList);


    cout << "\n====================" << endl;
    cout << "Merged list:" << endl;
    showList(mergedList);


    deleteList(mergedList);
    delete list1;
    delete list2;

    return 0;
}


// add comment
