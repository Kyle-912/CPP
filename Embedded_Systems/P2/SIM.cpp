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
    vector<string> compressedInstructions;

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

    // Direct Matches
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

    // Consecutive Mismatches Handling
    for (size_t i = 0; i < instructions.size(); ++i)
    {
        const string &instr = instructions[i];
        string consecutiveMismatchEncoding = "";
        if (instructions[i].size() != 32)
        {
            continue;
        }
        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            const string &dict = dictionaryEntries[j];
            int consecutiveMismatchCount = 0;
            int totalMismatchCount = 0;
            size_t mismatchStartIndex = 0;
            for (size_t k = 0; k < instr.size(); ++k)
            {
                if (instr[k] != dict[k])
                {
                    ++consecutiveMismatchCount;
                    ++totalMismatchCount;

                    if (consecutiveMismatchCount > 4 || totalMismatchCount != consecutiveMismatchCount)
                    {
                        consecutiveMismatchEncoding = "";
                        break;
                    }

                    if (consecutiveMismatchCount == 1)
                    {
                        mismatchStartIndex = k;
                    }
                }
                else
                {
                    consecutiveMismatchCount = 0;
                }

                if (consecutiveMismatchCount == 1)
                {
                    // Single-bit mismatch
                    consecutiveMismatchEncoding = "011";
                }
                else if (consecutiveMismatchCount == 2)
                {
                    // Two-bit consecutive mismatch
                    consecutiveMismatchEncoding = "100";
                }
                else if (consecutiveMismatchCount == 4)
                {
                    // Four-bit consecutive mismatch
                    consecutiveMismatchEncoding = "101";
                }
                else if (consecutiveMismatchCount == 3)
                {
                    consecutiveMismatchEncoding = "";
                }

                if (consecutiveMismatchEncoding.size() != 0 && consecutiveMismatchCount != 0)
                {
                    consecutiveMismatchEncoding += bitset<5>(mismatchStartIndex).to_string();
                    consecutiveMismatchEncoding += bitset<4>(j).to_string();
                }

                if (k == 31 && consecutiveMismatchEncoding.size() != 0)
                {
                    instructions[i] = consecutiveMismatchEncoding;
                    break;
                }
            }
        }
    }

    // Bitmask Handling
    for (size_t i = 0; i < instructions.size(); ++i)
    {
        const string &instr = instructions[i];
        string encodedInstruction = "";

        if (instr.size() != 32)
        {
            continue;
        }

        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            const string &dict = dictionaryEntries[j];

            for (size_t start = 0; start <= 28; ++start)
            {
                for (int mask = 8; mask <= 15; ++mask)
                {
                    bool matching = true;

                    string compressedInstruction = instr;

                    for (size_t k = 0; k < 4; ++k)
                    {
                        if (((instr[start + k] - '0') ^ ((mask >> (3 - k)) & 1)) != (dict[start + k] - '0'))
                        {
                            matching = false;
                            break;
                        }
                        else
                        {
                            compressedInstruction[start + k] = (dict[start + k] - '0') ? '1' : '0';
                        }
                    }

                    if (matching && compressedInstruction == dict)
                    {
                        encodedInstruction = "010";
                        encodedInstruction += bitset<5>(start).to_string();
                        encodedInstruction += bitset<4>(mask).to_string();
                        encodedInstruction += bitset<4>(j).to_string();
                        break;
                    }
                }

                if (!encodedInstruction.empty())
                {
                    break;
                }
            }

            if (!encodedInstruction.empty())
            {
                break;
            }
        }

        if (!encodedInstruction.empty())
        {
            instructions[i] = encodedInstruction;
        }
    }

    // 2 Mismatches Anywhere Handling
    for (size_t i = 0; i < instructions.size(); ++i)
    {
        const string &instr = instructions[i];
        string encodedInstruction = "";

        if (instr.size() != 32)
        {
            continue;
        }

        for (size_t j = 0; j < dictionaryEntries.size(); ++j)
        {
            const string &dict = dictionaryEntries[j];
            int mismatchCount = 0;
            size_t firstMismatchIndex = 0;
            size_t secondMismatchIndex = 0;

            for (size_t k = 0; k < instr.size(); ++k)
            {
                if (instr[k] != dict[k])
                {
                    mismatchCount++;
                    if (mismatchCount == 1)
                    {
                        firstMismatchIndex = k;
                    }
                    else if (mismatchCount == 2)
                    {
                        secondMismatchIndex = k;
                    }
                    else if (mismatchCount > 2)
                    {
                        break;
                    }
                }
            }

            if (mismatchCount == 2)
            {
                encodedInstruction = "110";
                encodedInstruction += bitset<5>(firstMismatchIndex).to_string();
                encodedInstruction += bitset<5>(secondMismatchIndex).to_string();
                encodedInstruction += bitset<4>(j).to_string();
                break;
            }
        }

        if (!encodedInstruction.empty())
        {
            instructions[i] = encodedInstruction;
        }
    }

    // Original Binaries Handling
    for (size_t i = 0; i < instructions.size(); ++i)
    {
        if (instructions[i].size() == 32)
        {
            instructions[i] = "000" + instructions[i];
        }
    }

    // RLE Handling
    int consecutiveCount = 1;                    // Initialize consecutive count
    string currentInstruction = instructions[0]; // Initialize current instruction
    for (size_t i = 1; i < instructions.size(); ++i)
    {
        if (instructions[i] == currentInstruction)
        {
            // Increase consecutive count if instruction is the same as the previous one
            consecutiveCount++;
        }
        else
        {
            // If consecutive repetitions were found
            if (consecutiveCount > 1)
            {
                // Apply RLE compression for up to 8 repetitions
                while (consecutiveCount > 8)
                {
                    string rleEncodedInstruction = "001";                                         // Start with RLE indicator
                    int rleCount = 7;                                                             // RLE count (maximum 8 repetitions - 1)
                    rleEncodedInstruction += bitset<3>(rleCount).to_string();                     // Add RLE count as 3 bits
                    compressedInstructions.push_back(rleEncodedInstruction + currentInstruction); // Store RLE compressed instruction
                    consecutiveCount -= 7;                                                        // Update consecutive count
                }
                // Handle remaining repetitions (up to 8)
                string rleEncodedInstruction = "001";                                         // Start with RLE indicator
                int rleCount = consecutiveCount - 1;                                          // Calculate RLE count excluding the first occurrence
                rleEncodedInstruction += bitset<3>(rleCount).to_string();                     // Add RLE count as 3 bits
                compressedInstructions.push_back(rleEncodedInstruction + currentInstruction); // Store RLE compressed instruction
            }
            else
            {
                // If no consecutive repetitions, add the current instruction as is
                compressedInstructions.push_back(currentInstruction);
            }
            // Update current instruction and reset consecutive count
            currentInstruction = instructions[i];
            consecutiveCount = 1;
        }
    }

    // Handle the last instruction
    if (consecutiveCount > 1)
    {
        // Apply RLE compression for up to 8 repetitions
        while (consecutiveCount > 8)
        {
            string rleEncodedInstruction = "001";                                         // Start with RLE indicator
            int rleCount = 7;                                                             // RLE count (maximum 8 repetitions - 1)
            rleEncodedInstruction += bitset<3>(rleCount).to_string();                     // Add RLE count as 3 bits
            compressedInstructions.push_back(rleEncodedInstruction + currentInstruction); // Store RLE compressed instruction
            consecutiveCount -= 7;                                                        // Update consecutive count
        }
        // Handle remaining repetitions (up to 8)
        string rleEncodedInstruction = "001";                                         // Start with RLE indicator
        int rleCount = consecutiveCount - 1;                                          // Calculate RLE count excluding the first occurrence
        rleEncodedInstruction += bitset<3>(rleCount).to_string();                     // Add RLE count as 3 bits
        compressedInstructions.push_back(rleEncodedInstruction + currentInstruction); // Store RLE compressed instruction
    }
    else
    {
        compressedInstructions.push_back(currentInstruction);
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