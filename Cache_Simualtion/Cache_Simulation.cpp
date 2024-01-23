#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <cmath>
#include <array>
using namespace std;

vector<string> ReadFile(string fileName);
vector<string> HexToBinary(vector<string> addresses);
int BinaryToDecimal(string binary);

int main()
{
    cout << "Kyle Thompson" << endl;

    for (int run = 0; run < 54; run++)
    {
        // User-set values
        string inFile = "gcc.trace";
        int block_lineSizeByte = 64;
        int memoryAddressSizeBits = 32;

        // Set per run
        string associativity = "";     // direct | set | fully
        string replacementPolicy = ""; // FIFO | LRU
        int cacheSizeByte = 0;
        int n_way = 1; // only used if associativity is "set"
        switch (run)
        {
        case 0:
            associativity = "direct";
            cacheSizeByte = 512;
            break;
        case 1:
            associativity = "direct";
            cacheSizeByte = 1024;
            break;
        case 2:
            associativity = "direct";
            cacheSizeByte = 2048;
            break;
        case 3:
            associativity = "direct";
            cacheSizeByte = 4096;
            break;
        case 4:
            associativity = "direct";
            cacheSizeByte = 8192;
            break;
        case 5:
            associativity = "direct";
            cacheSizeByte = 16384;
            break;
        case 6:
            associativity = "fully";
            replacementPolicy = "FIFO";
            cacheSizeByte = 512;
            break;
        case 7:
            associativity = "fully";
            replacementPolicy = "FIFO";
            cacheSizeByte = 1024;
            break;
        case 8:
            associativity = "fully";
            replacementPolicy = "FIFO";
            cacheSizeByte = 2048;
            break;
        case 9:
            associativity = "fully";
            replacementPolicy = "FIFO";
            cacheSizeByte = 4096;
            break;
        case 10:
            associativity = "fully";
            replacementPolicy = "FIFO";
            cacheSizeByte = 8192;
            break;
        case 11:
            associativity = "fully";
            replacementPolicy = "FIFO";
            cacheSizeByte = 16384;
            break;
        case 12:
            associativity = "fully";
            replacementPolicy = "LRU";
            cacheSizeByte = 512;
            break;
        case 13:
            associativity = "fully";
            replacementPolicy = "LRU";
            cacheSizeByte = 1024;
            break;
        case 14:
            associativity = "fully";
            replacementPolicy = "LRU";
            cacheSizeByte = 2048;
            break;
        case 15:
            associativity = "fully";
            replacementPolicy = "LRU";
            cacheSizeByte = 4096;
            break;
        case 16:
            associativity = "fully";
            replacementPolicy = "LRU";
            cacheSizeByte = 8192;
            break;
        case 17:
            associativity = "fully";
            replacementPolicy = "LRU";
            cacheSizeByte = 16384;
            break;
        case 18:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 512;
            n_way = 2;
            break;
        case 19:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 1024;
            n_way = 2;
            break;
        case 20:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 2048;
            n_way = 2;
            break;
        case 21:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 4096;
            n_way = 2;
            break;
        case 22:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 8192;
            n_way = 2;
            break;
        case 23:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 16384;
            n_way = 2;
            break;
        case 24:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 512;
            n_way = 2;
            break;
        case 25:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 1024;
            n_way = 2;
            break;
        case 26:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 2048;
            n_way = 2;
            break;
        case 27:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 4096;
            n_way = 2;
            break;
        case 28:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 8192;
            n_way = 2;
            break;
        case 29:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 16384;
            n_way = 2;
            break;
        case 30:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 512;
            n_way = 4;
            break;
        case 31:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 1024;
            n_way = 4;
            break;
        case 32:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 2048;
            n_way = 4;
            break;
        case 33:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 4096;
            n_way = 4;
            break;
        case 34:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 8192;
            n_way = 4;
            break;
        case 35:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 16384;
            n_way = 4;
            break;
        case 36:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 512;
            n_way = 4;
            break;
        case 37:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 1024;
            n_way = 4;
            break;
        case 38:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 2048;
            n_way = 4;
            break;
        case 39:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 4096;
            n_way = 4;
            break;
        case 40:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 8192;
            n_way = 4;
            break;
        case 41:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 16384;
            n_way = 4;
            break;
        case 42:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 512;
            n_way = 8;
            break;
        case 43:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 1024;
            n_way = 8;
            break;
        case 44:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 2048;
            n_way = 8;
            break;
        case 45:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 4096;
            n_way = 8;
            break;
        case 46:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 8192;
            n_way = 8;
            break;
        case 47:
            associativity = "set";
            replacementPolicy = "FIFO";
            cacheSizeByte = 16384;
            n_way = 8;
            break;
        case 48:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 512;
            n_way = 8;
            break;
        case 49:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 1024;
            n_way = 8;
            break;
        case 50:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 2048;
            n_way = 8;
            break;
        case 51:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 4096;
            n_way = 8;
            break;
        case 52:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 8192;
            n_way = 8;
            break;
        case 53:
            associativity = "set";
            replacementPolicy = "LRU";
            cacheSizeByte = 16384;
            n_way = 8;
            break;
        default:
            break;
        }

        // Size calculations
        int numLines = cacheSizeByte / block_lineSizeByte;
        int numSets = cacheSizeByte / (block_lineSizeByte * n_way);
        int offsetSizeBits = log2(block_lineSizeByte);

        int set_lineSizeBits = 0;
        int tagSizeBits = 0;
        if (associativity == "direct")
        {
            set_lineSizeBits = log2(numLines);
            tagSizeBits = memoryAddressSizeBits - set_lineSizeBits - offsetSizeBits;
        }
        else if (associativity == "set")
        {
            set_lineSizeBits = log2(numSets);
            tagSizeBits = memoryAddressSizeBits - set_lineSizeBits - offsetSizeBits;
        }
        else if (associativity == "fully")
        {
            tagSizeBits = memoryAddressSizeBits - offsetSizeBits;
        }
        else
        {
            cout << "Invalid associativity type" << endl;
        }

        // Prep trace addresses and cache
        vector<string> addresses = HexToBinary(ReadFile(inFile));
        vector<vector<int>> cache;
        if (associativity == "direct")
        {
            for (int i = 0; i < numLines; i++)
            {
                cache.push_back({i, 0, 0});
            }
        }
        else if (associativity == "set")
        {
            for (int i = 0; i < numLines; i++)
            {
                cache.push_back({i / 2, 0, 0});
            }
        }
        else if (associativity == "fully")
        {
            for (int i = 0; i < numLines; i++)
            {
                cache.push_back({0, 0, 0});
            }
        }

        // Run cache simulation
        double hitCounter = 0;
        vector<int> orderAdded;
        for (auto address : addresses)
        {
            // Set fields
            string tagBinary = "";
            string set_lineBinary = "";
            for (int i = 0; i < tagSizeBits; i++)
            {
                tagBinary += address[i];
            }
            for (int i = tagSizeBits; i < tagSizeBits + set_lineSizeBits; i++)
            {
                set_lineBinary += address[i];
            }
            int tag = BinaryToDecimal(tagBinary);
            int set_line = BinaryToDecimal(set_lineBinary);

            // Input address to cache
            bool miss = 0;
            for (int i = 0; i < numLines; i++) // go through each line
            {
                if (cache[i][0] == set_line) // if the block can be placed here
                {
                    if (cache[i][1] == 0) // empty
                    {
                        cache[i][1] = tag;
                        cache[i][2] = 1;
                        miss = false;
                        orderAdded.push_back(i);
                        break;
                    }
                    else if (cache[i][1] == tag) // hit
                    {
                        cache[i][2] += 1;
                        hitCounter += 1;
                        miss = false;
                        break;
                    }
                    else // miss
                    {
                        if (associativity == "direct")
                        {
                            cache[i][1] = tag;
                            cache[i][2] = 1;
                            break;
                        }
                        else
                        {
                            miss = true;
                        }
                    }
                }
            }
            if (miss)
            {
                if (replacementPolicy == "FIFO")
                {
                    for (int i = 0; i < orderAdded.size(); i++) // go through the lines added in order
                    {
                        if (cache[orderAdded[i]][0] == set_line) // find the first added line in which the block can be placed
                        {
                            cache[orderAdded[i]][1] = tag;
                            cache[orderAdded[i]][2] = 1;

                            int temp = orderAdded[i];
                            for (int j = i; j < orderAdded.size() - 1; j++)
                            {
                                orderAdded[j] = orderAdded[j + 1];
                            }
                            orderAdded.back() = temp;

                            break;
                        }
                    }
                }
                else if (replacementPolicy == "LRU") // replace item with smallest counter
                {
                    int indexToReplace = 0;
                    int valueToBeat = INT_MAX;
                    for (int i = 0; i < numLines; i++) // go through each line
                    {
                        if (cache[i][0] == set_line) // if the block can be placed here
                        {
                            if (cache[i][2] < valueToBeat)
                            {
                                indexToReplace = i;
                                valueToBeat = cache[i][2];
                            }
                        }
                    }
                    cache[indexToReplace][1] = tag;
                    cache[indexToReplace][2] = 1;
                }
                else
                {
                    cout << "Invalid replacement policy" << endl;
                }
            }
        }
        cout << "Hit Rate for " << associativity << " " << replacementPolicy << " with a cache size of " << cacheSizeByte << " bytes is: " << hitCounter / addresses.size() << endl;
    }
    return 0;
}

