// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int option = atoi(argv[1]);

    if (option == 1)
    {
        cout << "Option 1 selected. Hello!" << endl;
    }
    else if (option == 2)
    {
        cout << "Option 2 selected. World!" << endl;
    }

    return 0;
}
