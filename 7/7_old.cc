#include <iostream>
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

        // print
        // copy(cbegin(command), cend(command),
        //     ostream_iterator<string>(cout, " "));
        // cout << endl;
    }
    return commands;
}


map<string, pair<int, string>> create_tree(vector<vector<string>> & all_commands)
{
    // name_of_dir, <size, parent>
    map<string, pair<int, string>> tree {};
    stack<string> cd_log {};
    cd_log.push("__ROOT__");

    // this can be changed to transform 100%
    for (vector<string> const & command : all_commands)
    {
        string arg1 {command[0]};
        string arg2 {command[1]};

        cout << arg1 << arg2 << endl;

        if (arg1 == "$")
        {
            if (arg2 == "cd")
            {
                if (command[2] != "..")
                {
                    tree.emplace(command[2], make_pair(0, cd_log.top()));
                    //tree[command[2]] = make_pair(0, cd_log.top());
                    cd_log.push(command[2]);
                } else 
                {
                    cd_log.pop();
                }
            } 
        } else 
        {
            if (arg1 != "dir")
            {
                cout << "stoi("<< arg1 << endl;
                int file_size {stoi(arg1)};
                tree[cd_log.top()].first += file_size;
            }
        }
    }

    return tree;
}


unordered_map<string, int> tree_crawler(map<string, pair<int, string>> & tree)
{
    unordered_map<string, int> dir_sizes{};

    for (auto & dir : tree)
    {
        string dir_name {dir.first};
        int current_size {dir.second.first};
        // int current_size {tree[dir_name].first};

        // cout << "DIR " << dir_name << " size " << current_size << endl;

        // auto add_my_children = [&dir_name] (map<string, pair<int, string>> cur_dir,
        //                                     int size)
        // {
        //     if(cur_dir.second.second == dir_name)
        //         return stoi(cur_dir.second.first);
        //     return 0;
        // };

        // int total = accumulate(cbegin(tree), cend(tree), current_size, add_my_children);

        for (auto const& possible_child : tree)
        {
            if (possible_child.second.second == dir_name)
            {
                // cout << "Found my child " << possible_child.first 
                //      << " adding size " << possible_child.second.first << endl;
                current_size += possible_child.second.first;
            }
        }
        // cout << "FINISHED - DIR " << dir_name << "size " << current_size << endl;
        dir_sizes.emplace(dir_name, current_size);
    }

    return dir_sizes;
}


int accumulate_dirs_sizes_if(unordered_map<string, int> & dirs, int max_size)
{

    auto check_size = [max_size] (int total_size, pair<string, int> dir) 
    { 
        int dir_size {dir.second};
        if (dir_size < max_size)
            return dir_size + total_size;
        return total_size;
    };

    return accumulate(begin(dirs), end(dirs), 0, check_size);
}


int accumulate_dirs_sizes_if2(unordered_map<string, int> & dirs, int max_size)
{
    int total_size;
    for (auto const& dir : dirs)
    {
        if(dir.second <= max_size)
        {
            total_size += dir.second;
        }
    }

    return total_size;

}


void print_tree(map<string, pair<int, string>> const& tree)
{
    for (auto const& node : tree)
    {
        cout << "DIR " << node.first << " SIZE " << node.second.first << " PARENT " <<
             node.second.second << endl;
    }

}





int main()
{
    // string file_name {"test_input.txt"}; // 95437
    // string file_name {"test_input2.txt"}; // 95437
    string file_name {"full_input.txt"}; // 1.000.000 - 2.000.000

    vector<vector<string>> lines {load_file(file_name)};

    map<string, pair<int, string>> tree {create_tree(lines)};
    print_tree(tree);

    cout << tree["/"].first << endl; // 2m+
    cout << tree["a"].second << endl; // "/"
    cout << tree["d"].first << endl; // "/"
    cout << tree["d"].second << endl; // "/"

    unordered_map<string, int> dir_sizes {tree_crawler(tree)};

    cout << "HOOOOO" << dir_sizes["zjghthcb"] << endl;

    int total_size {accumulate_dirs_sizes_if2(dir_sizes, 100001)};

    cout << total_size << endl;

    return 0;
}