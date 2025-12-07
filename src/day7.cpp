#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

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
    unsigned int rowIndex = 0;
    set<pair<unsigned int, unsigned int>> beams;
    map<unsigned int, unsigned long> pathCounts;

    while (getline(fileStream, line)) {
        unsigned int columnIndex = 0;
        map<unsigned int, unsigned long> newPathCounts;
        for (char& c : line) {
            if (c == startChar) {
                beams.insert({rowIndex, columnIndex});
                newPathCounts[columnIndex] = 1;
            } else if (c != splitChar && beams.find({rowIndex - 1, columnIndex}) != beams.end()) {
                beams.insert({rowIndex, columnIndex});
                newPathCounts[columnIndex] += pathCounts[columnIndex];
            } else if (c == splitChar && beams.find({rowIndex - 1, columnIndex}) != beams.end()) {
                if (columnIndex > 0) {
                    beams.insert({rowIndex, columnIndex - 1});
                    newPathCounts[columnIndex - 1] += pathCounts[columnIndex];
                }
                if (columnIndex <= line.size()) {
                    beams.insert({rowIndex, columnIndex + 1});
                    newPathCounts[columnIndex + 1] += pathCounts[columnIndex];
                }
                splitCount++;
            }
            columnIndex++;
        }
        pathCounts = newPathCounts;
        rowIndex++;
    }
    fileStream.close();

    unsigned long totalPaths = 0;
    for (const pair<unsigned int, unsigned long>& pair : pathCounts) {
        totalPaths += pair.second;
    }

    cout << "1) Number of splits: " << splitCount << endl;
    cout << "2) Number of possible paths: " << totalPaths << endl;

    return 0;
}