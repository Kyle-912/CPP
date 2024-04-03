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

    bool foundMismatch = false;

    for (size_t i = 0; i < instructions.size(); ++i)
    {
        const string &instr = instructions[i];
        bool mismatchFound = false;
        int mismatchIndex1 = -1;
        int mismatchIndex2 = -1;
        int dictionaryIndex = -1;

        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            const string &dict = dictionaryEntries[j];
            int mismatchCount = 0;
            int mismatchStart = -1;

            if (instr.length() != dict.length())
                continue; // Skip if lengths are different

            for (size_t k = 0; k < instr.length(); ++k)
            {
                if (instr[k] != dict[k])
                {
                    if (mismatchStart == -1)
                    {
                        mismatchStart = k;
                    }
                    mismatchCount++;
                    if (mismatchCount > 4)
                    {
                        // More than 4 mismatches, no need to continue
                        break;
                    }
                    if (mismatchCount == 1)
                    {
                        mismatchIndex1 = k;
                        dictionaryIndex = j;
                    }
                    else if (mismatchCount == 2 && k - mismatchIndex1 == 1)
                    {
                        mismatchIndex2 = k;
                    }
                }
            }

            if (mismatchCount == 1)
            {
                // Found a 1-bit mismatch
                string compressed = "011";
                // Add 5-bit representation of mismatch index
                compressed += bitset<5>(mismatchIndex1).to_string();
                // Add 4-bit representation of dictionary index
                compressed += bitset<4>(dictionaryIndex).to_string();
                instructions[i] = compressed;
                mismatchFound = true;
                break;
            }
            else if (mismatchCount == 2 && mismatchIndex2 - mismatchIndex1 == 1)
            {
                // Found two consecutive bit mismatches
                string compressed = "100";
                // Add 5-bit representation of mismatch or start of mismatch
                compressed += bitset<5>(mismatchStart).to_string();
                // Add 4-bit representation of dictionary index
                compressed += bitset<4>(dictionaryIndex).to_string();
                instructions[i] = compressed;
                mismatchFound = true;
                break;
            }
        }

        if (!mismatchFound && mismatchIndex1 != -1 && mismatchIndex2 != -1)
        {
            // Found a 2 bit mismatch anywhere
            string compressed = "110";
            // Add 5-bit representation of first mismatch index
            compressed += bitset<5>(mismatchIndex1).to_string();
            // Add 5-bit representation of second mismatch index
            compressed += bitset<5>(mismatchIndex2).to_string();
            // Add 4-bit representation of dictionary index
            compressed += bitset<4>(dictionaryIndex).to_string();
            instructions[i] = compressed;
            mismatchFound = true;
            break;
        }
    }

    if (!foundMismatch)
    {
        cout << "nothing" << endl;
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