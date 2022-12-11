#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <algorithm>

using namespace std;

unordered_map<char, int> generate_priority_map()
{
    string letters {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    unordered_map<char, int> priority {};

    int index{0};
    auto set_char_values = [index](char c) mutable
    {
        index++;
        return std::make_pair(c, index);
    };

    std::transform(letters.begin(), letters.end(), 
                   std::inserter(priority, priority.end()), set_char_values);

    return priority;
}


int find_matching_letters(ifstream & file, 
                          unordered_map<char, int> const& priority)
{
    string line {};
    // doing this in case part 2 has multiple occurances
    int total_value {};


    while(getline(file, line))
    {
        cout << line << endl;
        unordered_map<char, int> occurances{};
        int half_point {(int)line.size() / 2};

        // read first half and memorise chars
        for (int i {0}; i < half_point; i++)
        {
            occurances[line[i]] += 1;
        }

        // read second half and check if char repeats in first half
        int end {(int)line.size()};
        for (int i {half_point}; i < end; i++)
        {
            if(occurances.find(line[i]) != occurances.end())
            {
                total_value += priority.at(line[i]);
                break;
            }
        }
    }

    return total_value;
}



int main()
{
    ifstream file{"input_full.txt"}; // 157
    // ifstream file{"input_example.txt"}; // 157

    unordered_map<char, int> priority {generate_priority_map()};

    int value {find_matching_letters(file, priority)};

    cout << "Total value: " << value << endl;

}