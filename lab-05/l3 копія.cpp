#include <iostream>
using namespace std;

struct Mark {
    int m;
    Mark *next;
} *first, *last = 0;

Mark *addFirst(Mark *first, int value) // Додавання в початок списку
{
    Mark *c = new Mark;
    c->m = value;
    c->next = first;
    first = c;
    if (last == 0)
        last = first;
    return first;
}

Mark *addLast(Mark *first, int value) // Додавання в кінець списку
{
    Mark *c = new Mark;
    c->m = value;
    c->next = 0;
    if (first == 0) {
        first = c;
        last = c;
        return first;
    }
    last->next = c;
    last = c;
    return first;
}

Mark *addAfter(Mark* first, int value, int afterValue) // Додавання в середину списку
{
    Mark *q = first;
    while (q!=0 && q->m != afterValue)
        q = q->next;
    if (q == 0) {
        cout<<"Eror";
        return first;
    }
    Mark *c= new Mark;
    c->m = value;
    c->next = q->next;
    q->next = c;
    return first;

}
Mark* delFirst(Mark* first) // Видалення з початку
{
    Mark *q;
    q = first;
    first = first->next;
    if (first == 0) {
        cout<<"List is empty";
    }
    delete q;
    return first;
}
Mark* delLast(Mark* first) // Видалення з кінця
{
    if (first == 0) {
        cout<<"List is empty";
    }
    Mark *q = first;
    while (q->next != last)
        q = q->next;
    delete last;
    last = q;
    last->next = 0;
    return first;
}

void showList(Mark *first) // Вивід списку
{
    Mark *q = first;
    if (q == 0) {
        cout << "List is empty" << endl;
        return;
    }
    while (q != 0) {
        cout << q->m << " ";
        q = q->next;
    }
    cout << endl;
}

int main() {
    showList(first);

    first = addFirst(first, 90);
    cout<<"Додавання в початок списку: ";
    showList(first);

    first = addLast(first, 95);
    cout<<"Додавання в кінець списку: ";
    showList(first);

    first = addAfter(first, 92, 90);
    cout<<"Додавання в середину списку: ";
    showList(first);

    first = delFirst(first);
    cout<<"Видалення з початку: ";
    showList(first);

    first = delLast(first);
    cout<<"Видалення з кінця: ";
    showList(first);

    return 0;
}
