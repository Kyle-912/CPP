#include <iostream>
#include <vector>
#include <queue>
#include <array>
using namespace std;

int traverse(vector<string> &graph)
{
	queue<pair<int, int>> q;
    queue<int> pathLength;
    bool visted [graph.size()][graph[0].length()];
    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[0].length(); ++j)
        {
            visted[i][j] = false;
        }
    }
    q.push(make_pair(0, 0));
    pathLength.push(0);

    while(!q.empty())
    {
        visted[q.front().first][q.front().second] = true;
        if (graph[q.front().first][q.front().second] != 't')
        {
            if (q.front().first + 1 < graph.size()) //if down 1 exists
            {
                if (graph[q.front().first + 1][q.front().second] != '#' && !visted[q.front().first + 1][q.front().second]) //if down 1 isn't a #, and hasn't been visited
                {
                    q.push(make_pair(q.front().first + 1, q.front().second));
                    pathLength.push(pathLength.front() + 1);
                }
            }
            if (q.front().first - 1 >= 0) //if up 1 exists
            {
                if (graph[q.front().first - 1][q.front().second] != '#' && !visted[q.front().first - 1][q.front().second]) //if up 1 isn't a #, and hasn't been visited
                {
                    q.push(make_pair(q.front().first - 1, q.front().second));
                    pathLength.push(pathLength.front() + 1);
                }
            }
            if (q.front().second + 1 < graph[0].length()) //if right 1 exists
            {
                if (graph[q.front().first][q.front().second + 1] != '#' && !visted[q.front().first][q.front().second + 1]) //if right 1 isn't a #, and hasn't been visited
                {
                    q.push(make_pair(q.front().first, q.front().second + 1));
                    pathLength.push(pathLength.front() + 1);
                }
            }
            if (q.front().second - 1 >= 0) //if left 1 exists
            {
                if (graph[q.front().first][q.front().second - 1] != '#' && !visted[q.front().first][q.front().second - 1]) //if left 1 isn't a #, and hasn't been visited
                {
                    q.push(make_pair(q.front().first, q.front().second - 1));
                    pathLength.push(pathLength.front() + 1);
                }
            }
            q.pop();
            pathLength.pop();
        } else
        {
            return pathLength.front();
        }
    }
	return -1;
}

int main()
{
    vector<string> graph;
    graph.push_back("s#.#.");
    graph.push_back(".#...");
    graph.push_back("...#t");

    cout << traverse(graph);
}