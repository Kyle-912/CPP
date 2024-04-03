// “On my honor, I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bitset>

using namespace std;

void compression()
{
    vector<string> instructions;
    vector<string> dictionaryEntries;

    ifstream file("original.txt");
    if (file.is_open())
    {
        string instruction;
        while (getline(file, instruction))
        {
            instructions.push_back(instruction);
        }
        file.close();
    }

    unordered_map<string, int> counts;
    for (const string &instruction : instructions)
    {
        counts[instruction]++;
    }
    vector<pair<int, string>> countsVector;
    for (const auto &pair : counts)
    {
        countsVector.push_back(make_pair(pair.second, pair.first));
    }
    sort(countsVector.begin(), countsVector.end(), [&](const pair<int, string> &a, const pair<int, string> &b)
         {
        if (a.first != b.first) {
            return a.first > b.first;
        } else {
            auto indexA = find(instructions.begin(), instructions.end(), a.second);
            auto indexB = find(instructions.begin(), instructions.end(), b.second);
            return distance(instructions.begin(), indexA) < distance(instructions.begin(), indexB);
        } });
    for (size_t i = 0; i < min<size_t>(16, countsVector.size()); ++i)
    {
        dictionaryEntries.push_back(countsVector[i].second);
    }

    //Direct Matches
    for (size_t i = 0; i < instructions.size(); ++i)
    {
        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            if (instructions[i] == dictionaryEntries[j])
            {
                string directMatch = "111";
                for (int k = 3; k >= 0; --k)
                {
                    directMatch += ((j >> k) & 1) ? '1' : '0';
                }
                instructions[i] = directMatch;
                break;
            }
        }
    }

    bool mismatchFound = false;

    for (size_t i = 0; i < instructions.size(); ++i)
    {
        const string &instr = instructions[i];
        bool instructionMatched = false;

        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            const string &dict = dictionaryEntries[j];

            // Your existing code for matching instructions with dictionary entries

            // Check for bitmask mismatch
            bitset<4> bitmask;
            bool bitmaskMismatch = false;
            int bitmaskStartIndex = -1; // Initialize to an invalid value
            for (size_t k = 0; k < instr.length(); ++k)
            {
                if (instr[k] != dict[k])
                {
                    bitmask[k] = 1; // Set bit in bitmask
                    if (bitmaskStartIndex == -1)
                    {
                        bitmaskStartIndex = k; // Set start index if not set yet
                    }
                    else if (k - bitmaskStartIndex == 3)
                    {
                        // Found a 4-bit bitmask
                        bitmaskMismatch = true;
                        break;
                    }
                }
            }

            if (bitmaskMismatch)
            {
                // Found 4-bit bitmask mismatch
                string compressed = "010";
                // Add 5-bit representation of bitmask start index
                compressed += bitset<5>(bitmaskStartIndex).to_string();
                // Add 4-bit representation of bitmask
                compressed += bitmask.to_string();
                // Add 4-bit representation of dictionary index
                compressed += bitset<4>(j).to_string();
                instructions[i] = compressed;
                mismatchFound = true;
                break;
            }
        }
    }

    cout << "";
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

/*
Heirarchy:
    RLE - 3
    Direct Match - 4
    1-bit mismatch - 9
    2-bit consecutive mistmatches - 9
    4-bit consecutive mistmatches - 9
    bitmask - 13
    2-bit mismatches anywhere - 14

Compress with lowest indicy dictionary entry
MSB is location 0
*/