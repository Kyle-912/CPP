// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int option = std::atoi(argv[1]);

    if (option == 1)
    {
        std::cout << "Option 1 selected. Hello!" << std::endl;
    }
    else if (option == 2)
    {
        std::cout << "Option 2 selected. World!" << std::endl;
    }

    return 0;
}
