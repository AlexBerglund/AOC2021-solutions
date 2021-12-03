#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

int part1(vector<tuple<string, int>>& input) {
    
    int h = 0;
    int d = 0;

    for (auto [direction, value] : input) {
       
        if (direction == "forward") {
            h += value;
        } else if (direction == "up") {
            d -= value;
        } else if (direction == "down") {
            d += value;
        }
    }

    return h * d;
}

int part2(vector<tuple<string, int>>& input) {

    int h = 0;
    int d = 0;
    int aim = 0;

    for (auto [direction, value] : input) {

        if (direction == "forward") {
            h += value;
            d += aim * value;
        } else if (direction == "up") {
            aim -= value;
        } else if (direction == "down") {
            aim += value;
        }
    }

    return h * d;
}

int main() {
    
    fstream f("day2_input.txt");

    string direction;
    int value;
    vector<tuple<string, int>> input;
    while (f >> direction >> value) {
        input.emplace_back(direction, value);
    }

    std::cout << "Part1: " << part1(input) << std::endl;
    std::cout << "Part2: " << part2(input) << std::endl;
    
    return 0;
}