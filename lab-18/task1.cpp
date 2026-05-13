#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// Українська абетка
string alpha = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
int N = 33;

// Знайти індекс букви в абетці (-1 якщо не буква)
int getIndex(char c) {
    for (int i = 0; i < N; i++) {
        // Кожна українська буква займає 2 байти в UTF-8
        if (alpha[i * 2] == c)
            return i;
    }
    return -1;
}

// Шифрування/дешифрування (shift > 0 — шифрування, shift < 0 — дешифрування)
string caesar(string text, int shift) {
    shift = ((shift % N) + N) % N;
    string result = "";
    int i = 0;
    while (i < text.size()) {
        // Перевіряємо чи це двобайтовий символ кирилиці
        unsigned char c = text[i];
        if (c >= 0xC0 && i + 1 < text.size()) {
            string ch = "";
            ch += text[i];
            ch += text[i + 1];
            int idx = -1;
            for (int j = 0; j < N; j++) {
                string a = "";
                a += alpha[j * 2];
                a += alpha[j * 2 + 1];
                if (a == ch) {
                    idx = j;
                    break;
                }
            }
            if (idx != -1) {
                int newIdx = (idx + shift) % N;
                result += alpha[newIdx * 2];
                result += alpha[newIdx * 2 + 1];
            } else {
                result += text[i];
                result += text[i + 1];
            }
            i += 2;
        } else {
            result += text[i];
            i++;
        }
    }
    return result;
}

// Частотний аналіз — знайти найкращий зсув
int findShift(string text) {
    // Еталонні частоти (індекс відповідає індексу в alpha)
    // Але ref відповідає порядку: о,а,е,і,н,т,с,р,л,в,к,м,д,п,у,з,я,и,б,г,ї,й,х,ж,є,ч,ю,ш,ц,щ,ф,ґ,ь
    // Перебудуємо по індексу абетки
    // Порядок букв у alpha: а=0,б=1,в=2,г=3,ґ=4,д=5,е=6,є=7,ж=8,з=9,и=10,і=11,ї=12,й=13,к=14,л=15,м=16,н=17,о=18,п=19,р=20,с=21,т=22,у=23,ф=24,х=25,ц=26,ч=27,ш=28,щ=29,ь=30,ю=31,я=32
    double refByIdx[33] = {
        8.34, 1.85, 4.48, 1.70, 0.15, 3.61, 7.89, 0.82, 0.95, 2.65,
        2.20, 7.56, 1.49, 1.35, 3.95, 4.70, 3.78, 6.95, 9.28, 3.42,
        5.01, 5.62, 6.29, 2.90, 0.22, 1.11, 0.52, 0.77, 0.59, 0.43,
        0.13, 0.64, 2.47
    };

    // Підрахувати частоти букв у тексті
    int count[33] = {};
    int total = 0;
    int i = 0;
    while (i < (int) text.size()) {
        unsigned char c = text[i];
        if (c >= 0xC0 && i + 1 < (int) text.size()) {
            string ch = "";
            ch += text[i];
            ch += text[i + 1];
            for (int j = 0; j < N; j++) {
                string a = "";
                a += alpha[j * 2];
                a += alpha[j * 2 + 1];
                if (a == ch) {
                    count[j]++;
                    total++;
                    break;
                }
            }
            i += 2;
        } else { i++; }
    }

    // Знайти зсув з найбільшою кореляцією
    int bestShift = 0;
    double bestScore = -1e18;
    for (int s = 0; s < N; s++) {
        double score = 0;
        for (int j = 0; j < N; j++) {
            double freq = (total > 0) ? (100.0 * count[j] / total) : 0;
            int orig = (j - s + N) % N;
            score += freq * refByIdx[orig];
        }
        if (score > bestScore) {
            bestScore = score;
            bestShift = s;
        }
    }
    return bestShift;
}

// Пошук підрядка (KMP)
vector<int> kmpSearch(string text, string pat) {
    vector<int> pos;
    int n = text.size(), m = pat.size();
    if (m == 0) return pos;
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) lps[i++] = ++len;
        else if (len)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
    i = 0;
    int j = 0;
    while (i < n) {
        if (text[i] == pat[j]) {
            i++;
            j++;
        }
        if (j == m) {
            pos.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && text[i] != pat[j]) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
    return pos;
}

int lab18_task1() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int choice;

    cout << "=== ШИФ ЦЕЗАРЯ ===" << endl;
    cout << "1. Шифрування" << endl;
    cout << "2. Дешифрування" << endl;
    cout << "Вибір: ";
    cin >> choice;
    cin.ignore();

    // Читання тексту
    cout << "\n1. Ввести текст з консолі" << endl;
    cout << "2. Читати з файлу" << endl;
    cout << "Вибір: ";
    int src;
    cin >> src;
    cin.ignore();

    string text = "";
    if (src == 1) {
        cout << "Введіть текст: ";
        getline(cin, text);
    } else {
        cout << "Ім'я файлу: ";
        string fname;
        getline(cin, fname);
        ifstream fin(fname);
        if (!fin) {
            cout << "Файл не знайдено!" << endl;
            return 1;
        }
        string line;
        while (getline(fin, line)) text += line + "\n";
        fin.close();
    }

    string result = "";

    if (choice == 1) {
        // Шифрування
        cout << "\nКрок зсуву (від'ємне - вліво, додатне - вправо): ";
        int shift;
        cin >> shift;
        result = caesar(text, shift);
        cout << "\nЗашифрований текст:\n" << result << endl;
    } else {
        // Дешифрування
        cout << "\n1. Обернений зсув" << endl;
        cout << "2. Частотний метод" << endl;
        cout << "Вибір: ";
        int decChoice;
        cin >> decChoice;
        cin.ignore();

        if (decChoice == 1) {
            cout << "Крок зсуву який використовувався при шифруванні: ";
            int shift;
            cin >> shift;
            result = caesar(text, -shift);
            cout << "\nРозшифрований текст:\n" << result << endl;
        } else {
            int shift = findShift(text);
            result = caesar(text, -shift);
            cout << "\nВизначений зсув: " << shift << endl;
            cout << "Розшифрований текст:\n" << result << endl;

            // Перевірка ключовим словом
            cout << "\nВведіть ключове слово для перевірки (або Enter щоб пропустити): ";
            string keyword;
            getline(cin, keyword);
            if (!keyword.empty()) {
                vector<int> found = kmpSearch(result, keyword);
                if (found.empty()) {
                    cout << "Слово не знайдено. Можливо зсув невірний." << endl;
                } else {
                    cout << "Слово знайдено на позиціях: ";
                    for (int p: found) cout << p << " ";
                    cout << endl;
                }
            }
        }
    }

    // Зберегти у файл?
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

    // cout << "Результат: " << endl;
    // cout << result << endl;

    return 0;
}
