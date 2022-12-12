
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iterator>

using namespace std;

string get_line_from_file(string const& file_name) 
{
    ifstream file {file_name}; 
    string signal_line {};
    getline(file, signal_line);
    return signal_line;
}

template <typename T>
void print_container(T const& container)
{
    for (auto const& i : container)
    {
        cout << i;
    }
    cout << endl;
}


bool check_sequence_unique(vector<char> const& marker)
{
    set<char> marker_set {};
    copy(cbegin(marker), cend(marker), inserter(marker_set, begin(marker_set)));
    return marker.size() == marker_set.size();
}

int find_marker(istringstream & signal, size_t distinct_chars)
{
    vector<char> marker{};

    int counter {0};

    auto check_marker = [marker, &counter, distinct_chars] (char c) mutable
    { 
        marker.push_back(c);
        counter++;
        bool is_marker_unique {check_sequence_unique(marker)};

        if(is_marker_unique && marker.size() == distinct_chars)
        {
            return true;
        } else if(!is_marker_unique)
        {
            marker.erase(begin(marker));
        }

        return false;
    };

    find_if(istream_iterator<char>(signal), istream_iterator<char>(), check_marker);

    return counter;
}


int main()
{
    // istringstream signal {"mjqjpqmgbljsphdztnvjfqwrcgsmlb"};   // 19 - jpqm
    // istringstream signal {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"}; // 26 
    istringstream signal {get_line_from_file("full_input.txt")};  // 1655 / 2665 
    
    // int marker_index {find_marker(signal, 4)};
    int marker_index {find_marker(signal, 14)};

    cout << "Marker index: " << marker_index << endl;

    return 0;
}