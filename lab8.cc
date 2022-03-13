/**
 *    @file: lab8.cc
 *  @author: Josh Marusek
 *    @date: 2021-10-15
 *   @brief: Encrypts or decrypts a file using a caesar cipher
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

void displayMenu();
int getKeyValue();
void encrypt(int key);
void decrypt(int key);
string getFileName (bool isInFile);

int main()
{
    int choice;
    int key = 3;  // default

    do {
        cout << endl;
        displayMenu();
        cin >> choice;
        cin.get();  // remove the newline from the buffer
        switch (choice) {
            case 1:
                // set key
                key = getKeyValue();
                break;
            case 2:
                encrypt(key);
                break;
            case 3:
                decrypt(key);
        }
    } while (choice != 4);

    return (EXIT_SUCCESS);
}

/**
 *  Function: displayMenu
 *  @brief Displays a menu of actions.
 */
void displayMenu() {
    cout << "1. Set the shift key value (default is 3)" << endl;
    cout << "2. Encrypt a file" << endl;
    cout << "3. Decrypt a file" << endl;
    cout << "4. Quit" << endl;
}

/**
 *  Function: getKeyValue
 *  @brief Gets a value 1-10 from cin.
 * 
 *  @return a value 1-10
 */
int getKeyValue() {
    int input;
    do {
        cout << "Enter a key value 1-10: ";
        cin >> input;
    } while (input < 1 || input > 10);
    cin.get();  // remove the newline from the buffer

    return input;
}

/**
 *  Function: encrypt
 *  @brief Writes the encrypted text from one file to another.
 * 
 *  @param key the keyvalue with which to encrypt the file
 */
void encrypt(int key) {
    ifstream inFile;
    ofstream outFile;
    char ch;
    bool retry;

    do {
        retry = false;
        string inFileName = getFileName(true);
        inFile.open(inFileName.c_str());
        if (inFile.fail()) {
            cout << "Failed to open file." << endl;
            retry = true;
        }
    } while (retry);

    do {
        retry = false;
        string outFileName = getFileName(false);
        outFile.open(outFileName.c_str());
        if (outFile.fail()) {
            cout << "Failed to open file." << endl;
            retry = true;
        }
    } while (retry);


    while (inFile.get(ch)) {
        outFile << static_cast<char>(ch + key);
    }

    inFile.close();
    outFile.close();
}

/**
 *  Function: decrypt
 *  @brief Writes the decrypted text from one file to another.
 * 
 *  @param key the keyvalue with which to encrypt the file
 */
void decrypt(int key) {
    ifstream inFile;
    ofstream outFile;
    char ch;
    bool retry = false;

    do {
        retry = false;
        string inFileName = getFileName(true);
        inFile.open(inFileName.c_str());
        if (inFile.fail()) {
            cout << "Failed to open file." << endl;
            retry = true;
        }
    } while (retry);

    do {
        retry = false;
        string outFileName = getFileName(false);
        outFile.open(outFileName.c_str());
        if (outFile.fail()) {
            cout << "Failed to open file." << endl;
            retry = true;
        }
    } while (retry);


    while (inFile.get(ch)) {
        outFile << static_cast<char>(ch - key);
    }

    inFile.close();
    outFile.close();
}

/**
 *  Function: getFileName
 *  @brief Gets the name of a file.
 * 
 *  @return the name of the file
 */
string getFileName (bool isInFile) {
    string input;
    cout << "Enter the name of the " << (isInFile ? "input" : "output") << " file: ";
    getline(cin, input);

    return input;
}