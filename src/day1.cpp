#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string filePath = "./resources/day1.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    int maxPointer = 99;
    int currentPointer = 50;
    int hitsOnZero = 0;
    int directHitsOnZero = 0;
    string line;
    while (getline(fileStream, line)) {
        string command = line.substr(0,1);
        int value = stoi(line.substr(1)) * (command == "L" ? -1 : 1);

        bool wasAtZero = (currentPointer == 0);
        currentPointer += value;

        while (currentPointer < 0) {
            currentPointer += maxPointer + 1;
            if (!wasAtZero && currentPointer != 0) {
                hitsOnZero++;
            }
            wasAtZero = false;
        }

        while (currentPointer > maxPointer) {
            currentPointer -= maxPointer + 1;
            if (currentPointer != 0) {
                hitsOnZero++;
            }
        }

        if (currentPointer == 0) {
            hitsOnZero++;
            directHitsOnZero++;
        }
    }
    fileStream.close();
    
    cout << "1) Direct hits on zero: " << directHitsOnZero << endl;
    cout << "2) Hits on zero: " << hitsOnZero << endl;

    return 0;
}
