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

    Dir(string name, int size, string parent)
    : name{name}, size{size}, parent{parent}
    {};

    void print_dir() const
    {
        cout << "[Dir: " << name << " size: " << size << " parent " << parent <<endl;
    };
};

int get_dir_from_tree(vector<Dir> const& dirs, string const& target)
{
    int counter{0};
    for (auto const& dir : dirs)
    {
        if(dir.name == target)
        {
            return counter;
        }


        counter++;
    }

    throw runtime_error("Get_dir_from_tree could not be found");
    return counter;
}


vector<Dir> create_tree(vector<vector<string>> & all_commands)
{
    vector<Dir> tree {};
    stack<string> cd_log {};
    cd_log.push("__ROOT__");

    Dir current {Dir("_ROOT_", 0, "")};
    tree.push_back(current);

    // Dir current {tree[get_dir_from_tree(tree, cd_log.top())]};
    // this can be changed to transform 100%
    for (vector<string> command : all_commands)
    {
        string arg1 {command[0]};
        string arg2 {command[1]};


        if (arg1 == "$")
        {
            if (arg2 == "cd")
            {
                if (command[2] != "..")
                {
                    Dir new_dir {Dir(command[2], 0, current.name)};
                    tree.push_back(new_dir);
                    cd_log.push(new_dir.name);
                    current = tree[get_dir_from_tree(tree, cd_log.top())];
                    cout << "On " << current.name << endl;
                } else 
                {
                    cd_log.pop();
                    current = tree[get_dir_from_tree(tree, cd_log.top())];
                    cout << "Back On " << current.name << endl;
                }
            } 
        } else 
        {
            if (arg1 != "dir")
            {
                int file_size {stoi(arg1)};
                cout << "adding file " << arg2 << " " << file_size << " to " << current.name << endl;
                Dir & cur = tree[get_dir_from_tree(tree, cd_log.top())];
                cur.size += file_size;
            }
        }
    }

    for (auto const& dir : tree)
    {
        dir.print_dir();
    }

    return tree;
}


vector<Dir> tree_crawler(vector<Dir> & tree)
{
    vector<Dir> dir_sizes{};

    for (auto & dir : tree)
    {
        string dir_name {dir.name};
        int current_size {dir.size};

        // accumulate possible here
        for (auto & possible_child : tree)
        {
            if (possible_child.parent == dir_name)
            {
                current_size += possible_child.size;
            }
        }
        cout << "FINISHED - DIR " << dir_name << "size " << current_size << endl;
        Dir done_dir{Dir(dir_name, current_size, "")};
        dir_sizes.push_back(done_dir);
    }

    return dir_sizes;
}


int accumulate_dirs_sizes_if(vector<Dir> & dirs, int max_size)
{

    auto check_size = [max_size] (int total_size, Dir dir) 
    { 
        if (dir.size < max_size)
            return dir.size + total_size;
        return total_size;
    };

    return accumulate(begin(dirs), end(dirs), 0, check_size);
}


int main()
{
    // string file_name {"test_input.txt"}; // 95437
    // string file_name {"test_input2.txt"}; // 95437
    string file_name {"full_input.txt"}; // 1.000.000 - 2.000.000

    vector<vector<string>> lines {load_file(file_name)};

    vector<Dir> tree {create_tree(lines)};

    vector<Dir> dir_sizes {tree_crawler(tree)};

    int total_size {accumulate_dirs_sizes_if(dir_sizes, 100001)};

    cout << "Total size: " << total_size << endl;

    return 0;
}