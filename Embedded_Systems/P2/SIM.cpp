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
        else
        {
            cerr << "Error opening file original.txt" << endl;
        }
    }
    else if (option == 2)
    {
        cout << "Option 2 selected. World!" << endl;
    }

    return 0;
}
