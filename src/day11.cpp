#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "utils/string_utils.h"

using namespace std;

struct Node {
    string name;
    vector<Node*> children;
};

void walkPaths (Node* current, Node* target, set<string>& currentPath, vector<set<string>>& paths, set<string> pathFilter = {}) {
    currentPath.insert(current->name);
    if (current == target){
        if(pathFilter.size() > 0 && includes(currentPath.begin(), currentPath.end(), pathFilter.begin(), pathFilter.end())) {
            paths.push_back(currentPath);
        } else if (pathFilter.empty()) {
            paths.push_back(currentPath);
        }
    } else {
        for (Node* child : current->children) {
            walkPaths(child, target, currentPath, paths, pathFilter);
        }
    }
    currentPath.erase(current->name);
};

int main()
{
    string filePath = "./resources/day11.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    map<string, Node*> nodes;
    vector<string> nodeFilter;

    while (getline(fileStream, line)) {
        string name = line.substr(0, line.find(':'));
        if (nodes.find(name) == nodes.end()) {
            nodes[name] = new Node{name, {}};
        }

        vector<string> childNames = utils::split(line.substr(line.find(':') + 1), ' ');
        for (const string& childName : childNames) {
            if (childName.empty()) continue;
            if (nodes.find(childName) == nodes.end()) {
                nodes[childName] = new Node{childName, {}};
            }
            
            nodes[name]->children.push_back(nodes[childName]);
        }
    }
    fileStream.close();

    set<string> currentPath;
    vector<set<string>> youToOutPaths;
    if (nodes.find("you")!= nodes.end()) {
        walkPaths(nodes["you"], nodes["out"], currentPath, youToOutPaths);
    }

    currentPath.clear();
    vector<set<string>> svrToOutPaths;
    if (nodes.find("svr") != nodes.end()) {
        walkPaths(nodes["svr"], nodes["out"], currentPath, svrToOutPaths, {"dac", "fft"});
    }

    cout << "1) Number of paths from 'you' to 'out': " << youToOutPaths.size() << endl;
    cout << "2) Number of paths from 'svr' to 'out' visiting 'dac' and 'fft': " << svrToOutPaths.size() << endl;

    return 0;
}