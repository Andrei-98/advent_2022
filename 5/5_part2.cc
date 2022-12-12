
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

void print_storage(map<int, stack<char>> const& storage)
{
    string top_crates;
    for ( auto const & i : storage)
    {
        cout << i.first << " "; 

        top_crates += i.second.top();
    }
    cout << top_crates << endl;
}


map<int, stack<char>> create_starting_position(ifstream & file)
{
    vector<string> lines{};
    string line;
    while(true)
    {
        getline(file, line);
        if(line == "")
            break;

        lines.push_back(line);
    }

    reverse(begin(lines), end(lines));
    map<int, stack<char>> crates_positions{};

    string numbers{lines[0]};
    for (int i{}; i < numbers.size(); i++)
    {
        if(numbers[i] != ' ')
        {
            int current_number {atoi(&numbers[i])};
            stack<char> creates_for_current {};

            for (int row{1}; row < lines.size(); row++)
            {
                char possible_letter {lines[row][i]};
                if(possible_letter != ' ')
                    creates_for_current.push(possible_letter);
                else
                    continue;
            }
            crates_positions[current_number] = creates_for_current;
        }
    }
    return crates_positions;
}


void execute_crane_movements(ifstream & file, map<int, stack<char>> & crates)
{
    string line;
    while(getline(file, line))
    {
        istringstream line_stream{line};
        string move, from_string, to_string;
        int nr_of_crates, from, to;

        line_stream >> move >> nr_of_crates >> from_string 
                    >> from >> to_string >> to;

        vector<char> crates_to_move;
        for (int i{0}; i < nr_of_crates; i++)
        {
            char current_crate {crates[from].top()};
            crates[from].pop();
            crates_to_move.push_back(current_crate);
        }

        reverse(begin(crates_to_move), end(crates_to_move));

        for(auto const & crate : crates_to_move)
        {
            crates[to].push(crate);
        }
    }
}


int main()
{
    ifstream file {"full_input.txt"};

    map<int, stack<char>> starting_crates {create_starting_position(file)};
    execute_crane_movements(file, starting_crates);
    print_storage(starting_crates);

    return 0;
}