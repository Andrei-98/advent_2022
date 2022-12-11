// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// These functions have been replaced by better ones so why are you even here?


// int find_overlapping_pairs(ifstream & file)
// {
//     int overlapping_teams{};
//     string line{};
//     regex numbers_regex{"(\\d+)-(\\d+)\\,(\\d+)-(\\d+)"};
//     smatch match{};
//     while(getline(file, line))
//     {
//         regex_match(line, match, numbers_regex);
//         int first {stoi(match[1].str())};
//         int second {stoi(match[2].str())};
//         int third {stoi(match[3].str())};
//         int fourth {stoi(match[4].str())};

//         if (check_if_ranges_overlap(first, second, third, fourth))
//             overlapping_teams++;

//     };

//     return overlapping_teams;
// }