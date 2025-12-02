#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const unsigned int MAX_POINTER = 99;

int main()
{
    string filePath = "./resources/day1.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }
    
    int currentPointer = 50;
    unsigned int hitsOnZero = 0;
    unsigned int directHitsOnZero = 0;

    string line;
    while (getline(fileStream, line)) {
        string command = line.substr(0,1);
        int value = stoi(line.substr(1)) * (command == "L" ? -1 : 1);

        bool wasAtZero = (currentPointer == 0);
        currentPointer += value;

        while (currentPointer < 0) {
            currentPointer += MAX_POINTER + 1;
            if (!wasAtZero) {
                hitsOnZero++;
            }
            wasAtZero = false;
        }

        while (currentPointer > MAX_POINTER) {
            currentPointer -= MAX_POINTER + 1;
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
