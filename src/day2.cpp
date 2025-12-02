#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "utils/string_utils.h"

using namespace std;

bool hasSequenceRepeatingOnce(unsigned long n) {
    string s = to_string(n);
    size_t len = s.length();
    if (len > 0 && len % 2 == 0) {
        size_t half = len / 2;
        if (s.substr(0, half) == s.substr(half)) {
            return true;
        }
    }
    return false;
}

bool hasSequenceRepeatingMultipleTimes(unsigned long n) {
    string s = to_string(n);
    size_t len = s.length();

    if(len > 1) {
        for(size_t subLen = 1; subLen <= len / 2; subLen++) {
            if(len % subLen == 0) {
                string subStr = s.substr(0, subLen);
                size_t repetitions = len / subLen;
                string constructed;
                for(size_t i = 0; i < repetitions; i++) {
                    constructed += subStr;
                }
                if(constructed == s) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    string filePath = "./resources/day2.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }
    
    string line;
    vector<unsigned long> invalidIdSums = {0, 0};

    while (getline(fileStream, line)) {
        for (const string& idRange : utils::split(line, ',')) {

            unsigned long rangeStart = stoul(idRange.substr(0, idRange.find('-')));
            unsigned long rangeEnd = stoul(idRange.substr(idRange.find('-') + 1));

            for (unsigned long id = rangeStart; id <= rangeEnd; id++)
            {
                if(hasSequenceRepeatingOnce(id)) {
                    invalidIdSums[0] += id;
                    invalidIdSums[1] += id;
                } else if(hasSequenceRepeatingMultipleTimes(id)) {
                    invalidIdSums[1] += id;
                }
            }
        }
    }

    cout << "1) Sum of invalid IDs: " << invalidIdSums[0] << endl;
    cout << "2) Sum of invalid IDs: " << invalidIdSums[1] << endl;
    return 0;
}
