#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iterator>
#include <unordered_map>
#include <stack>

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


// crawl through the input and crate a map
unordered_map<string, pair<int, string>> create_tree(vector<vector<string>> & all_commands)
{
    // name_of_dir, <size, parent>
    unordered_map<string, pair<int, string>> tree {};
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
                    tree[command[2]] = make_pair(0, cd_log.top());
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


int tree_crawler(unordered_map<string, pair<int, string>> const& tree)
{
    unordered_map<string, int> dir_sizes{};
    for (auto const& dir : tree)
    {
        string dir_name {dir.first};
        int current_size {dir.second.first};
        string parent {dir.second.second};

    }
}


int main()
{
    string file_name {"test_input.txt"}; // 95437

    vector<vector<string>> lines {load_file(file_name)};

    unordered_map<string, pair<int, string>> tree {create_tree(lines)};

    cout << tree["/"].first << endl; // 2m+
    cout << tree["a"].second << endl; // "/"
    cout << tree["d"].first << endl; // "/"
    cout << tree["d"].second << endl; // "/"

    int total_sieze {tree_crawler(tree)};


    return 0;
}