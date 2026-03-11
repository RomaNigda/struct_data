#include <iostream>

#include "lab3.h"

using namespace std;

enum PaymentType {
    cash,
    card,
    transfer
};

struct Payment {

    int number;
    PaymentType type;

    union Details {

        struct {
            double amount;
        } cashPayment;

        struct {
            char cardNumber[20];
        } cardPayment;

        struct {
            char account[20];
            char bank[20];
        } transferPayment;

    } details;
};

int lab3_task3(int n) {


    Payment payments[n];

    int cashCount = 0;
    int cardCount = 0;
    int transferCount = 0;

    for (int i = 0; i < n; i++) {

        cout << "\nPayment #" << i + 1 << endl;

        cout << "Enter payment number: ";
        cin >> payments[i].number;

        int type;
        cout << "Type (0-cash, 1-card, 2-transfer): ";
        cin >> type;

        payments[i].type = (PaymentType)type;

        switch (payments[i].type) {
            case cash:
                cout << "Enter amount: ";
                cin >> payments[i].details.cashPayment.amount;
                cashCount++;
                break;

            case card:
                cout << "Enter card number: ";
                cin >> payments[i].details.cardPayment.cardNumber;
                cardCount++;
                break;

            case transfer:
                cout << "Enter account: ";
                cin >> payments[i].details.transferPayment.account;
                cout << "Enter bank: ";
                cin >> payments[i].details.transferPayment.bank;
                transferCount++;
                break;
        }
    }

    cout << "\nPayments info:\n";

    for (int i = 0; i < n; i++) {

        cout << "\nPayment number: " << payments[i].number << endl;

        switch (payments[i].type) {
            case cash:
                cout << "Type: Cash\n";
                cout << "Amount: " << payments[i].details.cashPayment.amount << endl;
                break;

            case card:
                cout << "Type: Card\n";
                cout << "Card number: " << payments[i].details.cardPayment.cardNumber << endl;
                break;

            case transfer:
                cout << "Type: Transfer\n";
                cout << "Account: " << payments[i].details.transferPayment.account << endl;
                cout << "Bank: " << payments[i].details.transferPayment.bank << endl;
                break;
        }
    }

    cout << "\nStatistics:\n";
    cout << "Cash payments: " << cashCount << endl;
    cout << "Card payments: " << cardCount << endl;
    cout << "Transfer payments: " << transferCount << endl;

    return 0;
}