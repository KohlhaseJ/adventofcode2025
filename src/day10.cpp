#include <iostream>
#include <fstream>
#include <set>
#include "utils/string_utils.h"

using namespace std;

int main()
{
    string filePath = "./resources/day10.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    set<pair<int, int>> tilePositions;

    long largestArea = 0;

    while (getline(fileStream, line)) {
    }
    fileStream.close();

    cout << "1) Largest area: " << largestArea << endl;
    return 0;
}