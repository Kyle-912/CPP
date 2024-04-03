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

    for (size_t i = 0; i < instructions.size(); ++i)
    {
        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            const string &instr = instructions[i];
            const string &dict = dictionaryEntries[j];
            int mismatchCount = 0;
            int mismatchStart = -1;

            if (instr.length() != dict.length())
                continue; // Skip if lengths are different

            for (size_t k = 0; k < instr.length(); ++k)
            {
                if (instr[k] != dict[k])
                {
                    if (mismatchCount == 0)
                    {
                        mismatchStart = k; // Start of mismatch
                        mismatchCount++;
                    }
                    else if (k == mismatchStart + 1)
                    {
                        // Check for 2 consecutive bit mismatches
                        int consecutiveMismatchCount = 2; // Number of consecutive mismatches expected
                        for (size_t l = k + 1; l < instr.length(); ++l)
                        {
                            if (instr[l] != dict[l])
                            {
                                consecutiveMismatchCount--;
                                if (consecutiveMismatchCount == 0)
                                {
                                    // Replace instruction with "100" + 5-bit representation of mismatch start + 4-bit representation of dictionary index
                                    string indexRepresentation = "100";
                                    // Add 5-bit representation of mismatch start
                                    for (int m = 4; m >= 0; --m)
                                    {
                                        indexRepresentation += ((mismatchStart >> m) & 1) ? '1' : '0';
                                    }
                                    // Add 4-bit representation of dictionary index
                                    for (int m = 3; m >= 0; --m)
                                    {
                                        indexRepresentation += ((j >> m) & 1) ? '1' : '0';
                                    }
                                    instructions[i] = indexRepresentation;
                                    break; // Move to the next instruction
                                }
                            }
                            else
                            {
                                // Reset mismatchCount if the consecutive mismatch is broken
                                mismatchCount = 0;
                                break;
                            }
                        }
                    }
                    else
                    {
                        // Reset mismatchCount if the consecutive mismatch is broken
                        mismatchCount = 0;
                        break;
                    }
                }
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