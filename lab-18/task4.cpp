#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>

using namespace std;

namespace lab18_task4_n {
    const int GRID_SIZE = 5;
    const string ALPHABET = "abcdefghiklmnopqrstuvwxyz"; // 25 letters (no j)

    char grid[GRID_SIZE][GRID_SIZE];
    map<char, string> encryptMap;
    map<string, char> decryptMap;

    // Generate random shuffled alphabet
    string getShuffledAlphabet() {
        string alphabet = ALPHABET;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(alphabet.begin(), alphabet.end(), default_random_engine(seed));
        return alphabet;
    }

    // Prepare text (convert j to i, remove non-letters, to lowercase)
    string prepareText(const string &input) {
        string result;
        for (char ch: input) {
            if (isalpha(ch)) {
                char lower = tolower(ch);
                if (lower == 'j') lower = 'i';
                result += lower;
            }
        }
        return result;
    }

    // Initialize grid and mappings
    void initCipher() {
        string shuffled = getShuffledAlphabet();

        int index = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = shuffled[index++];
                string coord = to_string(i + 1) + to_string(j + 1);
                encryptMap[grid[i][j]] = coord;
                decryptMap[coord] = grid[i][j];
            }
        }
    }

    // Display the Polybius square
    void displayGrid() {
        cout << "\n=== POLYBIUS SQUARE (5x5) ===\n";
        cout << "    1   2   3   4   5\n";
        cout << "  +---+---+---+---+---+\n";
        for (int i = 0; i < GRID_SIZE; i++) {
            cout << i + 1 << " |";
            for (int j = 0; j < GRID_SIZE; j++) {
                cout << " " << grid[i][j] << " |";
            }
            cout << "\n  +---+---+---+---+---+\n";
        }
        cout << "\nNote: 'J' is treated as 'I'\n\n";
    }

    // Display mapping table
    void displayMapping() {
        cout << "\n=== CHARACTER MAPPING ===\n";
        cout << "Letter -> Coordinates:\n";
        for (const auto &pair: encryptMap) {
            cout << "  " << pair.first << "  -> " << pair.second << "\n";
        }
        cout << "\n";
    }

    // Encrypt function
    string encrypt(const string &plaintext) {
        string prepared = prepareText(plaintext);
        string ciphertext;

        for (char ch: prepared) {
            if (encryptMap.find(ch) != encryptMap.end()) {
                ciphertext += encryptMap[ch];
            }
        }
        return ciphertext;
    }

    // Decrypt function
    string decrypt(const string &ciphertext) {
        string plaintext;

        for (size_t i = 0; i < ciphertext.length(); i += 2) {
            if (i + 1 < ciphertext.length()) {
                string coord = ciphertext.substr(i, 2);
                if (decryptMap.find(coord) != decryptMap.end()) {
                    plaintext += decryptMap[coord];
                }
            }
        }
        return plaintext;
    }

    // Process from console
    void processFromConsole(int mode) {
        cin.ignore();

        if (mode == 1) {
            cout << "\nEnter text to encrypt: ";
            string text;
            getline(cin, text);

            string encrypted = encrypt(text);
            cout << "\n=== RESULTS ===\n";
            cout << "Original text: " << text << endl;
            cout << "Encrypted text: " << encrypted << endl;
        } else {
            cout << "\nEnter text to decrypt (format: row+col pairs, e.g., 112131 for 'abc'): ";
            string text;
            getline(cin, text);

            string decrypted = decrypt(text);
            cout << "\n=== RESULTS ===\n";
            cout << "Original ciphertext: " << text << endl;
            cout << "Decrypted text: " << decrypted << endl;
        }
    }

    // Process from file
    void processFromFile(int mode) {
        string inputFile, outputFile;
        cout << "\nEnter input filename: ";
        cin >> inputFile;
        cout << "Enter output filename: ";
        cin >> outputFile;

        ifstream inFile(inputFile);
        if (!inFile) {
            cout << "Error: cannot open file " << inputFile << endl;
            return;
        }

        string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        cout << "\n=== RESULTS ===\n";
        cout << "Original content read from file:\n" << content << endl;

        if (mode == 1) {
            string encrypted = encrypt(content);
            cout << "\nEncrypted text:\n" << encrypted << endl;

            ofstream outFile(outputFile);
            if (outFile) {
                outFile << encrypted;
                outFile.close();
                cout << "\nEncrypted result saved to " << outputFile << endl;
            }
        } else {
            string decrypted = decrypt(content);
            cout << "\nDecrypted text:\n" << decrypted << endl;

            ofstream outFile(outputFile);
            if (outFile) {
                outFile << decrypted;
                outFile.close();
                cout << "\nDecrypted result saved to " << outputFile << endl;
            }
        }
    }

    int lab18_task4() {
        cout << "=== POLYBIUS SQUARE CIPHER ===\n";
        cout << "Random grid is generated automatically.\n";

        // Initialize cipher
        initCipher();

        // Display the random Polybius square
        displayGrid();

        // Ask if user wants to see full mapping
        char showMapping;
        cout << "Show full character mapping? (y/n): ";
        cin >> showMapping;
        if (showMapping == 'y' || showMapping == 'Y') {
            displayMapping();
        }

        // Select mode
        int mode;
        cout << "\n=== SELECT MODE ===\n";
        cout << "1 - Encryption\n";
        cout << "2 - Decryption\n";
        cout << "Your choice: ";
        cin >> mode;

        if (mode != 1 && mode != 2) {
            cout << "Invalid choice!" << endl;
            return 1;
        }

        // Select data source
        int source;
        cout << "\n=== SELECT DATA SOURCE ===\n";
        cout << "1 - Console input\n";
        cout << "2 - Read from file\n";
        cout << "Your choice: ";
        cin >> source;

        if (source == 1) {
            processFromConsole(mode);
        } else if (source == 2) {
            processFromFile(mode);
        } else {
            cout << "Invalid choice!" << endl;
            return 1;
        }

        return 0;
    }
}

int lab18_task4() {
    lab18_task4_n::lab18_task4();
    return 0;
}
