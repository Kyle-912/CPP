#include <iostream>
#include <sstream>
#include <vector>
#include "AVL.h"
using namespace std;

int main() {
    AVL avl = *new AVL;

    string numCommandsS = "";
    int numCommands = 0;
    getline(cin, numCommandsS);
    for (char c : numCommandsS) {
        if (!isdigit(c)) {
            cout << "First command must be number" << endl;
            getline(cin, numCommandsS);
            break;
        }
    }
    numCommands = stoi(numCommandsS);

    for (int i = 0; i < numCommands; i++) {
        string command = "";
        string name = "";
        string id = "";
        string line = "";
        string remainder = "";
        bool inQuotes = false;

        getline(cin, line);
        istringstream in(line);
        /*-----------------------------------------reading----------------------------------------------*/
        in >> command;
        if (command == "insert") {
            getline(in, name, '"');
            getline(in, name, '"');
            in >> id;
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "remove") {
            in >> id;
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "search") {
            in >> name;
            for (char c : name) {
                if (isdigit(c)) {
                    id = name;
                    name = "";
                    break;
                }
            }
            if (name[0] == '"' && name[name.length() - 1] == '"') {
                name.erase(0, 1);
                name.erase(name.length() - 1, 1);
                inQuotes = true;
            }
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "printInorder") {
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "printPreorder") {
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "printPostorder") {
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "printLevelCount") {
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        } else if (command == "removeInorder") {
            in >> id;
            while (!in.eof()) {
                string temp = "";
                in >> temp;
                remainder += temp;
            }
        }
        bool isAlpha = true;
        for (char c : name) {
            if (!isalpha(c)) {
                isAlpha = false;
            }
        }
        /*-----------------------------------------commands----------------------------------------------*/
        if (command == "insert" && id.length() == 8 && isAlpha && remainder.empty()) {
            int idNum = stoi(id);
            avl.insert(name, idNum);
        } else if (command == "remove" && id.length() == 8 && name.empty() && remainder.empty()) {
            int idNum = stoi(id);
            avl.remove(idNum);
        } else if (command == "search" && id.length() == 8 && name.empty() && remainder.empty()) {
            int idNum = stoi(id);
            avl.search(idNum);
        } else if (command == "search" && isAlpha && id.empty() && inQuotes && remainder.empty()) {
            vector<int> idsToPrint;
            vector<int>* ids = &idsToPrint;
            avl.search(name, ids);
            for (int j = 0; j < idsToPrint.size(); j++) {
                string print = to_string(idsToPrint[j]);
                while (print.length() < 8) {
                    print.insert(0,"0");
                }
                cout << print << endl;
            }
            if (idsToPrint.empty()) {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "printInorder" && name.empty() && id.empty() && remainder.empty()) {
            vector<string> namesToPrint;
            vector<string>* names = &namesToPrint;
            avl.printInorder(names);
            if (!names->empty()) {
                for (int j = 0; j < names->size() - 1; j++) {
                    cout << namesToPrint[j] << ", ";
                }
                cout << namesToPrint[namesToPrint.size() - 1] << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "printPreorder" && name.empty() && id.empty() && remainder.empty()) {
            vector<string> namesToPrint;
            vector<string>* names = &namesToPrint;
            avl.printPreorder(names);
            if (!names->empty()) {
                for (int j = 0; j < names->size() - 1; j++) {
                    cout << namesToPrint[j] << ", ";
                }
                cout << namesToPrint[namesToPrint.size() - 1] << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "printPostorder" && name.empty() && id.empty() && remainder.empty()) {
            vector<string> namesToPrint;
            vector<string>* names = &namesToPrint;
            avl.printPostorder(names);
            if (!names->empty()) {
                for (int j = 0; j < names->size() - 1; j++) {
                    cout << namesToPrint[j] << ", ";
                }
                cout << namesToPrint[namesToPrint.size() - 1] << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "printLevelCount" && name.empty() && id.empty() && remainder.empty()) {
            avl.printLevelCount();
        } else if (command == "removeInorder" && name.empty() && remainder.empty()) {
            int idNum = stoi(id);
            avl.removeInorder(idNum);
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    avl.destruct();
    return 0;
}