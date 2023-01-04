#include <queue>
#include <algorithm>


using namespace std;


class Monkey
{
public:
    Monkey(queue<long long> & items, long long id, int true_throw_to,
           long long false_throw_to, char operation_type,
           string value, long long division)
        : items{items}, id{id}, true_throw_to{true_throw_to}, 
        false_throw_to{false_throw_to}, operation_type{operation_type},
        operation_value{}, division{division}, inspections {}, old_mode{false}
        {
            if (value == "old")
                old_mode = true;
            else
                operation_value = stol(value);

        };

    pair<long long, long long> toss()
    {
        long long item {items.front()};
        items.pop();

        item = recalculate_stress_for_item(item); // / 3;
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

    void add_to_items(long long item)
    {
        items.push(item);
    }

    long long get_nr_of_items() const
    {
        return items.size();
    }

    long long get_inspections() const
    {
        return inspections;
    }

private:
    queue<long long> items;
    long long const id;
    long long const true_throw_to;
    long long const false_throw_to;
    char const operation_type;
    long long operation_value;
    long long const division;
    long long inspections;
    bool old_mode;


    long long recalculate_stress_for_item(long long item)
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


    bool test_division(long long const stress)
    {
        return (stress % division) == 0;
    }
};



class MonkeyBusiness
{
public:
    MonkeyBusiness(vector<Monkey> & monkeys)
    :monkeys{monkeys}
    {};

    void round_robin()
    {
        cout << "IN ROUND ROBIND" << endl;
        size_t current_index {0};
        long long round {0};

        while(true)
        {
            Monkey & current_monkey {monkeys[current_index]};
            cout << "IN ROUND ROBIND" << endl;

            long long iterations {current_monkey.get_nr_of_items()};

            for(long long i {iterations}; i != 0; i--)
            {
                cout << " -- MONKEY " << current_index << endl;
                pair<long long, long long> item_to_monkey(current_monkey.toss());
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


    long long calculate_monkey_business()
    {
        vector<long long> total_inspections;
        transform(begin(monkeys), end(monkeys), back_inserter(total_inspections),
                  [] (Monkey const& monke) { return monke.get_inspections();});
        
        sort(begin(total_inspections), end(total_inspections), greater<long long>());

        return total_inspections[0] * total_inspections[1];
    }

private:
    vector<Monkey> monkeys;
};


