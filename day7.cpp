#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int brute_force(const vector<int>& positions, const bool& use_increasing_cost) {
    
    int lowest_cost = 0x7FFFFFFF;
    int current_cost;

    for (const int& pos1 : positions) {
        
        current_cost = 0;
        
        for (const int& pos2 : positions) {

            if (use_increasing_cost) {
                int n = abs(pos2 - pos1);
                current_cost += n * (n + 1) / 2;
            } else {
                current_cost += abs(pos2 - pos1);
            }
        }
        
        if (current_cost < lowest_cost) {
            lowest_cost = current_cost;
        }
    }

    return lowest_cost;
}

int main() {

    ifstream f("day7_input.txt");

    vector<int> input;

    for (int pos; f >> pos;) {
        input.push_back(pos);
        f.ignore();
    }

    cout << "Part 1: " << brute_force(input, false) << endl;
    cout << "Part 2: " << brute_force(input, true) << endl;

    return 0;
}