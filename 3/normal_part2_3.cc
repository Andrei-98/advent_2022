#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;


unordered_map<char, int> generate_priority_map2()
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

template <typename T, typename Y>
set<char> find_common_char(T & line1, Y & line2)
{
    set<char> common_chars {};
    set<char> line1_set{begin(line1), end(line1)};
    set<char> line2_set{begin(line2), end(line2)};

    set_intersection(begin(line1_set), end(line1_set),
                     begin(line2_set), end(line2_set),
                     inserter(common_chars, begin(common_chars)));

    return common_chars;
}

int find_matching_letters(ifstream & file, 
                          unordered_map<char, int> const& priority)
{
    string elf1, elf2, elf3;

    int total_value {};

    while(getline(file, elf1))
    {
        getline(file, elf2);
        getline(file, elf3);

        set<char> elf1_elf2{find_common_char(elf1, elf2)};
        set<char> final_set{find_common_char(elf1_elf2, elf3)};
        
        char first = *begin(final_set);
        total_value += priority.at(first);
    }

    return total_value;
}


int main()
{
    ifstream file{"input_full.txt"}; // 2607
    // ifstream file{"input_example.txt"}; // 

    unordered_map<char, int> priority {generate_priority_map2()};

    int value {find_matching_letters(file, priority)};

    cout << "Total value: " << value << endl;
}