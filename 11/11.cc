#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "MonkeyBusiness.cc"


using namespace std;


Monkey make_monkey(string const& monkey_id_line, string const& items_line,
                 string const& operation_line, string const& test_line,
                 string const& true_line, string const& false_line)
{
    istringstream monkey_id_stream {monkey_id_line};
    istringstream monkey_items {items_line};
    istringstream monkey_operation {operation_line};
    istringstream monkey_test {test_line};
    istringstream monkey_true {true_line};
    istringstream monkey_false {false_line};

    // get id
    // Monkey 0: // gets 0
    string trash;
    int id; 
    monkey_id_stream >> trash;
    monkey_id_stream >> id;

    // get queue of items
    // Starting items: 54, 65, 75, 74 // gets 54, 65, 75, 74
    queue<int> items;
    int item;
    char trash_comma;
    // eat Starting items:
    monkey_items >> trash >> trash;
    while(monkey_items >> item >> trash_comma)
    {
        items.push(item);
    }
    items.push(item);


    // get operation
    // Operation: new = old * 19
    monkey_operation >> trash >> trash >> trash >> trash;
    char operation_symbol;
    string value;
    monkey_operation >> operation_symbol;
    monkey_operation >> value;

    // get divisible value
    int test_division;
    monkey_test >> trash >> trash >> trash >> test_division;

    // get true_throw_to
    // get false_throw_to
    // If true: throw to monkey 2
    monkey_true >> trash >> trash >> trash >> trash >> trash;
    monkey_false >> trash >> trash >> trash >> trash >> trash;
    int true_throw_to;
    int false_throw_to;
    monkey_true >> true_throw_to;
    monkey_false >> false_throw_to;

    // cout << "MONKEY ID = " << id  << " DONE" << endl;
    // cout << "NR OF ITEMS = " << items.size() << endl;
    // cout << "operation = " << operation_symbol << " " << value << endl;
    // cout << "test if divisible by " << test_division << endl;
    // cout << "if True throw to  " << true_throw_to << endl;
    // cout << "if false throw to  " << false_throw_to << endl;
    // cout << endl;

    Monkey monke {Monkey(items, id, true_throw_to, false_throw_to, 
                 operation_symbol, value, test_division)};
    
    return monke;
};


MonkeyBusiness read_file(string file_name)
{
    ifstream file {file_name};
    string monkey_id_line, items_line, operation_line, 
           test_line, true_line, false_line, new_line{};
    vector<Monkey> all_monkeys {};
    // MonkeyBusiness mb {MonkeyBusiness(all_monkeys)};

    while(getline(file, monkey_id_line))
    {
        getline(file, items_line);
        getline(file, operation_line);
        getline(file, test_line);
        getline(file, true_line);
        getline(file, false_line);
        getline(file, new_line);

        Monkey monke {make_monkey(monkey_id_line, items_line, operation_line,
                     test_line, true_line, false_line)};
        all_monkeys.push_back(monke);
    }
    MonkeyBusiness mb {MonkeyBusiness(all_monkeys)};
    return mb;
}


// void monkey_circus(string file_name)
// {


// }


int main()
{
    MonkeyBusiness mb {read_file("test_input.txt")}; // 10605
    // MonkeyBusiness mb {read_file("full_input.txt")}; // 90294 

    mb.round_robin();

    int value {mb.calculate_monkey_business()};
    cout << "MONKEY BUSINESS VALUE = " << value << endl;

    return 0;
}