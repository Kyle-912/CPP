// “On my honor, I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void compression();
void decompression();

vector<string> instructions;
string compressedInstructions;
vector<string> dictionary;

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
    }

    return 0;
}

void compression()
{
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
}

void decompression()
{
    ifstream file("compressed.txt");

    if (file.is_open())
    {
        string line;
        bool startStoring = false;
        while (getline(file, line))
        {
            if (line == "xxxx")
            {
                startStoring = true; // Set the flag to true after reading "xxxx"
                continue;            // Skip storing "xxxx" in the vector
            }

            if (startStoring)
            {
                instructions.push_back(line); // Store lines to the vector
            }
            else
            {
                compressedInstructions += line; // Concatenate lines before "xxxx"
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
