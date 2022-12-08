#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <ios>

using namespace std;
// 74198
// 209914

void process_elf_backpack(long current_elf_cals, array<long, 3> &top_three)
{
    array<long, 3>::iterator it = min_element(top_three.begin(), top_three.end());

    if (current_elf_cals > *it)
    {
        swap(*it, current_elf_cals);
    }
}

long chad_read_file(string const &file_name)
{
    ifstream input(file_name);
    array<long, 3> top_three{};
    long current_cals{0};

    auto lambda_func = [top_three, current_cals](string line) mutable
    {
        if (line == "")
        {
            process_elf_backpack(stol(line), top_three);
        }
        else
        {
            current_cals += stol(line);
        }
        return "";
    };

    // auto test_lamda = [](string line) mutable

    noskipws(input);
    transform(istream_iterator<string>(input),
              istream_iterator<string>(),
              ostream_iterator<string>({cout}),
              lambda_func);

    return accumulate(top_three.begin(), top_three.end(),0);
    // return 0;
}

long read_file(string const &file_name)
{
    ifstream input(file_name);
    long current_cal_count{0};
    string value{};
    array<long, 3> highest_three_elves{};

    while (getline(input, value))
    {
        // we are on last elemnt force check by setting value to ""
        if (input.peek() == EOF)
        {
            current_cal_count += stol(value);
            value = "";
        }

        if (value == "")
        {
            process_elf_backpack(current_cal_count, highest_three_elves);
            current_cal_count = 0;
            continue;
        }

        current_cal_count += stol(value);
    }

    long result = accumulate(highest_three_elves.begin(), highest_three_elves.end(), 0);

    return result;
}

int main()
{
    // cout << read_file("calories.txt") << endl;
    // cout << read_file("test_input.txt") << endl;
    cout << chad_read_file("test_input.txt") << endl;

    return 0;
}