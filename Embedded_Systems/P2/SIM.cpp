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
        while (getline(file, line))
        {
            if (line == "xxxx")
            {
                break;
            }
            compressedInstructions += line;
        }
        file.close();

        cout << "Contents of compressed.txt:" << endl;
        cout << compressedInstructions << endl;
        cout << "xxxx" << endl;
        for (const auto &r : dictionary)
        {
            cout << r << endl;
        }
    }
}
