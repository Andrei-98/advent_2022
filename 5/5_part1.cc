#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

void print_storage(map<int, vector<char>> const& storage)
{
    string top_crates;
    for ( auto const & i : storage)
    {
        cout << i.first << " "; 

        top_crates += i.second.back();

        //copy(first(i.second), end(i.second), std::output_iterator(cout, " "));

        for ( auto const & j : i.second )
        {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << "Top crates are: " << top_crates << endl;
}

map<int, vector<char>> create_creates(ifstream & file)
{
    vector<string> lines{};
    string line;
    while(true)
    {
        getline(file, line);
        if(line == "")
            break;

        lines.push_back(line);
        cout << line << endl;
    }

    reverse(begin(lines), end(lines));
    map<int, vector<char>> crates_positions{};

    string numbers{lines[0]};
    // [B] [T] [M] [B] [J] [C] [T] [G] [N]
    //  1   2   3   4   5   6   7   8   9 
    // go number by number, start with 1, check if the letter above is a space,
    // if not add that letter to the map coresponding the key 1, keep going up for 1
    // etc...
    for (int i{}; i < numbers.size(); i++)
    {
        if(numbers[i] != ' ')
        {
            int current_number {atoi(&numbers[i])};
            vector<char> creates_for_current {};

            for (int row{1}; row < lines.size(); row++)
            {
                char possible_letter {lines[row][i]};
                if(possible_letter != ' ')
                    creates_for_current.push_back(possible_letter);
                else
                    continue;
            }
            crates_positions[current_number] = creates_for_current;
        }
    }
    return crates_positions;
}


void execute_crane_movements(ifstream & file, map<int, vector<char>> & crates)
{
    string line;
    while(getline(file, line))
    {
        istringstream line_stream{line};
        string move, from_string, to_string;
        int nr_of_crates, from, to;

        line_stream >> move >> nr_of_crates >> from_string 
                    >> from >> to_string >> to;

        auto it = prev(crates[from].end(), nr_of_crates);
        std::reverse_copy(it, crates[from].end(), back_inserter(crates[to]));
        crates[from].erase(it, crates[from].end());
    }
}


int main()
{
    ifstream file {"full_input.txt"};

    map<int, vector<char>> starting_crates {create_creates(file)};
    execute_crane_movements(file, starting_crates);
    print_storage(starting_crates);

    return 0;
}