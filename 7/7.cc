#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iterator>
#include <map>
#include <stack>
#include <numeric>
#include <unordered_map>
#include <exception>

using namespace std;

// read from file line by line, where line = "$ cd /"
// line becomes ["$", "cd", "/"] for easier manipulation in tree_crawler()
vector<vector<string>> load_file(string const& file_name)
{
    ifstream input {file_name};

    vector<vector<string>> commands{};
    string line {};
    while(getline(input, line))
    {
        istringstream line_stream {line};

        vector<string> command;
        copy(istream_iterator<string>(line_stream), istream_iterator<string>(),
             back_inserter(command));
        commands.push_back(command);
    }
    return commands;
}


struct Dir
{
    string name;
    int size;
    string parent;
    vector<string> children;

    Dir(string name, int size, string parent)
    : name{name}, size{size}, parent{parent}
    {};

    void print_dir() const
    {
        cout << "[Dir: " << name << " size: " << size << " parent " << parent <<endl;
    };
};


vector<Dir> create_tree(vector<vector<string>> const& commands)
{
    vector<Dir> tree;

    for( auto const& command : commands) 
    {
        // $ cd ..
        // $ ls
        // dir name
        // 1230 a.txt
        string arg1 {command[0]};
        string arg2 {command[1]};

        stack<string> cd_stack;


        if ( arg1 == "$" )
        {
            if ( arg2 == "cd ")
            {

            }
            
        }
    }

    return tree;
}



int main()
{
    // string file_name {"test_input.txt"}; // 95437
    string file_name {"test_input2.txt"}; // 95437
    // string file_name {"full_input.txt"}; // 1.000.000 - 2.000.000

    vector<vector<string>> lines {load_file(file_name)};

    vector<Dir> tree {create_tree(lines)};

    vector<Dir> dir_sizes {tree_crawler(tree)};

    int total_size {accumulate_dirs_sizes_if(dir_sizes, 100001)};

    cout << "Total size: " << total_size << endl;

    return 0;
}