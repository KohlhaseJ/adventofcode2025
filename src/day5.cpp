#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include "utils/string_utils.h"

using namespace std;

int main()
{
    string filePath = "./resources/day5.txt";
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    string line;
    unsigned long numberOfFreshIngredients = 0;
    set<pair<long, long>> freshIngredientRanges;
    
    bool isFreshIngredientSection = true;
    while (getline(fileStream, line)) {
        if (line.empty()) {
            isFreshIngredientSection = false;
            continue;
        }

        if (isFreshIngredientSection) {
            vector<string> parts = utils::split(line, '-');
            if (parts.size() != 2) {
                cerr << "Invalid ingredient range format: " << line << endl;
                continue;
            }
            freshIngredientRanges.insert(make_pair(stol(parts[0]), stol(parts[1])));
        } else {
            long ingredientId = stol(line);
            for (const auto& range : freshIngredientRanges) {
                if (ingredientId >= range.first && ingredientId <= range.second) {
                    numberOfFreshIngredients++;
                    break;
                }
            }
        }
    }
    fileStream.close();

    unsigned long numberOfUniqueFreshIngredientIds= 0;
    set<pair<long, long>>::iterator iterator = freshIngredientRanges.begin();
    long currentStart = iterator->first;
    long currentEnd = iterator->second;
    iterator++;
    
    for (; iterator != freshIngredientRanges.end(); ++iterator) {
        long nextStart = iterator->first;
        long nextEnd = iterator->second;
        
        if (nextStart <= currentEnd) {
            currentEnd = max(currentEnd, nextEnd);
        } else {
            numberOfUniqueFreshIngredientIds += (currentEnd - currentStart + 1);
            currentStart = nextStart;
            currentEnd = nextEnd;
        }
    }
    numberOfUniqueFreshIngredientIds += (currentEnd - currentStart + 1);

    cout << "1) Number of fresh ingredients: " << numberOfFreshIngredients << endl;
    cout << "2) Number of unique fresh ingredient IDs: " << numberOfUniqueFreshIngredientIds << endl;

    return 0;
}