vector<string> ReadFile(string fileName)
{
    vector<string> addresses;
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            string instruction = "";
            string loadOrStore = "";
            string removePrefix = "";
            string address = "";
            string numBytes = "";

            getline(inFile, instruction);
            if (instruction == "")
            {
                break;
            }

            istringstream instructionStream(instruction);
            getline(instructionStream, loadOrStore, ' ');
            getline(instructionStream, removePrefix, 'x');
            getline(instructionStream, address, ' ');
            getline(instructionStream, numBytes, ' ');

            addresses.push_back(address);
        }
    }
    else
    {
        cout << "File could not open" << endl;
    }

    return addresses;
}

vector<string> HexToBinary(vector<string> addressesHex)
{
    vector<string> addressesBinary;

    for (auto address : addressesHex)
    {
        string addressBinary = "";
        for (auto hexChar : address)
        {
            if (hexChar == '0')
            {
                addressBinary += "0000";
            }
            else if (hexChar == '1')
            {
                addressBinary += "0001";
            }
            else if (hexChar == '2')
            {
                addressBinary += "0010";
            }
            else if (hexChar == '3')
            {
                addressBinary += "0011";
            }
            else if (hexChar == '4')
            {
                addressBinary += "0100";
            }
            else if (hexChar == '5')
            {
                addressBinary += "0101";
            }
            else if (hexChar == '6')
            {
                addressBinary += "0110";
            }
            else if (hexChar == '7')
            {
                addressBinary += "0111";
            }
            else if (hexChar == '8')
            {
                addressBinary += "1000";
            }
            else if (hexChar == '9')
            {
                addressBinary += "1001";
            }
            else if (hexChar == 'A' || hexChar == 'a')
            {
                addressBinary += "1010";
            }
            else if (hexChar == 'B' || hexChar == 'b')
            {
                addressBinary += "1011";
            }
            else if (hexChar == 'C' || hexChar == 'c')
            {
                addressBinary += "1100";
            }
            else if (hexChar == 'D' || hexChar == 'd')
            {
                addressBinary += "1101";
            }
            else if (hexChar == 'E' || hexChar == 'e')
            {
                addressBinary += "1110";
            }
            else if (hexChar == 'F' || hexChar == 'f')
            {
                addressBinary += "1111";
            }
            else
            {
                cout << "Invalid character in address" << endl;
            }
        }
        addressesBinary.push_back(addressBinary);
    }

    return addressesBinary;
}

int BinaryToDecimal(string binary)
{
    int decimal = 0;

    int indexCounter = 0;
    for (int i = binary.length() - 1; i >= 0; i--)
    {
        if (binary[i] == '1')
        {
            decimal += pow(2, indexCounter);
        }
        indexCounter++;
    }

    return decimal;
}
