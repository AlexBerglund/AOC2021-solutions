#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

void update(array<long, 9>& state_count) {
    long zero_count = state_count[0];
    for (int i = 0; i < 8; i++) {
        state_count[i] = state_count[i+1];
    }
    state_count[6] += zero_count;
    state_count[8] = zero_count;
}

long count_fish(const array<long, 9>& state_count) {
    long num_fish = 0;
    for (auto& state : state_count) {
        num_fish += state;
    }
    return num_fish;
}

long simulate(array<long, 9> fish_states, int days) {
    for (int i = 0; i < days; i++) {
        update(fish_states);
    }
    return count_fish(fish_states);
}

int main() {

    ifstream f("day6_input.txt");

    array<long, 9> fish_states = {0,0,0,0,0,0,0,0,0};

    for (int state; f >> state;) {
        fish_states[state]++;
        f.ignore();
    }

    cout << "Part 1: " << simulate(fish_states, 80) << endl;    
    cout << "Part 2: " << simulate(fish_states, 256) << endl;    

    return 0;
}