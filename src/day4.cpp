#include <string>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;


set<pair<int, int>> getReachableLocations(const set<pair<int, int>>& locations) {
    set<pair<int, int>> reachableLocations;
    for (const auto& loc : locations) {
        int r = loc.first;
        int c = loc.second;
        int adjacentCount = 0;
        if (locations.count({r-1, c})) adjacentCount++; // up
        if (locations.count({r-1, c+1})) adjacentCount++; // up-right
        if (locations.count({r, c+1})) adjacentCount++; // right
        if (locations.count({r+1, c+1})) adjacentCount++; // down-right
        if (locations.count({r+1, c})) adjacentCount++; // down
        if (locations.count({r+1, c-1})) adjacentCount++; // down-left
        if (locations.count({r, c-1})) adjacentCount++; // left
        if (locations.count({r-1, c-1})) adjacentCount++; // up-left
        if (adjacentCount < 4) {
            reachableLocations.insert(loc);
        }
    }
    return reachableLocations;
}

set<pair<int, int>> removeLocations(const set<pair<int, int>>& locations, const set<pair<int, int>>& toRemove) {
    set<pair<int, int>> result;
    for (const pair<int, int>& loc : locations) {
        if (toRemove.count(loc) == 0) {
            result.insert(loc);
        }
    }
    return result;
}

int main()
{
    string filePath = "./resources/day4.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    int lineIndex = 0;
    set<pair<int, int>> locations;
    while (getline(fileStream, line)) {
        int rowIndex = 0;
        for (char c : line) {
            if(c == '@') { 
              locations.insert({lineIndex, rowIndex});
            }
            rowIndex++;
        }
        lineIndex++;
    }
    fileStream.close();

    set<pair<int, int>> newLocations = locations;
    set<pair<int, int>> reachableLocations = getReachableLocations(newLocations);
    long totalNumberOfReachableLocations = 0;
    while (reachableLocations.size() > 0)
    {
        totalNumberOfReachableLocations += reachableLocations.size();
        newLocations = removeLocations(newLocations, reachableLocations);
        reachableLocations = getReachableLocations(newLocations);
    }
    

    cout << "1) number of reachable locations: " << getReachableLocations(locations).size() << endl;
    cout << "2) total number of reachable locations: " << totalNumberOfReachableLocations << endl;

    return 0;
}