#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <set>

using namespace std;


unordered_map<char, int> generate_priority_map()
{
    // FIXME: string stream?
    string lowercase {"abcdefghijklmnopqrstuvwxyz"};
    string uppercase {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    cout << typeid(uppercase[1]).name() << endl;
    cout << typeid(uppercase[26]).name() << endl;
    cout << typeid(uppercase[1]).name() << endl;

    unordered_map<char, int> priority {};

    // FIXME: transform?
    for(int i{0}; i < 26; i++)
    {
       priority[lowercase[i]] = i + 1;
    }

    for(int i{26}; i < 52; i++)
    {
       priority[uppercase[i-26]] = i + 1;
    }

    return priority;
}



int find_matching_letters(ifstream & file, 
                          unordered_map<char, int> const& priority)
{
    string elf1 {};
    string elf2 {};
    string elf3 {};
    // doing this in case part 2 has multiple occurances
    int total_value {};

    while(getline(file, elf1))
    {
        getline(file, elf2);
        getline(file, elf3);

        set<char> elem_elf1{begin(elf1), end(elf1)};
        set<char> elem_elf2{begin(elf2), end(elf2)};
        set<char> elem_elf3{begin(elf3), end(elf3)};
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