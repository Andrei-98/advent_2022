#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

// x controls the horizontal pos of the sprite
// sprite is 3 pixels wide
// x is the horizontal position of the middle of the sprite
// crt draw a pixel per cycle
class CPU
{
public:
    CPU()
    : cycle {0}, x_reg{1}, total_sum{0}, screen{}
    {}

    void addr(int op)
    {
        exec_cycle();
        exec_cycle();
        x_reg += op;
    }

    void noop() { exec_cycle(); }

    int get_total_sum() { return total_sum; }

private:
    int cycle;
    int x_reg; 
    int total_sum;
    vector<char> screen;

    void exec_cycle()
    {
        if (cycle == x_reg || cycle - 1 == x_reg || cycle + 1 == x_reg)
        {
            screen.push_back('#');
        }
        else
        {
            screen.push_back('.');
        }
        cycle++;

        if (cycle == 40)
        {
            copy(begin(screen), end(screen), ostream_iterator<char>(cout));
            cout << endl;
            screen.clear();
            cycle = 0;
        }
    }
};


void process_command(CPU & cpu, string const& command, int const value)
{
    if(command == "noop")
        cpu.noop();
    else 
        cpu.addr(value);
}


void cpu_simulator(string const& file_name)
{
    CPU cpu {CPU()};
    ifstream file {file_name};
    string line {};

    while(getline(file, line))
    {
        istringstream line_stream {line};
        string command {};
        int value {};

        line_stream >> command;
        line_stream >> value;

        process_command(cpu, command, value);
    }
}


int main()
{
    cpu_simulator("test_input.txt"); // 13140
    cpu_simulator("full_input.txt"); // 17180
    return 0;
}