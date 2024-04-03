// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readFile(int compression_decompression);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <1|2>" << endl;
        return 1;
    }

    int compression_decompression = atoi(argv[1]);
    readFile(compression_decompression);

    return 0;
}

void readFile(int compression_decompression)
{
    if (compression_decompression == 1)
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
    else if (compression_decompression == 2)
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

