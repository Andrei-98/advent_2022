#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
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

bool is_tree_in_row_hidden(vector<size_t> const& row, size_t from, size_t to, size_t my_size)
{
    // 2 5 5 1 2
    for ( size_t i {from}; i < to; i++ )
    {
        if(row[i] >= my_size)
            return true;
    }
    return false;
}


bool is_tree_in_column_hidden(Forest const& forest, size_t cur_column, 
                              size_t from, size_t to, size_t my_size)
{
    // cout << endl;
    // cout << "Curent column: " << cur_column << " from " << from << " to " << to << " my size " << my_size << endl;
    for (size_t row {from}; row < to; row++)
    {
        size_t cur_size {forest.matrix[row][cur_column]};
        bool hidden { cur_size >= my_size};
        // cout << "LOOKING AT " << cur_size << " vs " << cur_size << endl;

        if (hidden)
        {
            return true;
        }
    }
    return false;

}


size_t forest_lazer(Forest const& forest)
{
    size_t hidden_trees {};
    size_t total_trees { forest.matrix.size() * forest.matrix[0].size()};

    for ( size_t row {0}; row < forest.matrix.size(); row++ )
    {
        size_t row_size {forest.matrix[row].size()};
        for ( size_t column {0}; column < row_size; column++)
        {
            // edge
            if (column == 0 || column == row_size || row == 0 || row == forest.matrix.size() )
                continue;

            size_t cur_tree {forest.matrix[row][column]};
            vector<size_t> cur_row {forest.matrix[row]};

            // edge

            bool left {is_tree_in_row_hidden(cur_row, 0, column, cur_tree)};
            bool right {is_tree_in_row_hidden(cur_row, column + 1, row_size, cur_tree)};

            bool top {is_tree_in_column_hidden(forest, column, 0, row, cur_tree)};
            bool bottom {is_tree_in_column_hidden(forest, column, row+1, forest.matrix.size(), cur_tree)};


            if ( left && right && top && bottom )
                hidden_trees++;
        }

    }

    return total_trees - hidden_trees;
}


int main()
{
    // Forest matrix { build_matrix("test_input.txt") }; // 21
    Forest matrix { build_matrix("full_input.txt") }; // 1736 
    // Forest matrix { build_matrix("test_input2.txt") }; // 68 < x <?


    size_t visible_trees { forest_lazer(matrix) };

    cout << "Nr of visible trees is: " << visible_trees << endl;

    return 0;
}