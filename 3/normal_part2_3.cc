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


int find_matching_letters(ifstream & file, 
                          unordered_map<char, int> const& priority)
{
    string elf1 {};
    string elf2 {};
    string elf3 {};

    int total_value {};

    while(getline(file, elf1))
    {
        getline(file, elf2);
        getline(file, elf3);

        set<char> elem_elf1{begin(elf1), end(elf1)};
        set<char> elem_elf2{begin(elf2), end(elf2)};
        set<char> elem_elf3{begin(elf3), end(elf3)};

        set<char> elf1_elf2{};
        set_intersection(begin(elem_elf1), end(elem_elf1),
                         begin(elem_elf2), end(elem_elf2),
                         inserter(elf1_elf2, begin(elf1_elf2)));

        set<char> final_set{};
        set_intersection(begin(elf1_elf2), end(elf1_elf2),
                         begin(elem_elf3), end(elem_elf3),
                         inserter(final_set, begin(final_set)));
        
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