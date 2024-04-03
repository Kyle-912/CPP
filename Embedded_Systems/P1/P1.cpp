// “On my honor, I have neither given nor received any unauthorized aid on this assignment

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int step = 0;
vector<vector<string>> INM;
vector<string> INB;
vector<string> AIB;
vector<string> LIB;
vector<string> ADB;
vector<vector<string>> REB;
vector<vector<string>> RGF;
vector<vector<string>> DAM;
ofstream outFile("simulation.txt");

bool readFile(const string &filename, vector<vector<string>> &data)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    string line;
    while (getline(file, line))
    {
        vector<string> fields;
        stringstream ss(line.substr(1, line.size() - 2));
        string field;
        while (getline(ss, field, ','))
        {
            fields.push_back(field);
        }
        data.push_back(fields);
    }

    file.close();
    return true;
}

void printStep()
{
    if (step != 0)
    {
        outFile << "\n\n";
    }

    outFile << "STEP ";
    outFile << step << ":\nINM:";
    if (!INM.empty())
    {
        for (auto it = INM.begin(); it != INM.end(); ++it)
        {
            outFile << "<" << (*it)[0] << "," << (*it)[1] << "," << (*it)[2] << "," << (*it)[3] << ">";
            if (next(it) != INM.end())
            {
                outFile << ",";
            }
            else
            {
                outFile << "\nINB:";
            }
        }
    }
    else
    {
        outFile << "\nINB:";
    }

    if (!INB.empty())
    {
        outFile << "<" << INB[0] << "," << INB[1] << "," << INB[2] << "," << INB[3] << ">" << "\nAIB:";
    }
    else
    {
        outFile << "\nAIB:";
    }

    if (!AIB.empty())
    {
        outFile << "<" << AIB[0] << "," << AIB[1] << "," << AIB[2] << "," << AIB[3] << ">" << "\nLIB:";
    }
    else
    {
        outFile << "\nLIB:";
    }

    if (!LIB.empty())
    {
        outFile << "<" << LIB[0] << "," << LIB[1] << "," << LIB[2] << "," << LIB[3] << ">" << "\nADB:";
    }
    else
    {
        outFile << "\nADB:";
    }

    if (!ADB.empty())
    {
        outFile << "<" << ADB[0] << "," << ADB[1] << ">" << "\nREB:";
    }
    else
    {
        outFile << "\nREB:";
    }

    if (!REB.empty())
    {
        for (auto it = REB.begin(); it != REB.end(); ++it)
        {
            outFile << "<" << (*it)[0] << "," << (*it)[1] << ">";
            if (next(it) != REB.end())
            {
                outFile << ",";
            }
            else
            {
                outFile << "\nRGF:";
            }
        }
    }
    else
    {
        outFile << "\nRGF:";
    }

    for (auto it = RGF.begin(); it != RGF.end(); ++it)
    {
        outFile << "<" << (*it)[0] << "," << (*it)[1] << ">";
        if (next(it) != RGF.end())
        {
            outFile << ",";
        }
        else
        {
            outFile << "\nDAM:";
        }
    }

    for (auto it = DAM.begin(); it != DAM.end(); ++it)
    {
        outFile << "<" << (*it)[0] << "," << (*it)[1] << ">";
        if (next(it) != DAM.end())
        {
            outFile << ",";
        }
    }
}

int main()
{
    if (!outFile.is_open())
        return 1;

    if (!readFile("instructions.txt", INM))
        return 1;

    if (!readFile("registers.txt", RGF))
        return 1;

    if (!readFile("datamemory.txt", DAM))
        return 1;

    printStep();

    while (!INM.empty() || !INB.empty() || !AIB.empty() || !LIB.empty() || !ADB.empty() || !REB.empty())
    {
        step++;

        vector<string> tempINB;
        vector<string> tempAIB;
        vector<string> tempLIB;
        vector<string> tempADB;
        vector<vector<string>> tempREB = REB;
        vector<vector<string>> tempRGF = RGF;

        if (!INM.empty()) // DECODE/READ
        {
            tempINB = INM[0];
            INM.erase(INM.begin());
            tempINB[2] = RGF[stoi(tempINB[2].substr(1))][1];
            tempINB[3] = RGF[stoi(tempINB[3].substr(1))][1];
        }

        if (!INB.empty())
        {
            if (INB[0] != "LD") // ISSUE1
            {
                tempAIB = INB;
            }
            else // ISSUE2
            {
                tempLIB = INB;
            }
        }

        if (!ADB.empty()) // LOAD
        {
            ADB[1] = DAM[stoi(ADB[1])][1];
            tempREB.push_back(ADB);
        }

        if (!AIB.empty()) // ALU
        {
            int resultNum = -1;
            if (AIB[0] == "ADD")
            {
                resultNum = stoi(AIB[2]) + stoi(AIB[3]);
            }
            else if (AIB[0] == "SUB")
            {
                resultNum = stoi(AIB[2]) - stoi(AIB[3]);
            }
            else if (AIB[0] == "AND")
            {
                resultNum = stoi(AIB[2]) & stoi(AIB[3]);
            }
            else if (AIB[0] == "OR")
            {
                resultNum = stoi(AIB[2]) | stoi(AIB[3]);
            }

            vector<string> result;
            result.push_back(AIB[1]);
            result.push_back(to_string(resultNum));

            tempREB.push_back(result);
        }

        if (!LIB.empty()) // ADDR
        {
            string addr = to_string(stoi(LIB[2]) + stoi(LIB[3]));
            vector<string> toLoad;
            toLoad.push_back(LIB[1]);
            toLoad.push_back(addr);
            tempADB = toLoad;
        }

        if (!REB.empty()) // WRITE
        {
            tempRGF[stoi(REB[0][0].substr(1))][1] = REB[0][1];
            tempREB.erase(tempREB.begin());
        }

        INB = tempINB;
        AIB = tempAIB;
        LIB = tempLIB;
        ADB = tempADB;
        REB = tempREB;
        RGF = tempRGF;

        printStep();
    }

    outFile.close();

    return 0;
}