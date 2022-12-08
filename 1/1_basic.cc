#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
// 74198
// this make me cry... what the fuck...three years? and this is it?
// i can do better

void read_file(string const &file_name)
{
    ifstream input(file_name);
    long highest_cal_count{0};
    long current_cal_count{0};
    int index_highest_cal{0};
    int index_current{0};
    string value{};

    while (getline(input, value))
    {
        if (value == "")
        {
            cout << "saving value" << endl;
            index_current++;
            if (current_cal_count > highest_cal_count)
            {
                highest_cal_count = current_cal_count;
                index_highest_cal = index_current;
            }
            current_cal_count = 0;
            continue;
        }
        if (stol(value) == 12716)
            cout << "hi" << endl;

        cout << "value = " << value << endl;
        current_cal_count += stol(value);
    }

    if (current_cal_count > highest_cal_count)
    {
        highest_cal_count = current_cal_count;
        current_cal_count = 0;

        index_highest_cal = index_current + 1;
    }

    cout << highest_cal_count << " " << index_highest_cal << endl;
}

int main()
{
    read_file("calories.txt");
    // read_file("test_input.txt");

    // get_elf_with_most_calories()

    return 0;
}