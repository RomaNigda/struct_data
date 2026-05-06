#include <iostream>
#include <deque>
#include <algorithm>
#include <ctime>

using namespace std;

struct Order {
    int id;
    string client;
    string address;
    double price;
    int priority; // 1 = urgent, 0 = normal
    string time;

    string status; // ative, completed, canceled
};

// Get current time as string
string getCurrentTime() {
    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back();
    return dt;
}

// Add order
void addOrder(deque<Order> &orders) {
    Order o;

    cout << "Enter ID: ";
    cin >> o.id;
    cout << "Enter client name: ";
    cin >> o.client;
    cout << "Enter address: ";
    cin >> o.address;
    cout << "Enter price: ";
    cin >> o.price;
    cout << "Enter priority (1 = urgent, 0 = normal): ";
    cin >> o.priority;

    o.time = getCurrentTime();
    o.status = "active";

    if (o.priority == 1)
        orders.push_front(o);
    else
        orders.push_back(o);

    cout << "Order added.\n";
}

// Display orders
void display(const deque<Order> &orders) {
    if (orders.empty()) {
        cout << "No orders.\n";
        return;
    }

    for (const auto &o: orders) {
        cout << "\nID: " << o.id
                << "\nClient: " << o.client
                << "\nAddress: " << o.address
                << "\nPrice: " << o.price
                << "\nPriority: " << (o.priority ? "Urgent" : "Normal")
                << "\nTime: " << o.time
                << "\nStatus: " << o.status << "\n";
    }
}

// Delete completed or canceled
void deleteFinished(deque<Order> &orders) {
    orders.erase(remove_if(orders.begin(), orders.end(),
                           [](Order o) {
                               return o.status == "completed" || o.status == "canceled";
                           }), orders.end());

    cout << "Finished orders removed.\n";
}

// Search
void search(deque<Order> &orders) {
    int choice;
    cout << "Search by: 1-ID, 2-Client, 3-Status: ";
    cin >> choice;

    for (auto &o: orders) {
        if ((choice == 1 && cin >> ws && o.id == o.id) ||
            (choice == 2 && o.client == o.client) ||
            (choice == 3 && o.status == o.status)) {
            cout << "Found Order ID: " << o.id << "\n";
        }
    }
}

// Correct search
void searchFixed(deque<Order> &orders) {
    int choice;
    cout << "Search by: 1-ID, 2-Client, 3-Status: ";
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        for (auto &o: orders)
            if (o.id == id)
                cout << "Found order ID: " << o.id << "\n";
    } else if (choice == 2) {
        string name;
        cout << "Enter client: ";
        cin >> name;
        for (auto &o: orders)
            if (o.client == name)
                cout << "Found order ID: " << o.id << "\n";
    } else if (choice == 3) {
        string st;
        cout << "Enter status: ";
        cin >> st;
        for (auto &o: orders)
            if (o.status == st)
                cout << "Found order ID: " << o.id << "\n";
    }
}

// Edit order
void editOrder(deque<Order> &orders) {
    int id;
    cout << "Enter ID to edit: ";
    cin >> id;

    for (auto &o: orders) {
        if (o.id == id) {
            cout << "Enter new price: ";
            cin >> o.price;
            cout << "Enter new status: ";
            cin >> o.status;
            cout << "Updated.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

// Sort by price
void sortByPrice(deque<Order> &orders) {
    sort(orders.begin(), orders.end(),
         [](Order a, Order b) {
             return a.price < b.price;
         });

    cout << "Sorted by price.\n";
}

// Filter
void filter(deque<Order> &orders) {
    double minP, maxP;
    string status;
    int priority;

    cout << "Enter min price: ";
    cin >> minP;
    cout << "Enter max price: ";
    cin >> maxP;
    cout << "Enter status: ";
    cin >> status;
    cout << "Enter priority (1/0): ";
    cin >> priority;

    for (auto &o: orders) {
        if (o.price >= minP && o.price <= maxP &&
            o.status == status &&
            o.priority == priority) {
            cout << "Matched order ID: " << o.id << "\n";
        }
    }
}

// Menu
int lab12_task3() {
    deque<Order> orders;
    int choice;

    do {
        cout << "\n------ ORDER SYSTEM ------\n";
        cout << "1. Add order\n";
        cout << "2. Display orders\n";
        cout << "3. Delete completed/canceled\n";
        cout << "4. Search\n";
        cout << "5. Edit order\n";
        cout << "6. Sort by price\n";
        cout << "7. Filter orders\n";
        cout << "8. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: addOrder(orders);
                break;
            case 2: display(orders);
                break;
            case 3: deleteFinished(orders);
                break;
            case 4: searchFixed(orders);
                break;
            case 5: editOrder(orders);
                break;
            case 6: sortByPrice(orders);
                break;
            case 7: filter(orders);
                break;
        }
    } while (choice != 8);

    return 0;
}
