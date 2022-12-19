#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <exception>
#include <set>

using namespace std;

class Planck
{
public:
    Planck()
    : head{make_pair(0, 0)}, tail{make_pair(0, 0)}, visited_by_tail{}
    { 
        visited_by_tail.insert(tail);
        print_pos();
    };

    void move_right()
    {
        if(!is_tail_overlapping())
        {
            move_tail(0, 1);
        }
        head.second++;
        print_pos();
    }

    void move_up()
    {
        head.first++;
        lateral_move();

    }

// private:
    pair<int, int> head;
    pair<int, int> tail;

    set<pair<int, int>> visited_by_tail;

    void lateral_move()
    {
        int row_diff {abs(head.first) - abs(tail.second)};
        int column_diff {abs(head.first) - abs(tail.second)};

        if (row_diff == 1 && column_diff == 1)
        {
            return; // no need to move laterally, tail is adjacent
        } else if (row_diff == 2)
        {
            

        }

        
    } 

    void move_tail(int const row, int const column)
    {
        tail.first += row;
        tail.second += column;
        visited_by_tail.insert(tail);
    }

    bool is_tail_overlapping() const
    {
        return head == tail;
    }

    void print_pos() const
    {
        cout << "HEAD (" << head.first << " " << head.second << ") " << endl;
        cout << "TAIL (" << tail.first << " " << tail.second << ") " << endl;
    }

};


void move(Planck & planck, char direction, int distance)
{
    if (direction == 'R')
    {
        planck.move_right();
    }
}


int read_and_move(Planck & planck, string const& file_name)
{
    ifstream file{file_name};
    string line{};

    while(getline(file, line))
    {
        istringstream line_steram{line};
        char direction{};
        int distance{};

        line_steram >> direction;
        line_steram >> distance;
    }
}


int main()
{
    // store without matrix
    // keep track of coordinates for
    //  start, head, tail
    // put tail coordinates in a set of pair<int,int> // test if this works first

    Planck planck {Planck()};

    move(planck, 'R', 1);
    assert(make_pair(0,1) == planck.head);
    assert(make_pair(0,0) == planck.tail);


    move(planck, 'R', 1);
    assert(make_pair(0,2) == planck.head);
    assert(make_pair(0,1) == planck.tail);


    move(planck, 'R', 1);
    assert(make_pair(0,3) == planck.head);
    assert(make_pair(0,2) == planck.tail);


    move(planck, 'R', 1);
    assert(make_pair(0,4) == planck.head);
    assert(make_pair(0,3) == planck.tail);


    move(planck, 'U', 1);
    assert(make_pair(1,4) == planck.head);
    assert(make_pair(0,3) == planck.tail);


    return 0;
}