#include <iostream>
using namespace std;

static struct LinkedList {
    string name;
    int yearOfCreate;
    int price;
    LinkedList *next;
} *last = nullptr;

static LinkedList *createContainer() {
    auto c = new LinkedList;
    cout << "enter name: ";
    cin >> c->name;
    cout << "enter year of create: ";
    cin >> c->yearOfCreate;
    cout << "enter price: ";
    cin >> c->price;
    c->next = nullptr;

    return c;
}

static void showContainer(LinkedList const *container) {
    cout << "Name: " << container->name << " | Year: " << container->yearOfCreate << " | Price: " << container->price <<
            endl;
}

void static showList(LinkedList *first) {
    LinkedList *q = first;
    if (q == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    while (q != nullptr) {
        showContainer(q);
        q = q->next;
    }
    cout << endl;
}

static LinkedList *addFirst(LinkedList *first) {
    auto *c = createContainer();
    c->next = first;
    first = c;
    if (last == nullptr)
        last = first;
    return first;
}

void static deleteList(LinkedList *first) {
    if (first == nullptr) return;

    while (first != nullptr) {
        auto temp = first;
        first = first->next;
        delete temp;
    }
}

static int lengthOfList(LinkedList *first) {
    int count = 0;
    LinkedList *q = first;
    while (q != nullptr) {
        count++;
        q = q->next;
    }
    return count;
}

static LinkedList *addLast(LinkedList *first) {
    auto *c = createContainer();

    if (first == nullptr) {
        first = c;
        last = c;
        return first;
    }
    last->next = c;
    last = c;
    return first;
}

void showCarOldestThan(LinkedList *first, const int currentYear, const int olderThan, const int currentPrice) {
    LinkedList *q = first;
    while (q != nullptr) {
        if (currentYear - q->yearOfCreate >= olderThan && q->price <= currentPrice) {
            showContainer(q);
        }
        q = q->next;
    }
}


int lab5_task3(const int lengthOfList) {
    LinkedList *first = nullptr;

    for (int i = 0; i < lengthOfList; i++) {
        first = addLast(first);
    }

    showCarOldestThan(first, 2026, 10, 5000);
    deleteList(first);
    return 0;
}
