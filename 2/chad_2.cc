#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

struct Rules
{
    unordered_map<char, string> translate
    {
        {'A', "rock"},
        {'X', "rock"},

        {'B', "paper"},
        {'Y', "paper"},

        {'C', "scissors"},
        {'Z', "scissors"}
    };

    unordered_map<string, string> winner
    {
        {"rock", "scissors"},
        {"paper", "rock"},
        {"scissors", "paper"}
    };

    unordered_map<string, int> points
    {
        {"rock", 1},
        {"paper", 2},
        {"scissors", 3}
    };
};


int calculate_points(ifstream & file)
{
    Rules rules{};

    char op_char{};
    char me_char{};
    int my_points{};

    while(file >> op_char >> me_char)
    {
        string op = rules.translate[op_char];
        string me = rules.translate[me_char];
        if(me_char == 'Z') // win
        {
            my_points += rules.points[rules.winner[rules.winner[op]]] + 6;
        }
        else if (me_char == 'Y') // draw
        {
            my_points += rules.points[op] + 3;
        }
        else // loss 
        {
            my_points += rules.points[rules.winner[op]];
        }
        
    }

    return my_points;
}


int algo(ifstream & file)
{
    Rules rules{};

    char op_char{};
    char me_char{};
    int my_points{};

    // while(file >> op_char >> me_char)
    // {
    //     string op = rules.translate[op_char];
    //     string me = rules.translate[me_char];
    //     if(me_char == 'Z') // win
    //     {
    //         my_points += rules.points[rules.winner[rules.winner[op]]] + 6;
    //     }
    //     else if (me_char == 'Y') // draw
    //     {
    //         my_points += rules.points[op] + 3;
    //     }
    //     else // loss 
    //     {
    //         my_points += rules.points[rules.winner[op]];
    //     }
        
    // }

    auto round_points = [] (int total_points, )
    {

    }

    accumulate(istream_iterator<char>(file), istream_iterator<char>(), 0, )

    return my_points;
}

int main()
{
    ifstream file("full_game.txt"); // 12429
    // ifstream file("test_game.txt"); // 45

    cout << "Total points: " << calculate_points(file) << endl;

    return 0;

}