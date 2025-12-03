#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

long createNumberFromDigits(const vector<int> &digits) {
    long number = 0;
    for (int digit : digits) {
        number = number * 10 + digit;
    }
    return number;
}

long findLargestCombinedNumber(vector<int> &digits, int size) {

    if (digits.size() < size) {
        cerr << "Error: Not enough digits to form a number of size " << size << endl;
        return 0;
    }

    vector<int> result;
    int startIndex = 0;
    for (int i = 0; i < size; i++) {
        
        int remaining = size - i - 1;
        int searchEnd = digits.size() - remaining;
        
        int maxDigit = digits[startIndex];
        int maxIndex = startIndex;
        for (int j = startIndex; j < searchEnd; j++) {
            if (digits[j] > maxDigit) {
                maxDigit = digits[j];
                maxIndex = j;
            }
        }
        
        result.push_back(maxDigit);
        startIndex = maxIndex + 1;
    }
    
    return createNumberFromDigits(result);
}

int main()
{
    string filePath = "./resources/day3.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    unsigned long twoDigitSum = 0;
    unsigned long twelveDigitSum = 0;
    while (getline(fileStream, line)) {

        vector<int> lineDigits;
        for (char ch : line) {
            lineDigits.push_back(ch - '0');
        }

        twoDigitSum += findLargestCombinedNumber(lineDigits, 2);
        twelveDigitSum += findLargestCombinedNumber(lineDigits, 12);
    }
    fileStream.close();

    cout << "1) Total sum of maximum two-digit combinations: " << twoDigitSum << endl;
    cout << "2) Total sum of maximum twelve-digit combinations: " << twelveDigitSum << endl;

    return 0;
}
