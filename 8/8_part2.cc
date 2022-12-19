#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <exception>

using namespace std;

struct Forest
{
    Forest() : matrix{} {}

    Forest(vector<vector<size_t>> & matrix)
    : matrix{matrix}
    {};

    vector<vector<size_t>> matrix;
};


Forest build_matrix(string file_name)
{
    ifstream file{file_name};
    string line;
    Forest forest { Forest() };

    while(getline(file, line))
    {
        istringstream iss(line);
        vector<size_t> row {};
        transform(istream_iterator<char>(iss), istream_iterator<char>(), back_inserter(row),
             [] (char c) { return atoi(&c); } );
        forest.matrix.push_back(row);
    }

    return forest;
}

size_t get_score_left(vector<size_t> const& row, const size_t my_tree_pos, 
                     const size_t my_tree_size)
{
    size_t score {0};

    for(int i {my_tree_pos - 1}; i >= 0; i--)
    {
        if (row[i] >= my_tree_size)
        {
            score++;
            return score;
        }
        else 
            score++;
    }
    return score;
}

// size_t get_score(vector<size_t> const& row, size_t const my_tree_pos,
//                  size_t const my_tree_size)
// {
//     find_if()

// }


size_t get_score_right(vector<size_t> const& row, const size_t my_tree_pos,
                      const size_t my_tree_size)
{
    size_t score {0};

    for(size_t i {my_tree_pos + 1}; i < row.size(); i++)
    {
        if (row[i] >= my_tree_size)
        {
            score++;
            return score;
        }
        else
            score++;
    }
    return score;
}


size_t get_score_top(Forest const& forest, size_t const my_tree_pos,
                     size_t const my_tree_size, size_t const my_tree_row)
{
    size_t score {0};

    for(int i {my_tree_row - 1}; i >= 0; i--)
    {
        if(forest.matrix[i][my_tree_pos] >= my_tree_size)
        {
            score++;
            return score;
        }
        else
            score++;
    }

    return score;
}


size_t get_score_bottom(Forest const& forest, size_t const my_tree_pos,
                     size_t const my_tree_size, size_t const my_tree_row)
{
    size_t score {0};

    for(size_t i {my_tree_row + 1}; i < forest.matrix.size(); i++)
    {
        if(forest.matrix[i][my_tree_pos] >= my_tree_size)
        {
            score++;
            return score;
        }
        else
            score++;
    }

    return score;
}


size_t forest_lazer(Forest const& forest)
{
    size_t top_score {};
    size_t total_trees { forest.matrix.size() * forest.matrix[0].size()};

    for ( size_t row {0}; row < forest.matrix.size(); row++ )
    {
        size_t row_size {forest.matrix[row].size()};
        for ( size_t column {0}; column < row_size; column++)
        {
            // edge
            if (column == 0 || column == row_size || row == 0 || row == forest.matrix.size() - 1 )
                continue;

            size_t cur_tree {forest.matrix[row][column]};
            vector<size_t> cur_row {forest.matrix[row]};


            size_t left {get_score_left(cur_row, column, cur_tree)};
            size_t right {get_score_right(cur_row, column, cur_tree)};

            size_t top {get_score_top(forest, column,  cur_tree, row)};
            size_t bottom {get_score_bottom(forest, column, cur_tree, row)};

            size_t current_score {left * right * top * bottom };
            if (current_score > top_score)
            {
                top_score = current_score;
            }
        }
    }
    return top_score; 
}


int main()
{
    // Forest matrix { build_matrix("test_input.txt") }; // 8
    Forest matrix { build_matrix("full_input.txt") }; // 268800 
    // Forest matrix { build_matrix("test_input2.txt") }; // 72 

    // Testing
    vector<size_t> test_left {3, 0, 3, 7, 3, 9, 2, 0, 1};
    size_t test_left1 {get_score_left(test_left, 2, 3)}; // 1
    std::cout << "RESULT = " << test_left1 << endl;
    assert (test_left1 == 2);

    test_left1 = get_score_left(test_left, 3, 7); // 1
    std::cout << "RESULT = " << test_left1 << endl;
    assert (test_left1 == 3);

    test_left1 = get_score_left(test_left, 1, 0); // 1
    std::cout << "RESULT = " << test_left1 << endl;
    assert (test_left1 == 1);

    test_left1 = get_score_left(test_left, 7, 0); // 1
    std::cout << "RESULT = " << test_left1 << endl;
    assert (test_left1 == 1);

    test_left1 = get_score_left(test_left, 5, 9); // 1
    std::cout << "RESULT = " << test_left1 << endl;
    assert (test_left1 == 5);


    vector<size_t> test_right {2, 5, 5, 1, 2, 9, 2 ,0 ,9};
    size_t score = get_score_right(test_right, 2, 5);
    std::cout << "RESULT = " << score << endl;
    assert (score == 3);

    size_t top_score { forest_lazer(matrix) };

    cout << "Top Score is: " << top_score << endl;
    return 0;
}