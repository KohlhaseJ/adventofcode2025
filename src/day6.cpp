#include <iostream>
#include <string>
#include <fstream>

#include "utils/string_utils.h"

using namespace std;

int main()
{
    string filePath = "./resources/day6.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    vector<pair<long, long>> sumsAndMultiplies;
    long sumOfAllOperations = 0;
    while (getline(fileStream, line)) {
        unsigned int columnIndex = 0;
        for (const string& element : utils::split(line, ' ')) {
            if(element == "") {
                continue;
            }

            if(sumsAndMultiplies.size() <= columnIndex) {
                sumsAndMultiplies.push_back({0, 1});
            }

            if (element == "+") {
                sumOfAllOperations += sumsAndMultiplies[columnIndex].first;
            }
            else if (element == "*") {
                sumOfAllOperations += sumsAndMultiplies[columnIndex].second;
            }
            else {
                long value = stol(element);
                sumsAndMultiplies[columnIndex].first += value;
                sumsAndMultiplies[columnIndex].second *= value;
            }
            columnIndex++;
            
        }
    }
    fileStream.close();

    cout << "1) Sum of all operations: " << sumOfAllOperations << endl;

    return 0;
}