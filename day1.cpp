#include <iostream>
#include <fstream>
#include <vector>

int part1(const std::vector<int>& input) {

    int countLarger = 0;

    for (int i = 1; i < input.size(); i++) {
        if (input.at(i) > input.at(i-1)) {
            countLarger++;
        }
    }

    return countLarger;
}

int part2(const std::vector<int>& input) {

    int previousSum = -1;
    int currentSum;
    int countLarger = 0;
    
    for (int i = 0; i < input.size() - 2; i++) {
        currentSum = input.at(i) + input.at(i+1) + input.at(i+2);
        if (currentSum > previousSum && previousSum != -1) {
            countLarger++;
        }
        previousSum = currentSum;
    }

    return countLarger;
}

int main() {

    std::ifstream f("day1_input.txt");

    int value;
    std::vector<int> input;
    while (f >> value) input.push_back(value);

    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;

    return 0;
}
