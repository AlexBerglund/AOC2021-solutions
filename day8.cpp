#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

static string segcodes[10] = {"abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg"};

struct Entry {
    array<string, 10> input; 
    array<string, 4> output;
};

int get_digit(const string& input, const map<char, char>& mapping) {
    string decrypted;
    for (const char& c : input) {
        decrypted += mapping.find(c)->second;
    }
    
    sort(decrypted.begin(), decrypted.end());

    for (int i = 0; i < 10; i++) {
        if (segcodes[i].compare(decrypted) == 0) return i;
    }
    return -1;
}

char set_diff(set<char> s1, set<char> s2) {
    set<char> temp_set;
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(temp_set, temp_set.begin()));
    return *temp_set.begin();
}

set<char> set_uni(set<char> s1, set<char> s2) {
    set<char> uni_set;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(uni_set, uni_set.begin()));
    return uni_set;
}

/*
Algoritm:
    Hitta 1, 4, 7 och 8
    
    seg a = 7 - 1

    8-6
    8-0  -> [d, c, e]
    8-9

    seg e = [d, c, e] - 4

    Hitta 9 (enda av längd 6 som inte innehåller seg e)

    seg g = 9 - 4 - seg a

    Hitta 2 (enda av längd 5 som innehåller seg e)  

    3 = 2 - seg e + 1

    5 (den enda andra av längd 5)

    seg b = 9 - 3 

    seg c = 8 - 5 - seg e

    seg f = 8 - 2 - seg b

    seg d sista kvar
*/
map<char, char> build_map(const array<string, 10>& input) {

    array<set<char>, 10> enc_seg;
    map<char, char> mapped;

    set<char> temp_set;
    for (const string& code : input) {
        if (code.size() == 2) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            enc_seg[1] = temp_set;
        } else if (code.size() == 3) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            enc_seg[7] = temp_set;
        } else if (code.size() == 4) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            enc_seg[4] = temp_set;
        } else if (code.size() == 7) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            enc_seg[8] = temp_set;
        }

        temp_set.clear();        
    }

    char mapped_a = set_diff(enc_seg[7], enc_seg[1]);
    mapped.emplace(mapped_a, 'a');

    set<char> dce;
    for (const string& code : input) {
        if (code.size() == 6) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            dce.insert(set_diff(enc_seg[8], temp_set));
            temp_set.clear();
        }
    }

    char mapped_e = set_diff(dce, enc_seg[4]);
    mapped.emplace(mapped_e, 'e');

    for (const string& code : input) {
        if (code.size() == 6 && code.find(mapped_e) == string::npos) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            enc_seg[9] = temp_set;
            temp_set.clear();
            break;
        }
    }

    temp_set = enc_seg[9];
    temp_set.erase(mapped_a);
    char mapped_g = set_diff(temp_set, enc_seg[4]);
    mapped.emplace(mapped_g, 'g');
    temp_set.clear();

    for (const string& code : input) {
        if (code.size() == 5 && code.find(mapped_e) != string::npos) {
            for (const char& c : code) {
                temp_set.insert(c);
            }
            enc_seg[2] = temp_set;
            temp_set.clear();
            break;
        }
    }

    temp_set = set_uni(enc_seg[2], enc_seg[1]);
    temp_set.erase(mapped_e);
    enc_seg[3] = temp_set;
    temp_set.clear();

    for (const string& code : input) {
        if (code.size() == 5) {
            for (const char& c : code) {
                temp_set.insert(c);
            }

            if (temp_set == enc_seg[2] || temp_set == enc_seg[3]) {
                temp_set.clear();
                continue;
            }

            enc_seg[5] = temp_set;
            temp_set.clear();
            break;
        }
    }

    char mapped_b = set_diff(enc_seg[9], enc_seg[3]);
    mapped.emplace(mapped_b, 'b');


    temp_set = enc_seg[8];
    temp_set.erase(mapped_e);
    char mapped_c = set_diff(temp_set, enc_seg[5]);
    mapped.emplace(mapped_c, 'c');
    temp_set.clear();

    temp_set = enc_seg[8];
    temp_set.erase(mapped_b);
    char mapped_f = set_diff(temp_set, enc_seg[2]);
    mapped.emplace(mapped_f, 'f');
    temp_set.clear();

    for (const char& c : "abcdefg") {
        bool used = false;
        for (const auto& [c1, _] : mapped) {
            if (c1 == c) {
                used = true;
                break;
            }
        }
        if (!used) {
            mapped.emplace(c, 'd');
            break;
        }
    }
    
    return mapped;
}

int solve(const Entry& entry) {
    
    auto mapping = build_map(entry.input);
    
    int number = 0;
    int factor = 1000;
    for (const auto& code : entry.output) {
        number += get_digit(code, mapping) * factor;
        factor /= 10;
    }

    return number;
}

int part1(const vector<Entry>& puzzle_input) {
    int count = 0;

    for (const auto& [_, output] : puzzle_input) {
        for (const auto& str : output) {
            switch(str.size()) {
                case 2:
                case 3:
                case 4:
                case 7:
                    count++;
            }
        }
    }

    return count;
}


int part2(const vector<Entry>& puzzle_input) {
    int sum = 0;
    
    for (auto& entry : puzzle_input) {
        sum += solve(entry);
    }
    
    return sum;
}

int main() {

    ifstream f("day8_input.txt");
    vector<Entry> puzzle_input;

    string str;
    array<string, 10> input;
    array<string, 4> output;
    while (f >> str) {
        input[0] = str;
        
        for (int i = 1; i < 10; i++) {
            f >> str;
            input[i] = str;;
        }

        f.ignore(3);
        
        for (int i = 0; i < 4; i++) {
            f >> str;
            output[i] = str;
        }

        puzzle_input.push_back({input, output});
    } 

    std::cout << "Part 1: " << part1(puzzle_input) << endl;
    std::cout << "Part 2: " << part2(puzzle_input) << endl;

}