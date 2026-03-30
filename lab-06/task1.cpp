#include <iostream>
#include <ctime>
using namespace std;


struct Stack {
    double data;
    Stack *next;
};

static Stack *push(Stack *top, double value) {
    auto *newNode = new Stack;
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

static Stack *pop(Stack *top, double &value) {
    if (top == nullptr) {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    Stack *temp = top;
    value = top->data;
    top = top->next;
    delete temp;
    return top;
}

static void showStack(Stack *top) {
    if (top == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    Stack *current = top;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

static Stack *removeLessThan(Stack *top, double threshold) {
    Stack *newTop = nullptr;
    double value;

    while (top != nullptr) {
        top = pop(top, value);
        if (value >= threshold) {
            newTop = push(newTop, value);
        }
    }

    while (newTop != nullptr) {
        newTop = pop(newTop, value);
        top = push(top, value);
    }

    return top;
}


static double calculateAverage(Stack *top) {
    if (top == nullptr) {
        return 0;
    }

    double sum = 0;
    int count = 0;
    Stack *current = top;

    while (current != nullptr) {
        sum += current->data;
        count++;
        current = current->next;
    }

    return sum / count;
}


static void deleteStack(Stack *top) {
    double value;
    while (top != nullptr) {
        top = pop(top, value);
    }
}

int lab6_task1() {
    srand(time(nullptr));

    Stack *stack = nullptr;
    int lengthOfStack;
    double threshold;

    cout << "Enter number of elements: ";
    cin >> lengthOfStack;

    for (int i = 0; i < lengthOfStack; i++) {
        double randomValue = (rand() % 1700) / 100.0 - 6;

        stack = push(stack, randomValue);
        // cout << randomValue << " ";
    }
    cout << endl << endl;

    showStack(stack);

    cout << "\nEnter treshold number: ";
    cin >> threshold;

    stack = removeLessThan(stack, threshold);

    cout << "\nStack after delete elements after " << threshold << ":" << endl;
    showStack(stack);

    double average = calculateAverage(stack);
    if (stack != nullptr) {
        cout << "\nAverage after deleting: " << average << endl;
    } else {
        cout << "\nStack is empty" << endl;
    }

    deleteStack(stack);

    return 0;
}
