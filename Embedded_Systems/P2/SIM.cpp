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

    ifstream inFile("original.txt");
    if (inFile.is_open())
    {
        string instruction;
        while (getline(inFile, instruction))
        {
            instructions.push_back(instruction);
        }
        inFile.close();
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
    for (size_t i = 0; i < instructions.size();)
    {
        string instruction = instructions[i];
        int consecutiveRepetitions = 1;

        while (i + consecutiveRepetitions < instructions.size() && instructions[i + consecutiveRepetitions] == instruction && consecutiveRepetitions < 9)
        {
            ++consecutiveRepetitions;
        }

        if (consecutiveRepetitions > 1)
        {
            compressedInstructions.push_back(instruction);

            int rleCount = consecutiveRepetitions - 1;
            string rleEncoding = "001" + bitset<3>(min(7, rleCount - 1)).to_string();
            compressedInstructions.push_back(rleEncoding);

            i += consecutiveRepetitions;
        }
        else
        {
            compressedInstructions.push_back(instruction);
            ++i;
        }
    }

    ofstream outFile("cout.txt");
    if (outFile.is_open())
    {
        string allInstructions = "";
        for (const string &instruction : compressedInstructions)
        {
            allInstructions += instruction;
        }
        size_t padding = 32 - (allInstructions.size() % 32);
        allInstructions += string(padding, '0');
        for (size_t i = 0; i < allInstructions.size(); i += 32)
        {
            string chunk = allInstructions.substr(i, 32);
            outFile << chunk << endl;
        }
        outFile << "xxxx" << endl;
        for (const string &entry : dictionaryEntries)
        {
            outFile << entry << endl;
        }
        outFile.close();
    }
}

void decompression()
{
    string compressedInstructions;
    vector<string> dictionary;

    ifstream inFile("compressed.txt");
    if (inFile.is_open())
    {
        string line;
        bool isDictionary = false;
        while (getline(inFile, line))
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
        inFile.close();

        ofstream outFile("dout.txt");
        if (outFile.is_open())
        {
            int ins = 0;
            while (ins < compressedInstructions.length())
            {
                string code = compressedInstructions.substr(ins, 3);

                int numBits = 0;
                if (code == "000")
                    numBits = 32;
                else if (code == "001")
                    numBits = 3;
                else if (code == "010")
                    numBits = 13;
                else if (code == "011" || code == "100" || code == "101")
                    numBits = 9;
                else if (code == "110")
                    numBits = 14;
                else if (code == "111")
                    numBits = 4;

                ins += 3;
                string data = compressedInstructions.substr(ins, numBits);
                ins += numBits;

                if (code == "000")
                {
                    outFile << data << endl;
                }
                else if (code == "001")
                {

                }
                else if (code == "010")
                {
                    string location = data.substr(0,5);
                    string bitmask = data.substr(5, 4);
                    string index = data.substr(9,4);
                }
                else if (code == "011")
                {

                }
                else if (code == "100")
                {

                }
                else if (code == "101")
                {

                }
                else if (code == "110")
                {

                }
                else if (code == "111")
                {

                }
            }
            outFile.close();
        }

        cout << "";
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