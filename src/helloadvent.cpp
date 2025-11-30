#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "Advent", "of", "Code"};
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}
