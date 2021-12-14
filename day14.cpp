#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(const pair<char, long>& left, const pair<char, long>& right) {
    return left.second < right.second;
}

template<typename T> void update(map<T, long>& elem_count, const T& elem, long count) {
    auto iter = elem_count.find(elem);
    if (iter == elem_count.end()) {
        elem_count.emplace(elem, count);
    } else {
        iter->second += count;
    }
}

long simulate(const vector<char>& polymer, const map<pair<char, char>, char>& pairs, int steps) {
    map<pair<char, char>, long> unique_pairs;
    map<pair<char, char>, long> new_unique_pairs;
    map<char, long> count_occur;

    pair<char, char> new_pair;
    for (int i = 0; i < polymer.size() - 1; i++) {
        new_pair = {polymer[i], polymer[i+1]};
        update(unique_pairs, new_pair, 1);
    }

    for (int i = 0; i < steps; i++) {
    
        for (auto& entry : unique_pairs) {
            auto& [unique_pair, count] = entry;
            auto& [c1, c2] = unique_pair;

            char c = pairs.find(unique_pair)->second;
            
            new_pair = {c1, c};
            update(new_unique_pairs, new_pair, count);
            new_pair = {c, c2};
            update(new_unique_pairs, new_pair, count);

            if (i == steps - 1) {
                update(count_occur, c1, count);
                update(count_occur, c, count);    
            }
        }         

        unique_pairs = new_unique_pairs;
        new_unique_pairs.clear();
    }

    long min = min_element(count_occur.begin(), count_occur.end(), compare)->second;
    long max = max_element(count_occur.begin(), count_occur.end(), compare)->second;

    return max - min + 1;
}

int main() {

    ifstream f("input/day14_input.txt");

    vector<char> polymer;
    map<pair<char, char>, char> pairs;

    char c1, c2, c3;

    while (f >> c1) {
        polymer.push_back(c1);
        if (f.peek() == '\n') break;
    }

    while (f >> c1 && f >> c2 && f.ignore(4) && f >> c3) {
        pairs.emplace(pair(c1, c2), c3);
    }

    std::cout << "Part 1: " << simulate(polymer, pairs, 10) << endl;
    std::cout << "Part 2: " << simulate(polymer, pairs, 40) << endl;

}
