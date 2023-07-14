#include <array>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string> tableToList(vector<vector<string>> table);

int main() {
    vector<vector<string>> table;
    table.resize(2);
    table[0].resize(2);
    table[1].resize(2);
    table[0][0] = "test";
    table[0][1] = "ing";
    table[1][0] = "test";
    table[1][1] = "testtt";
    vector<string> list = tableToList(table);
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << endl;
    }
}

vector<string> tableToList(vector<vector<string>> table) {
    vector<string> list;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if (list.empty()) {
                list.push_back(table[i][j]);
            }
            else for (int k = 0; k < list.size(); k++) {
                if (table[i][j] == list[k]) {
                    break;
                }
                list.push_back(table[i][j]);
                break;
            }
        }
    }
    return list;
}
