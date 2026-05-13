#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

// Function to prepare text (only letters, convert to lowercase)
string prepareText(const string &input) {
    string result;
    for (char ch: input) {
        if (isalpha(ch)) {
            result += tolower(ch);
        }
    }
    return result;
}

// Function to extend key to match text length
string extendKey(const string &text, const string &key) {
    string extendedKey = "";
    int keyLen = key.length();
    int keyIndex = 0;

    for (int i = 0; i < text.length(); i++) {
        extendedKey += key[keyIndex % keyLen];
        keyIndex++;
    }
    return extendedKey;
}

// Vigenere encryption
string vigenereEncrypt(const string &plaintext, const string &key) {
    string preparedText = prepareText(plaintext);
    string extendedKey = extendKey(preparedText, key);
    string ciphertext = "";

    for (size_t i = 0; i < preparedText.length(); i++) {
        int p = ALPHABET.find(preparedText[i]);
        int k = ALPHABET.find(extendedKey[i]);
        int c = (p + k) % 26;
        ciphertext += ALPHABET[c];
    }

    return ciphertext;
}

// Vigenere decryption
string vigenereDecrypt(const string &ciphertext, const string &key) {
    string preparedText = prepareText(ciphertext);
    string extendedKey = extendKey(preparedText, key);
    string plaintext = "";

    for (size_t i = 0; i < preparedText.length(); i++) {
        int c = ALPHABET.find(preparedText[i]);
        int k = ALPHABET.find(extendedKey[i]);
        int p = (c - k + 26) % 26;
        plaintext += ALPHABET[p];
    }

    return plaintext;
}

// Process encryption/decryption from console
string processFromConsole(int mode, const string &key) {
    cout << "\nEnter text: ";
    cin.ignore();
    string text;
    getline(cin, text);

    string result;
    if (mode == 1) {
        result = vigenereEncrypt(text, key);
        cout << "\nEncrypted text: " << result << endl;
    } else {
        result = vigenereDecrypt(text, key);
        cout << "\nDecrypted text: " << result << endl;
    }
    return result;
}

// Process encryption/decryption from file
string processFromFile(int mode, const string &key) {
    string inputFile, outputFile;
    cout << "Enter input filename: ";
    cin >> inputFile;
    cout << "Enter output filename: ";
    cin >> outputFile;

    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "Error: cannot open file " << inputFile << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    string result;
    if (mode == 1) {
        result = vigenereEncrypt(content, key);
        cout << "\nEncryption completed." << endl;
    } else {
        result = vigenereDecrypt(content, key);
        cout << "\nDecryption completed." << endl;
    }

    return result;
}

// Function to validate key (only letters)
bool isValidKey(const string &key) {
    if (key.empty()) return false;
    for (char ch: key) {
        if (!isalpha(ch)) return false;
    }
    return true;
}


void displayVigenereTableCompact() {
    int n = ALPHABET.length();
    cout << "\n";
    cout << "   ";
    for (int i = 0; i < n; i++) {
        cout << "  " << ALPHABET[i];
    }
    cout << "\n";

    for (int row = 0; row < n; row++) {
        cout << " " << ALPHABET[row] << " ";
        for (int col = 0; col < n; col++) {
            int shiftedIndex = (row + col) % n;
            cout << "  " << ALPHABET[shiftedIndex];
        }
        cout << "\n";
    }
    cout << "\n";
}


int lab18_task3() {
    cout << "=== VIGENERE CIPHER (English Alphabet) ===\n\n";

    // Select mode
    int mode;
    cout << "Select mode:\n";
    cout << "1 - Encryption\n";
    cout << "2 - Decryption\n";
    cout << "Your choice: ";
    cin >> mode;

    if (mode != 1 && mode != 2) {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    string modeName = (mode == 1) ? "encryption" : "decryption";
    cout << "\nYou selected " << modeName << ".\n";

    // Get keyword
    string keyword;
    cout << "Enter keyword (letters only): ";
    cin >> keyword;

    // Convert keyword to lowercase
    for (char &ch: keyword) {
        ch = tolower(ch);
    }

    if (!isValidKey(keyword)) {
        cout << "Error: Keyword must contain only letters!" << endl;
        return 1;
    }

    cout << "\nKeyword: " << keyword << endl;

    // Select data source
    int source;
    cout << "\nSelect data source:\n";
    cout << "1 - Console input\n";
    cout << "2 - Read from file\n";
    cout << "Your choice: ";
    cin >> source;

    string result;

    if (source == 1) {
        result = processFromConsole(mode, keyword);
    } else if (source == 2) {
        result = processFromFile(mode, keyword);
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    cout << "\nSave into file? (1-yes, 0-no): ";
    int save;
    cin >> save;
    if (save == 1) {
        cin.ignore();
        cout << "Name of file: ";
        string fname;
        getline(cin, fname);
        ofstream fout(fname);
        fout << result;
        fout.close();
        cout << "Saved!" << endl;
    }

    cout << "===============================\n";
    displayVigenereTableCompact();

    return 0;
}
