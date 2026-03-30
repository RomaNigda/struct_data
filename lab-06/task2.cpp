#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct MusicRecord {
    string media;
    string name;
    string artist;
    double duration;
    int tracks;
    double price;
};

struct Stack {
    MusicRecord data;
    Stack *next;
};

static Stack *push(Stack *top, MusicRecord value) {
    auto *newNode = new Stack;
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

static Stack *pop(Stack *top, MusicRecord &value) {
    if (top == nullptr) {
        cout << "Stack is empty!" << endl;
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
        cout << "Stack is empty" << endl;
        return;
    }

    Stack *current = top;
    int i = 1;
    while (current != nullptr) {
        cout << "Record #" << i++ << ":" << endl;
        cout << "  Media: " << current->data.media << endl;
        cout << "  Title: " << current->data.name << endl;
        cout << "  Artist: " << current->data.artist << endl;
        cout << "  Duration: " << current->data.duration << " min" << endl;
        cout << "  Number of tracks: " << current->data.tracks << endl;
        cout << "  Price: " << current->data.price << " UAH" << endl;
        cout << endl;
        current = current->next;
    }
}

static double getTotalDurationByArtist(Stack *top, const string &artist) {
    double totalDuration = 0;
    Stack *current = top;

    while (current != nullptr) {
        if (current->data.artist == artist) {
            totalDuration += current->data.duration;
        }
        current = current->next;
    }

    return totalDuration;
}

static Stack *filterByCassette(Stack *top) {
    Stack *newStack = nullptr;
    Stack *current = top;

    while (current != nullptr) {
        if (current->data.media == "cassette") {
            newStack = push(newStack, current->data);
        }
        current = current->next;
    }

    return newStack;
}

static double calculateAveragePrice(Stack *top) {
    if (top == nullptr) {
        return 0;
    }

    double sum = 0;
    int count = 0;
    Stack *current = top;

    while (current != nullptr) {
        sum += current->data.price;
        count++;
        current = current->next;
    }

    return sum / count;
}

static void deleteStack(Stack *top) {
    MusicRecord value;
    while (top != nullptr) {
        top = pop(top, value);
    }
}

static MusicRecord inputMusicRecord() {
    MusicRecord record;

    cout << "Enter media type (vinyl/cassette/CD): ";
    cin >> record.media;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, record.name);

    cout << "Enter artist: ";
    getline(cin, record.artist);

    cout << "Enter duration (in minutes): ";
    cin >> record.duration;

    cout << "Enter number of tracks: ";
    cin >> record.tracks;

    cout << "Enter price (UAH): ";
    cin >> record.price;

    return record;
}

int lab6_task2() {
    Stack *mainStack = nullptr;
    int numRecords;

    cout << "Enter the number of music records: ";
    cin >> numRecords;

    for (int i = 0; i < numRecords; i++) {
        cout << "\nRecord #" << i + 1 << endl;
        MusicRecord record = inputMusicRecord();
        mainStack = push(mainStack, record);
    }

    cout << "Stack:" << endl;
    showStack(mainStack);

    string searchArtist;
    cout << "\n========================================" << endl;
    cout << "Enter artist name to search for: ";
    cin.ignore();
    getline(cin, searchArtist);

    double totalDuration = getTotalDurationByArtist(mainStack, searchArtist);
    cout << "Total duration of tracks by artist: " << searchArtist << " is: " << totalDuration << " minutes" << endl;

    Stack *cassetteStack = filterByCassette(mainStack);

    cout << "Cassette records:" << endl;

    if (cassetteStack == nullptr) {
        cout << "No cassette records found" << endl;
    } else {
        showStack(cassetteStack);

        double averagePrice = calculateAveragePrice(cassetteStack);
        cout << "\nAverage price of cassette records: " << averagePrice << " UAH" << endl;
    }

    deleteStack(mainStack);
    deleteStack(cassetteStack);

    return 0;
}
