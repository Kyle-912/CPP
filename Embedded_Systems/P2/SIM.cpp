// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <1|2>" << endl;
        return 1;
    }

    int option = atoi(argv[1]);

    if (option == 1)
    {
        cout << "Option 1 selected. Hello!" << endl;
    }
    else if (option == 2)
    {
        cout << "Option 2 selected. World!" << endl;
    }
    else
    {
        cerr << "Invalid option. Please provide either 1 or 2." << endl;
        return 1;
    }

    return 0;
}
