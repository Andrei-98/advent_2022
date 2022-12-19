#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


class CPU
{
public:
    CPU()
    : cycle {0}, x_reg{1}, total_sum{0}
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

    void exec_cycle()
    {
        cycle++;
        if (cycle == 20 || cycle == 60 || cycle == 100 
             || cycle == 140 || cycle == 180 || cycle == 220)
        {
            total_sum += (x_reg * cycle);
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


int cpu_simulator(string const& file_name)
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
    return cpu.get_total_sum();
}


int main()
{
    // cpu_simulator("test_input.txt"); // 13140
    int total {cpu_simulator("full_input.txt")}; // 17180
    cout << "Total sum of signals is " << total << endl; 
    return 0;
}