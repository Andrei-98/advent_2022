#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std;

bool check_if_ranges_overlap(int first, int second, int third, int fourth)
{
    if (third >= first && fourth <= second)
    {
        return true;
    }

    if (first >= third && second <= fourth)
    {
        return true;
    }

    return false;
}


int find_overlapping_pairs(ifstream & file)
{
    int overlapping_teams{};
    string line{};
    while(getline(file, line))
    {
        istringstream input_stream(line);

        int first, second, third, fourth;
        char dash1, dash2, comma;

        input_stream >> first >> dash1 >> second >> comma 
                     >> third >> dash2 >> fourth;


        if (check_if_ranges_overlap(first, second, third, fourth))
            overlapping_teams++;
    };

    return overlapping_teams;
}


int main()
{
    ifstream file {"full_input.txt"}; // 550
    // ifstream file {"test_input.txt"}; // 2 
    int all_overlapping_teams {find_overlapping_pairs(file)};
    cout << "Number of overlapping teams = " << all_overlapping_teams << endl;
    return 0;
}