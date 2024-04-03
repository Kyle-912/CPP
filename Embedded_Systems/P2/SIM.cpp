// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readFile(int selection);

int main(int argc, char *argv[])
{
    int selection = atoi(argv[1]);
    switch (selection)
    {
    case 1:
        /* code */
        break;
    
    default:
        break;
    }
    readFile(selection);

    return 0;
}

void readFile(int selection)
{
    if (selection == 1)
    {
        ifstream file("original.txt");

        if (file.is_open())
        {
            cout << "Contents of original.txt:" << endl;
            char c;
            while (file.get(c))
            {
                cout << c;
            }
            file.close();
        }
    }
    else if (selection == 2)
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
}
