#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

struct BinaryTreeNode {
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode() : left(nullptr), right(nullptr) {}
};

int main()
{
    const char startChar = 'S';
    const char splitChar = '^';
    string filePath = "./resources/day7.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    unsigned int splitCount = 0;
    unsigned int xi = 0;
    set<pair<int, int>> beams;
    while (getline(fileStream, line)) {
        unsigned int yi = 0;
        for (char& c : line) {
            if (c == startChar) {
                beams.insert({xi, yi});
            } else if (c != splitChar && beams.find({xi, yi}) != beams.end()) {
                beams.insert({xi + 1, yi});
            } else if (c == splitChar && beams.find({xi, yi}) != beams.end()) {
                if (yi > 0) {
                    beams.insert({xi + 1, yi - 1});
                }
                if (yi <= line.size()) {
                    beams.insert({xi + 1, yi + 1});
                }
                splitCount++;
            }
            yi++;
        }
        xi++;
    }
    fileStream.close();

    cout << "1) Number of splits: " << splitCount << endl;
}