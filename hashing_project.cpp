// hashing_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

constexpr unsigned long HASH_TABLE_SIZE = 127031UL;

typedef struct HashItem 
{
    int flag; // 0 : empty value, 1 : have value 
    string value;

    HashItem() : flag(0), value() {}; // constructor and initialize default value
};

unsigned long createHashKey(const string word) {
    unsigned long key = 0;
    for (int i = 0; i < word.length(); i++) {
        key += (unsigned long)pow(word[i], 3);
    }
    return key % HASH_TABLE_SIZE;
}

void quadraticHashing(const string word, HashItem hashTable[]) {
    unsigned long hash = createHashKey(word);

    if (hashTable[hash].flag) {
        // hash has value
        // find next hash
        for (unsigned long j = 1; j < HASH_TABLE_SIZE; j++) {
            hash = ((j * j) + hash) % HASH_TABLE_SIZE;
            if (!hashTable[hash].flag) {
                hashTable[hash].value = word;
                hashTable[hash].flag = 1;
                break;
            }
        }
    }
    else {
        // empty hash
        hashTable[hash].value = word;
        hashTable[hash].flag = 1;
    }
}

void displayFound(const string word) {
    cout << "FOUND: " << word << endl << endl << endl;
}

void displayNotFound() {
    cout << "NOT FOUND.\n\n\n";
}

bool search(const string word,const HashItem hashTable[]) {
    unsigned long hash = createHashKey(word);

    if (hashTable[hash].flag) { // flag == 1, have value
        if (word == hashTable[hash].value) { // check word is hash'value
            displayFound(word);
            return true;
        }
        else 
        {
            // have collistion
            unsigned long j = 1;
            do {
                cout << "Collision: " << hashTable[hash].value << endl;

                // next hash value
                hash = ((j * j) + hash) % HASH_TABLE_SIZE;
                if (! hashTable[hash].flag) { // flag == 0, empty
                    displayNotFound();
                    return false;
                }
                else if (word == hashTable[hash].value) {
                    // hash has value so compare
                    displayFound(word);
                    return true;
                }
                else {
                    j++;
                }

            } while (1);
        }
    }
    
    displayNotFound();
    return false;
}

bool initDict(HashItem hashTable[]) {
    ifstream inFile;

    inFile.open("dict.txt");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            quadraticHashing(line, hashTable);
        }
        inFile.close();
    }
    else {
        cout << "Unable to open file" << endl;
        return false;
    }
    return true;
}

int main()
{
    HashItem* hashTable = new HashItem[HASH_TABLE_SIZE];
    bool res = initDict(hashTable);
    if (res) {

        while (1) {

            string searchWord;
            cout << "Enter a word: ";
            if (getline(cin, searchWord) && !searchWord.empty()) {

                search(searchWord, hashTable);
            }
            else {
                break;
            }
        }
    }

    delete[] hashTable;
    return (res) ? 0 : 1;
}
