#include <iostream>
using namespace std;

static struct LinkedList {
    string name;
    int lengthToKyiv;
    LinkedList *next;
} *last = nullptr;

static LinkedList *createContainer() {
    auto c = new LinkedList;
    cout << "enter name: ";
    cin >> c->name;
    cout << "enter length to Kyiv: ";
    cin >> c->lengthToKyiv;
    c->next = nullptr;

    return c;
}

static void showContainer(LinkedList const *container) {
    cout << "Name: " << container->name << " | Year: " << container->lengthToKyiv << endl;
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

static int lengthOfList(LinkedList *first) {
    int count = 0;
    LinkedList *q = first;
    while (q != nullptr) {
        count++;
        q = q->next;
    }
    return count;
}

void showTwoMostDistanceCity(LinkedList *first) {
    if (lengthOfList(first) < 2) {
        cout << "Not enough elements" << endl;
        return;
    }

    LinkedList *elementOne = first;
    LinkedList *elementTwo = first->next;

    LinkedList *q = first;
    while (q != nullptr) {
        if (q->lengthToKyiv > elementOne->lengthToKyiv) {
            elementTwo = elementOne;
            elementOne = q;
        } else if (q->lengthToKyiv > elementTwo->lengthToKyiv && q != elementOne) {
            elementTwo = q;
        }

        q = q->next;
    }
    showContainer(elementOne);
    showContainer(elementTwo);
}

LinkedList *addLast(LinkedList *first) {
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


int lab5_task2(const int length) {
    LinkedList *first = nullptr;

    for (int i = 0; i < length; i++) {
        first = addFirst(first);
    }
    cout << lengthOfList(first) << endl;
    showList(first);

    cout << "=========================\n";
    showTwoMostDistanceCity(first);
    cout << "=========================\n";
    cout << "Enter foreign city: \n";
    first = addLast(first);
    showList(first);


    deleteList(first);
    return 0;
}
