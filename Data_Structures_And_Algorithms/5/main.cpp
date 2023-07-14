#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

string findTheDigits(string x, string y) {
	string result;
    map<char, int> xNumbers;
    map<char, int> yNumbers;

    for (char c : x) {
        auto it = xNumbers.find(c);
        if (it != xNumbers.end()) {
            it->second++;
        } else {
            xNumbers.insert(make_pair(c, 1));
        }
    }
    for (char c : y) {
        auto it = yNumbers.find(c);
        if (it != yNumbers.end()) {
            it->second++;
        } else {
            yNumbers.insert(make_pair(c, 1));
        }
    }

    for (auto it = yNumbers.begin(); it != yNumbers.end(); it++) {
        if (it->second > xNumbers.find(it->first)->second) {
            int loop = it->second - xNumbers.find(it->first)->second;
            for (int i = 0; i < loop; i++) {
                result += it->first;
            }
        }
    }
	return result;
}

int main() {
    string result = "";
    result = findTheDigits("8", "98887");
    //findTheDigits("8888888", "56981234");
    cout << result << endl;
    return 0;
}