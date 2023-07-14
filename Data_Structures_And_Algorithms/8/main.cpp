#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Graph
{
private:
    map<string, pair<vector<string>, float>> adjacencyList;
    map<string, float> ranks;
public:
    void InsertUrl(string from, string to);
    void InitializeRanks();
    void PageRank(int n);
};

void Graph::PageRank(int n) // prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places
{
    for (int i = 0; i < n - 1; i++) //perform operation p times
    {
        map<string, float> tempRanks = ranks;
        for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) //loop through each from for the value to compare against
        {
            float sum = 0.0;
            for (auto iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++) //loop through each from again to check their to's
            {
                for (int i = 0; i < iter->second.first.size(); i++) //in each from, loop through what they point to
                {
                    if (iter->second.first[i] == it->first) //if the from being calculated is encountered, multiply by the associated rank from the table and add to sum
                    {
                        sum += iter->second.second * ranks[iter->first];
                    }
                }
            }
            tempRanks[it->first] = sum;
        }
        ranks = tempRanks; //update ranks table
    }
    for (int i = 0; i < adjacencyList.size(); i++) //loop enough times to print all values
    {
        cout << ranks.begin()->first << " " << fixed << setprecision(2) << ranks.begin()->second << endl; //use begin() to find the smallest element
        ranks.erase(ranks.begin()->first); //remove smallest element from ranks map
    }
}

void Graph::InsertUrl(string from, string to)
{
    adjacencyList[from].first.push_back(to); //add url to map
    adjacencyList[from].second = 0; //default rank is 0
    if (adjacencyList.find(to) == adjacencyList.end())
    {
        adjacencyList[to] = {}; //if to isn't a key yet, add it to the map
        ranks[to] = {};
    }
    ranks[from] = 0;
}

void Graph::InitializeRanks()
{
    for (auto it = ranks.begin(); it != ranks.end(); it++) {
        it->second = 1.0 / adjacencyList.size(); //initialize ranks table with 1/|V|
    }

    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)
    {
        it->second.second = 1.0 / it->second.first.size(); //initialize ranks in adjacency list with 1/out degree
    }
}

int main()
{
    Graph graph;
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    for(int i = 0; i < no_of_lines; i++)
    {
        cin >> from;
        cin >> to;
        graph.InsertUrl(from, to);
    }
    graph.InitializeRanks();
    graph.PageRank(power_iterations);
    return 0;
}