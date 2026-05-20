#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <windows.h>

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const int HALF = 13; // 26/2 = 13

// Функція шифрування/дешифрування (працює однаково, бо заміна симетрична)
char transformChar(char ch) {
    if (!isalpha(ch)) return ch;

    bool isUpper = isupper(ch);
    char lowerCh = tolower(ch);

    int pos = ALPHABET.find(lowerCh);
    if (pos == string::npos) return ch;

    char result;
    if (pos < HALF) {
        result = ALPHABET[pos + HALF];
    } else {
        result = ALPHABET[pos - HALF];
    }

    return isUpper ? toupper(result) : result;
}

string transformText(const string &text) {
    string result = text;
    for (char &ch: result) {
        ch = transformChar(ch);
    }
    return result;
}

string processFromConsole() {
    cout << "Введіть текст (Enter для завершення):\n";
    string line;
    cin.ignore(); // очищаємо buffer після попереднього вводу
    getline(cin, line);
    string result = transformText(line);
    cout << "Результат: " << result << endl;
    return result;
}

string processFromFile() {
    string inputFile, outputFile;
    cout << "Введіть ім'я вхідного файлу: ";
    cin >> inputFile;
    cout << "Введіть ім'я вихідного файлу: ";
    cin >> outputFile;

    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "Помилка: не вдалося відкрити файл " << inputFile << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    string result = transformText(content);

    return result;
}

int lab18_task2() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "=== Шифрування простою заміною (A<->N, B<->O, ... M<->Z) ===\n\n";

    int choiceMode;
    cout << "Виберіть режим:\n";
    cout << "1 - Шифрування\n";
    cout << "2 - Дешифрування\n";
    cout << "Ваш вибір: ";
    cin >> choiceMode;

    if (choiceMode != 1 && choiceMode != 2) {
        cout << "Невірний вибір!" << endl;
        return 1;
    }

    string modeName = (choiceMode == 1) ? "шифрування" : "дешифрування";
    cout << "Ви обрали " << modeName << ".\n\n";
    int sourceChoice;
    cout << "Виберіть джерело даних:\n";
    cout << "1 - Введення з консолі\n";
    cout << "2 - Читання з файлу\n";
    cout << "Ваш вибір: ";
    cin >> sourceChoice;

    string result;
    if (sourceChoice == 1) {
        result = processFromConsole();
    } else if (sourceChoice == 2) {
        result = processFromFile();
    } else {
        cout << "Невірний вибір!" << endl;
        return 1;
    }


    cout << "\nЗберегти результат у файл? (1-так, 0-ні): ";
    int save;
    cin >> save;
    if (save == 1) {
        cin.ignore();
        cout << "Ім'я файлу: ";
        string fname;
        getline(cin, fname);
        ofstream fout(fname);
        fout << result;
        fout.close();
        cout << "Збережено!" << endl;
    }

    return 0;
}
