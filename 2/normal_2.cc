#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <string>

using namespace std;

int part1(ifstream & file)
{
    // A, X = Rock     = 1 p
    // B, Y = Paper    = 2 p
    // C, Z = Scissors = 3 p
    // loss = 0p
    // draw = 3p
    // win = 6p
    unordered_map<char, char> winner
    {
        {'X', 'C'},
        {'Y', 'A'},
        {'Z', 'B'}
    };

    unordered_map<char, char> draw
    {
        {'X', 'A'},
        {'Y', 'B'},
        {'Z', 'C'}
    };


    unordered_map<char, int> points
    {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };


    char oponent{};
    char me{};
    int my_points{};

    while(file >> oponent >> me)
    {
        if(winner[me] == oponent)
            my_points += points[me] + 6;
        else if (draw[me] == oponent)
            my_points += points[me] + 3;
        else 
            my_points += points[me];
    }

    return my_points;
}


int part2(ifstream & file)
{
    // oponent (key) loeses against (value)
    unordered_map<char, char> winner
    {
        {'A', 'Y'},
        {'B', 'Z'},
        {'C', 'X'}
    };

    unordered_map<char, char> draw
    {
        {'A', 'X'},
        {'B', 'Y'},
        {'C', 'Z'}
    };


    unordered_map<char, char> loss
    {
        {'A', 'Z'},
        {'B', 'X'},
        {'C', 'Y'}
    };


    unordered_map<char, int> points
    {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };


    char oponent{};
    char me{};
    int my_points{};

    while(file >> oponent >> me)
    {
        if(me == 'Z') // win
            my_points += points[winner[oponent]] + 6;
        else if (me == 'Y')
            my_points += points[draw[oponent]] + 3;
        else 
            my_points += points[loss[oponent]];
    }

    return my_points;
}


int main()
{
    ifstream file("full_game.txt");

    cout << "Total points: " << part2(file) << endl;

    return 0;

}