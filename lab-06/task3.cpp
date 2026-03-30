#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

struct Queue {
    int data;
    Queue *next;
};

struct QueueInfo {
    Queue *front;
    Queue *rear;
};

QueueInfo *createQueue() {
    auto *queue = new QueueInfo;
    queue->front = nullptr;
    queue->rear = nullptr;
    return queue;
}

void enqueue(QueueInfo *queue, int value) {
    auto *newNode = new Queue;
    newNode->data = value;
    newNode->next = nullptr;

    if (queue->rear == nullptr) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(QueueInfo *queue) {
    if (queue->front == nullptr) {
        cout << "Queue is empty!" << endl;
        return -1;
    }

    Queue *temp = queue->front;
    int value = temp->data;
    queue->front = queue->front->next;

    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }

    delete temp;
    return value;
}

void showQueue(QueueInfo *queue) {
    if (queue->front == nullptr) {
        cout << "Queue is empty" << endl;
        return;
    }

    Queue *current = queue->front;
    cout << "Queue elements: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

bool isEmpty(QueueInfo *queue) {
    return queue->front == nullptr;
}

double calculateGeometricMean(QueueInfo *queue) {
    if (isEmpty(queue)) {
        return 0;
    }

    double product = 1.0;
    int count = 0;
    Queue *current = queue->front;

    while (current != nullptr) {
        product *= current->data;
        count++;
        current = current->next;
    }

    return pow(product, 1.0 / count);
}

void deleteQueue(QueueInfo *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    delete queue;
}

int lab6_task3() {
    srand(time(nullptr));

    QueueInfo *mainQueue = createQueue();
    int numElements;

    cout << "Enter the number of elements in queue: ";
    cin >> numElements;

    for (int i = 0; i < numElements; i++) {
        int randomValue = rand() % 100 + 1;
        enqueue(mainQueue, randomValue);
    }
    cout << endl;

    cout << "\nOriginal queue:" << endl;
    showQueue(mainQueue);

    QueueInfo *newQueue = createQueue();

    cout << "\nProcessing queue elements:" << endl;
    cout << "----------------------------------------" << endl;

    int elementCount = 0;
    while (!isEmpty(mainQueue)) {
        int currentElement = dequeue(mainQueue);
        elementCount++;

        if (currentElement % 2 == 0) {
            enqueue(newQueue, currentElement);
            enqueue(newQueue, 100);
        }
    }

    cout << "\nNew queue (after processing even numbers):" << endl;
    showQueue(newQueue);


    if (!isEmpty(newQueue)) {
        double geometricMean = calculateGeometricMean(newQueue);
        cout << "\nGeometric mean of new queue elements: " << geometricMean << endl;
    } else {
        cout << "\nNew queue is empty - geometric mean cannot be calculated" << endl;
    }

    deleteQueue(mainQueue);
    deleteQueue(newQueue);

    return 0;
}

