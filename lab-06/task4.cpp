#include <iostream>
#include <string>
#include <climits>
using namespace std;

struct Team {
    string name;
    string city;
    int points;
};

struct Queue {
    Team data;
    Queue *next;
};

struct QueueInfo {
    Queue *front;
    Queue *rear;
};

static QueueInfo *createQueue() {
    auto *queue = new QueueInfo;
    queue->front = nullptr;
    queue->rear = nullptr;
    return queue;
}

static void enqueue(QueueInfo *queue, Team value) {
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

static Team dequeue(QueueInfo *queue) {
    if (queue->front == nullptr) {
        cout << "Queue is empty!" << endl;
        Team emptyTeam;
        emptyTeam.name = "";
        emptyTeam.city = "";
        emptyTeam.points = -1;
        return emptyTeam;
    }

    Queue *temp = queue->front;
    Team value = temp->data;
    queue->front = queue->front->next;

    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }

    delete temp;
    return value;
}

static void showQueue(QueueInfo *queue) {
    if (queue->front == nullptr) {
        cout << "Queue is empty" << endl;
        return;
    }

    Queue *current = queue->front;
    int i = 1;
    while (current != nullptr) {
        cout << "Team #" << i++ << ": " << current->data.name
                << " | City: " << current->data.city
                << " | Points: " << current->data.points << endl;
        current = current->next;
    }
}

static bool isEmpty(QueueInfo *queue) {
    return queue->front == nullptr;
}

static void deleteQueue(QueueInfo *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    delete queue;
}

Team inputTeam() {
    Team team;
    cout << "Enter team name: ";
    cin.ignore();
    getline(cin, team.name);
    cout << "Enter city: ";
    getline(cin, team.city);
    cout << "Enter points: ";
    cin >> team.points;
    return team;
}

int lab6_task4() {
    QueueInfo *mainQueue = createQueue();
    int numTeams;

    cout << "Volleyballs team queue:\n" << endl;
    cout << "Enter the number of teams: ";
    cin >> numTeams;

    for (int i = 0; i < numTeams; i++) {
        cout << "\n--- Team #" << i + 1 << " ---" << endl;
        Team team = inputTeam();
        enqueue(mainQueue, team);
    }

    cout << "Original queue:" << endl;
    showQueue(mainQueue);

    QueueInfo *tempQueue = createQueue();
    Team leader, outsider;
    bool first = true;

    Queue *current = mainQueue->front;
    while (current != nullptr) {
        enqueue(tempQueue, current->data);

        if (first) {
            leader = current->data;
            outsider = current->data;
            first = false;
        } else {
            if (current->data.points > leader.points) {
                leader = current->data;
            }
            if (current->data.points < outsider.points) {
                outsider = current->data;
            }
        }
        current = current->next;
    }

    cout << "Leader and outsider" << endl;
    cout << "Leader team: " << leader.name << " | City: " << leader.city
            << " | Points: " << leader.points << endl;
    cout << "Outsider team: " << outsider.name << " | City: " << outsider.city
            << " | Points: " << outsider.points << endl;

    QueueInfo *uniqueCityQueue = createQueue();
    string cities[100];
    int cityCount = 0;

    current = mainQueue->front;
    while (current != nullptr) {
        bool cityFound = false;
        for (int i = 0; i < cityCount; i++) {
            if (cities[i] == current->data.city) {
                cityFound = true;
                break;
            }
        }

        if (!cityFound) {
            cities[cityCount++] = current->data.city;
            enqueue(uniqueCityQueue, current->data);
        }
        current = current->next;
    }

    cout << "One team per city" << endl;
    showQueue(uniqueCityQueue);

    int threshold;
    cout << "Enter points threshold: ";
    cin >> threshold;

    QueueInfo *aboveThresholdQueue = createQueue();
    current = mainQueue->front;
    while (current != nullptr) {
        if (current->data.points > threshold) {
            enqueue(aboveThresholdQueue, current->data);
        }
        current = current->next;
    }

    cout << "Teams with points > " << threshold << endl;
    showQueue(aboveThresholdQueue);

    cout << "Restored original queue:" << endl;
    showQueue(mainQueue);

    deleteQueue(mainQueue);
    deleteQueue(tempQueue);
    deleteQueue(uniqueCityQueue);
    deleteQueue(aboveThresholdQueue);


    return 0;
}


