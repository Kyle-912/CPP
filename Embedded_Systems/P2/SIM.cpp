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
    else if (option == 2)
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

    return 0;
}
