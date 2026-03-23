#include <iostream>
#include <fstream>
#include <set>
#include "utils/string_utils.h"

using namespace std;

unsigned long euclideanDistance(const vector<int>& pos1, const vector<int>& pos2) {
    if (pos1.size() != pos2.size()) {
        cerr << "Error: Positions must have the same dimension." << endl;
        return 0;
    }
    unsigned long squaredSum = 0;
    for (size_t i = 0; i < pos1.size(); i++) {
        squaredSum += pow(pos1[i] - pos2[i], 2);
    }
    return sqrt(squaredSum);
}

int main()
{
    string filePath = "./resources/day8.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    set<vector<int>> positions;
    set<tuple<unsigned long, vector<int>, vector<int>>> distances;
    
    while (getline(fileStream, line)) {
        vector<string> coordinates = utils::split(line, ',');
        if (coordinates.size() != 3) {
            cerr << "Invalid line format: " << line << endl;
            continue;
        }

        vector<int> position = { stoi(coordinates[0]), stoi(coordinates[1]), stoi(coordinates[2])};
        for (const vector<int>& other : positions) {
            unsigned long distance = euclideanDistance(position, other);
            distances.insert({distance, position, other});
        }
        positions.insert(position);
    }
    fileStream.close();

    set<set<vector<int>>> connections;
    int connectionCount = 0;
    for (const auto& entry : distances) {
        unsigned long distance = get<0>(entry);
        const vector<int>& pos1 = get<1>(entry);
        const vector<int>& pos2 = get<2>(entry);

        set<set<vector<int>>> matchingConnections;
        for (const set<vector<int>>& connection : connections) {
            if (connection.find(pos1) != connection.end() || connection.find(pos2) != connection.end()) {
                matchingConnections.insert(connection);
            }
        }

        if (matchingConnections.empty()) {
            connections.insert({pos1, pos2});
        } else if(matchingConnections.size() == 2) {
            auto it = matchingConnections.begin();
            set<vector<int>> first = *it;
            ++it;
            set<vector<int>> second = *it;
            connections.erase(first);
            connections.erase(second);
            first.insert(second.begin(), second.end());
            connections.insert(first);
        } else if (matchingConnections.size() == 1) {
            auto it = matchingConnections.begin();
            set<vector<int>> connection = *it;
            connections.erase(connection);
            connection.insert(pos1);
            connection.insert(pos2);
            connections.insert(connection);
        }

        if(connectionCount == 10) {
            break;
        }
    }

    for (const set<vector<int>>& connection : connections) {
        cout << "Connection group:" << endl;
        for (const vector<int>& pos : connection) {
            cout << " - (" << pos[0] << "," << pos[1] << "," << pos[2] << ")" << endl;
        }
    }

    return 0;
}