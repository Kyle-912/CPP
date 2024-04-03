// “I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <1|2>" << std::endl;
        return 1;
    }

    int option = std::atoi(argv[1]);

    if (option == 1)
    {
        std::cout << "Option 1 selected. Hello!" << std::endl;
    }
    else if (option == 2)
    {
        std::cout << "Option 2 selected. World!" << std::endl;
    }
    else
    {
        std::cerr << "Invalid option. Please provide either 1 or 2." << std::endl;
        return 1;
    }

    return 0;
}
