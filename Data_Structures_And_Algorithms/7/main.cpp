#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph
{
   private:
      map<int, vector<pair<int,int>>> graph;

    public:
      void insertEdge(int from, int to, int weight);
      bool isEdge(int from, int to);
      int sumEdge(int from, int to);
      std::vector<int> getWeight(int from, int to);
      std::vector<int> getAdjacent(int vertex);
};

void Graph::insertEdge(int from, int to, int weight)
{
   graph[from].push_back(make_pair(to, weight));
   if (graph.find(to) == graph.end()) {
       graph[to] = {};
   }
}

bool Graph::isEdge(int from, int to)
{
    vector<pair<int, int>> v = graph[from];
    if (v.empty()) {
        return false;
    } else {
        for (pair<int, int> i : v) {
            if (i.first == to) {
                return true;
            }
        }
    }
    return false;
}

int Graph::sumEdge(int from, int to)
{
    int sum = 0;
    vector<pair<int, int>> v = graph[from];
    for (pair<int, int> i : v) {
        if (i.first == to) {
            sum += i.second;
        }
    }
    return sum;
}

vector<int> Graph::getWeight(int from, int to)
{
    vector<int> weights;
    vector<pair<int, int>> v = graph[from];
    for (pair<int, int> i : v) {
        if (i.first == to) {
            weights.push_back(i.second);
        }
    }
    return weights;
}

vector<int> Graph::getAdjacent(int vertex)
{
    vector<int> neighbors;
    vector<pair<int, int>> v = graph[vertex];
    for (pair<int, int> i : v) {
        neighbors.push_back(i.first);
    }
    return neighbors;
}

int main() {
    Graph graph;
    graph.insertEdge(0, 0, 10);
    graph.insertEdge(0, 1, 20);
    graph.insertEdge(0, 2, 30);
    graph.insertEdge(1, 2, 15);
    graph.insertEdge(0, 1, 15);
    bool isEdge = graph.isEdge(0, 0);
    if (isEdge) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    cout << graph.sumEdge(0, 1) << endl;
    vector<int> v1 = graph.getWeight(0, 1);
    for (int i : v1) {
        cout << i << endl;
    }
    vector<int> v2 = graph.getAdjacent(0);
    for (int i : v2) {
        cout << i << endl;
    }
    return 0;
}
