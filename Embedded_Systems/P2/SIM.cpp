// “On my honor, I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

void compression()
{
    vector<string> instructions;

    ifstream file("original.txt");
    if (file.is_open())
    {
        string instruction;
        while (getline(file, instruction))
        {
            instructions.push_back(instruction);
        }
        file.close();

        cout << "Contents of original.txt:" << endl;
        for (const auto &r : instructions)
        {
            cout << r << endl;
        }
    }

    vector<int> dictionaryIndices;
    unordered_map<string, int> counts;

    // Count occurrences of each string
    for (const string& instruction : instructions) {
        counts[instruction]++;
    }

    // Create a vector of pairs to store the counts and strings
    vector<pair<int, string>> countStringPairs;

    // Populate the vector of pairs
    for (const auto& pair : counts) {
        countStringPairs.push_back(make_pair(pair.second, pair.first));
    }

    // Sort the vector of pairs in descending order based on counts
    sort(countStringPairs.begin(), countStringPairs.end(), greater<pair<int, string>>());

    // Extract the top 16 strings
    vector<string> top16Strings;
    for (size_t i = 0; i < std::min<size_t>(16, countStringPairs.size()); ++i) {
        top16Strings.push_back(countStringPairs[i].second);
    }
    cout << "dictioanry" << endl;
    for (const auto &r : top16Strings)
    {
        cout << r << endl;
    }
}

void decompression()
{
    string compressedInstructions;
    vector<string> dictionary;

    ifstream file("compressed.txt");
    if (file.is_open())
    {
        string line;
        bool isDictionary = false;
        while (getline(file, line))
        {
            if (line == "xxxx")
            {
                isDictionary = true;
                continue;
            }

            if (isDictionary)
            {
                dictionary.push_back(line);
            }
            else
            {
                compressedInstructions += line;
            }
        }
        file.close();

        cout << "Contents of compressed.txt:" << endl;
        for (size_t i = 0; i < compressedInstructions.length(); i += 32)
        {
            cout << compressedInstructions.substr(i, 32) << endl;
        }
        cout << "xxxx" << endl;
        for (const auto &r : dictionary)
        {
            cout << r << endl;
        }
    }


}

int main(int argc, char *argv[])
{
    int selection = atoi(argv[1]);
    switch (selection)
    {
    case 1:
        compression();
        break;

    case 2:
        decompression();
        break;
    }

    return 0;
}
