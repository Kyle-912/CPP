#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int GetBlockSize (vector<string> graph, map<pair<int, int>, bool> visited, int i, int j, int max)
{
    if ((j - 1) > 0) //left exists
    {
        if (!visited[make_pair(i, j - 1)] && graph[i][j - 1] == 1)
        {
            max += 1;
            visited.emplace(make_pair(i, j - 1), true);
            max = GetBlockSize (graph, visited, i, j - 1, max);
        }
    }
    if ((j + 1) < graph[i].length ()) //right exists
    {
        if (!visited[make_pair(i, j + 1)] && graph[i][j + 1] == 1)
        {
            max += 1;
            visited.emplace(make_pair(i, j + 1), true);
            max = GetBlockSize (graph, visited, i, j + 1, max);
        }
    }
    if ((i - 1) > 0) //up exists
    {
        if (!visited[make_pair(i - 1, j)] && graph[i - 1][j] == 1) {
            max += 1;
            visited.emplace(make_pair(i - 1, j), true);
            max = GetBlockSize(graph, visited, i - 1, j, max);
        }
    }
    if ((i + 1) < graph.size ()) //down exists
    {
        if (!visited[make_pair(i + 1, j)] && graph[i + 1][j] == 1) {
            max += 1;
            visited.emplace(make_pair(i + 1, j), true);
            max = GetBlockSize(graph, visited, i + 1, j, max);
        }
    }
    return max;
}

vector<string> GraphBuilder (void)
{
    vector<string> graph;
    graph.push_back("01011");
    graph.push_back ("00001");
    graph.push_back("10000");
    graph.push_back("11011");
    graph.push_back ("11011");
    return graph;
}

int LargestBlock (void)
{
    vector<string> graph = GraphBuilder();
    map<pair<int, int>, bool> visited;
    int max = 0;

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].length(); i++) {
            visited.emplace(make_pair(i, j), false);
            if (graph[i][j] == '1') {
                int temp = GetBlockSize(graph, visited, i, j, 1);
                if (temp > max) {
                    max = temp;
                }
            }
        }
    }
    return max;
}

int main()
{
    int max = LargestBlock();
    cout << max;
    return 0;
}