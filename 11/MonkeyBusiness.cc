#include <queue>
#include <algorithm>


using namespace std;


class Monkey
{
public:
    Monkey(queue<int> & items, int id, int true_throw_to,
           int false_throw_to, char operation_type,
           string value, int division)
        : items{items}, id{id}, true_throw_to{true_throw_to}, 
        false_throw_to{false_throw_to}, operation_type{operation_type},
        operation_value{}, division{division}, inspections {}, old_mode{false}
        {
            if (value == "old")
                old_mode = true;
            else
                operation_value = stoi(value);

        };

    pair<int, int> toss()
    {
        int item {items.front()};
        items.pop();

        item = recalculate_stress_for_item(item) / 3; // / 3;
        inspections++;

        if(test_division(item))
        { 
            cout << "MONKEY id " << id << " TOSSING " << item << " to " <<  true_throw_to << endl;
            return make_pair(item, true_throw_to);
        }
        else
        {
            cout << "MONKEY id " << id << " TOSSING " << item << " to " << false_throw_to << endl;
            return make_pair(item, false_throw_to);
        }
    }

    void add_to_items(int item)
    {
        items.push(item);
    }

    int get_nr_of_items() const
    {
        return items.size();
    }

    int get_inspections() const
    {
        return inspections;
    }

private:
    queue<int> items;
    int const id;
    int const true_throw_to;
    int const false_throw_to;
    char const operation_type;
    int operation_value;
    int const division;
    int inspections;
    bool old_mode;


    int recalculate_stress_for_item(int item)
    {
        if(old_mode)
            operation_value = item;
        switch (operation_type)
        {
            case '+':
                return item + operation_value;
            case '-':
                return item - operation_value;
            case '*':
                return item * operation_value;
            case '/':
                return item / operation_value;
            default:
                throw runtime_error("UNKNOWN OPERATION TYPE");
        }

    }


    bool test_division(int const stress)
    {
        return (stress % division) == 0;
    }
};



class MonkeyBusiness
{
public:
    MonkeyBusiness(vector<Monkey> & monkeys)
    :monkeys{monkeys}, total_inspections{} 
    {};

    void round_robin()
    {
        cout << "IN ROUND ROBIND" << endl;
        size_t current_index {0};
        int round {0};

        while(true)
        {
            Monkey & current_monkey {monkeys[current_index]};
            cout << "IN ROUND ROBIND" << endl;

            int iterations {current_monkey.get_nr_of_items()};

            for(int i {iterations}; i != 0; i--)
            {
                cout << " -- MONKEY " << current_index << endl;
                pair<int, int> item_to_monkey(current_monkey.toss());
                monkeys[item_to_monkey.second].add_to_items(item_to_monkey.first);
            }

            cout << "DONE " << monkeys[current_index].get_nr_of_items() << endl;

            current_index++;
            if(current_index == monkeys.size())  
            {
                current_index = 0;
                round++;
                cout << "round incresead " << round << endl;
                if (round >= 20)
                {
                    break;
                }
            }

        }
    }


    int calculate_monkey_business()
    {
        // for (auto const & i : monkeys)Jjj
        // {
        //     cout << i.get_inspections() << endl;
        // }
        transform(begin(monkeys), end(monkeys), back_inserter(total_inspections),
                  [] (Monkey const& monke) { return monke.get_inspections();});
        
        int largest, second_largest {};

        for (auto i : total_inspections)
        {
            if(i > largest) 
            {
                second_largest = largest;
                largest = i;
            } else if (i > second_largest)
            {
                second_largest = i;
            }
        }
        cout << largest << " " << second_largest << endl;

        return largest * second_largest;
    }

private:
    vector<Monkey> monkeys;
    vector<int> total_inspections;
};


