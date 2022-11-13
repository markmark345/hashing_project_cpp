// hashing_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

typedef struct HashItem
{
    vector<string> value;
};

long generateHash(const string word)
{
    long hash = 0;

    for (int i = 0; i < word.length(); i++)
    {
        hash += (long)pow(word[i], 3);
    }
    return hash % 127031;
}

int main()
{
    HashItem *hashTable = new HashItem[127031];
    ifstream inFile;
    string line;
    string searchWord;

    inFile.open("dict.txt");
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            hashTable[generateHash(line)].value.push_back(line);
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
        delete[] hashTable;
        exit(1);
    }

    while (1)
    {
        cout << "Enter a word: ";
        if (getline(cin, searchWord) && !searchWord.empty())
        {
            bool found = false;
            for (string s : hashTable[generateHash(searchWord)].value)
            {
                if (s == searchWord)
                {
                    cout << "FOUND: " << searchWord << endl
                         << endl
                         << endl;
                    found = true;
                    break;
                }
                else
                {
                    cout << "Collision: " << s << endl;
                }
            }
            if (!found)
                cout << "NOT FOUND.\n\n\n";
        }
        else
        {
            break;
        }
    }

    delete[] hashTable;
    return 0;
}
