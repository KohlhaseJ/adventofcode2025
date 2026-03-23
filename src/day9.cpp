#include <iostream>
#include <fstream>
#include <set>
#include "utils/string_utils.h"

using namespace std;

int main()
{
    string filePath = "./resources/day9.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    set<pair<int, int>> tilePositions;

    long largestArea = 0;

    while (getline(fileStream, line)) {
        vector<string> tokens = utils::split(line, ',');
        if (tokens.size() != 2) {
            cerr << "Invalid line format: " << line << endl;
            continue;
        }
        int x = stoi(tokens[0]);
        int y = stoi(tokens[1]);

        for(const pair<int, int>& position : tilePositions) {
            long width = abs(position.first - x) + 1;
            long height = abs(position.second - y) + 1;
            long area = width * height;
            if (area > largestArea) {
                largestArea = area;
            }
        }

        tilePositions.insert(make_pair(x, y));
    }
    fileStream.close();

    cout << "1) Largest area: " << largestArea << endl;
    return 0;
}