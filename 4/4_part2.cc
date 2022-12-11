#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std;

bool check_if_overlap(int first, int second, int third, int fourth)
{

    set<int> first_team, second_team;

    generate_n(inserter(first_team, begin(first_team)), second - first + 1, 
               [i = first] () mutable { return i++; });
    
    generate_n(inserter(second_team, begin(second_team)), fourth - third + 1, 
               [i = third] () mutable { return i++; });

    vector<int> intersected_values;
    set_intersection(begin(first_team), end(first_team),
                     begin(second_team), end(second_team),
                     back_inserter(intersected_values));

    return intersected_values.size() != 0;
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


        if (check_if_overlap(first, second, third, fourth))
            overlapping_teams++;
    };

    return overlapping_teams;
}


int main()
{
    ifstream file {"full_input.txt"}; // 550
    // ifstream file {"test_input.txt"}; // 4 
    int all_overlapping_teams {find_overlapping_pairs(file)};
    cout << "Number of overlapping teams = " << all_overlapping_teams << endl;
    return 0;
}