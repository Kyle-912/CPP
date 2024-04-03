// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void compression();
void decompression();

vector<string> instructions;

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
        // Vector to store each row as a string


        // Read the file line by line
        string row;
        while (getline(file, row))
        {
            // Store the row in the vector
            instructions.push_back(row);
        }

        // Close the file
        file.close();

        // Print the contents of the vector
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
        cout << "Contents of compressed.txt:" << endl;
        char c;
        while (file.get(c))
        {
            cout << c;
        }
        file.close();
    }
}
