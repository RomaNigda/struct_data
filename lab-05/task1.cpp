#include <iostream>
using namespace std;

struct LinkedList {
    int number;
    LinkedList *next;
} *last = nullptr;

LinkedList *addFirst(LinkedList *first, int value) {
    auto *c = new LinkedList;
    c->number = value;
    c->next = first;
    first = c;
    if (last == nullptr)
        last = first;
    return first;
}

LinkedList *addLast(LinkedList *first, int value) {
    auto *c = new LinkedList;
    c->number = value;
    c->next = nullptr;
    if (first == nullptr) {
        first = c;
        last = c;
        return first;
    }
    last->next = c;
    last = c;
    return first;
}

LinkedList *addAfter(LinkedList *first, int value, int afterValue) {
    LinkedList *q = first;
    while (q != nullptr && q->number != afterValue) {
        q = q->next;
    }
    if (q == nullptr) {
        cout << "Value not find";
        return first;
    }

    auto *c = new LinkedList;
    c->number = value;
    c->next = q->next;
    q->next = c;
    return first;
}

LinkedList *delFirst(LinkedList *first) {
    auto q = first;
    first = first->next;
    if (first == nullptr) {
        cout << "List is empty";
    }
    delete q;
    return first;
}

LinkedList *delLast(LinkedList *first) {
    if (first == nullptr) {
        cout << "List is empty";
    }
    LinkedList *q = first;
    while (q->next != last)
        q = q->next;
    delete last;
    last = q;
    last->next = nullptr;
    return first;
}

void showList(LinkedList *first) {
    LinkedList *q = first;
    if (q == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    while (q != nullptr) {
        cout << q->number << " ";
        q = q->next;
    }
    cout << endl;
}

float countAverage(LinkedList *first) {
    float sum = 0.0;
    int count = 0;
    LinkedList *q = first;
    while (q != nullptr) {
        sum += q->number;
        q = q->next;
        count++;
    }

    return sum / (float) count;
}

LinkedList *deleteFirstEvenNumber(LinkedList *first) {
    LinkedList *q = first;
    if (q->number % 2 == 0) {
        auto temp = q->next;
        delete q;
        return temp;
    }

    while (q->next != nullptr && q->next->number % 2 != 0) {
        q = q->next;
    }
    if (q->next == nullptr) {
        cout << "Even number not find" << endl;
        return first;
    }
    auto temp = q->next;
    q->next = temp->next;
    delete temp;
    return first;
}

void deleteList(LinkedList *first) {
    if (first == nullptr) return;

    while (first != nullptr) {
        auto temp = first;
        first = first->next;
        delete temp;
    }
}


int lab5_task1() {
    LinkedList *first;
    showList(first);
    first = addFirst(first, 10);
    showList(first);
    first = addLast(first, 30);
    showList(first);
    first = addAfter(first, 20, 10);
    showList(first);
    first = addAfter(first, 25, 10);
    showList(first);

    cout << "Average: " << countAverage(first) << endl;
    showList(first);

    cout << "==================" << endl;

    first = deleteFirstEvenNumber(first);
    showList(first);
    deleteList(first);


    return 0;
}
