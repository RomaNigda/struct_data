#include <iostream>
#include <string>
using namespace std;

struct BusRoute {
    int routeNumber;
    string destination;
    int passengerCount;
};

struct QueueNode {
    BusRoute data;
    QueueNode *next;

    QueueNode(BusRoute d) : data(d), next(nullptr) {
    }
};

struct QueueInfo {
    QueueNode *front;
    QueueNode *rear;

    QueueInfo() : front(nullptr), rear(nullptr) {
    }
};

static QueueInfo *createQueue() {
    return new QueueInfo();
}

static void enqueue(QueueInfo *queue, BusRoute route) {
    QueueNode *newNode = new QueueNode(route);

    if (queue->rear == nullptr) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Видалення елемента з черги
static BusRoute dequeue(QueueInfo *queue) {
    if (queue->front == nullptr) {
        BusRoute emptyRoute = {-1, "", -1};
        cout << "Queue is empty!" << endl;
        return emptyRoute;
    }

    QueueNode *temp = queue->front;
    BusRoute route = temp->data;
    queue->front = queue->front->next;

    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }

    delete temp;
    return route;
}

static void showNode(QueueNode *node) {
    cout << "   " << node->data.routeNumber << "    |      "
            << node->data.destination << "       |      "
            << node->data.passengerCount << endl;
}

static void showQueue(QueueInfo *queue) {
    if (queue->front == nullptr) {
        cout << "Queue is empty" << endl;
        return;
    }

    QueueNode *current = queue->front;
    cout << "\n==================================================" << endl;
    cout << "Queue: " << endl;

    while (current != nullptr) {
        showNode(current);
        current = current->next;
    }
    cout << "==================================================" << endl;
}

static bool isEmpty(QueueInfo *queue) {
    return queue->front == nullptr;
}

static void fillQueue(QueueInfo *queue, const string &queueName) {
    int numRoutes;
    cout << "Enter count of routes in queue " << queueName << ": ";
    cin >> numRoutes;

    for (int i = 0; i < numRoutes; i++) {
        BusRoute route;
        cout << "\nRoute: " << i + 1 << ":" << endl;
        cout << "  Number: ";
        cin >> route.routeNumber;
        cin.ignore();
        cout << "  Destination: ";
        getline(cin, route.destination);
        cout << "  Count of passenger: ";
        cin >> route.passengerCount;
        enqueue(queue, route);
    }
}

static void mergeQueues(QueueInfo *queue1, QueueInfo *queue2, QueueInfo *result) {
    while (!isEmpty(queue1)) {
        BusRoute route = dequeue(queue1);
        enqueue(result, route);
    }

    while (!isEmpty(queue2)) {
        BusRoute route = dequeue(queue2);
        enqueue(result, route);
    }
}

static void showRoutesWithMorePassengers(QueueInfo *queue, const int threshold) {
    if (isEmpty(queue)) {
        cout << "Queue is empty!" << endl;
        return;
    }

    QueueNode *current = queue->front;
    bool found = false;

    cout << "\nRoutes with passengers more than > " << threshold << ":" << endl;


    while (current != nullptr) {
        if (current->data.passengerCount > threshold) {
            showNode(current);
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Not found routes with passengers more than > " << threshold << endl;
    }
    cout << "==================================================" << endl;
}

static void serveRoutes(QueueInfo *queue, int countOfRoutes) {
    if (isEmpty(queue)) {
        cout << "Queue is empty!" << endl;
        return;
    }

    cout << "\n\nServing routes: " << endl;

    QueueNode *current = queue->front;
    while (current != nullptr && countOfRoutes > 0) {
        cout << "Serve routes: " << current->data.routeNumber << endl;
        dequeue(queue);
        current = current->next;
        countOfRoutes--;
    }
}

static void deleteQueue(QueueInfo *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    delete queue;
}

int lab8_task2() {
    cout << "==============================\n" << endl;

    QueueInfo *queue1 = createQueue();
    QueueInfo *queue2 = createQueue();

    fillQueue(queue1, "1");
    fillQueue(queue2, "2");

    cout << "\n======================" << endl;
    cout << "Queue 1: ";
    showQueue(queue1);

    cout << "\nQueue 2: ";
    showQueue(queue2);

    QueueInfo *mergedQueue = createQueue();
    mergeQueues(queue1, queue2, mergedQueue);

    cout << "\nMerged queue " << endl;
    showQueue(mergedQueue);


    cout << "\nThreshold routes: " << endl;
    showRoutesWithMorePassengers(mergedQueue, 20);


    serveRoutes(mergedQueue, 2);
    cout << "\nQueue after serving " << endl;
    showQueue(mergedQueue);


    deleteQueue(mergedQueue);
    return 0;
}
