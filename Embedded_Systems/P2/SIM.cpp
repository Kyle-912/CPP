// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int option = atoi(argv[1]);

    if (option == 1)
    {
        ifstream file("original.txt"); // Open the file for reading

        if (file.is_open())
        {
            cout << "Contents of original.txt:" << endl;
            char c;
            while (file.get(c)) // Read the file character by character
            {
                cout << c;
            }
            file.close(); // Close the file
        }
    }
    else if (option == 2)
    {
        ifstream file("compressed.txt"); // Open the file for reading

        if (file.is_open())
        {
            cout << "Contents of compressed.txt:" << endl;
            char c;
            while (file.get(c)) // Read the file character by character
            {
                cout << c;
            }
            file.close(); // Close the file
        }
    }

    return 0;
}
