#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int part1(const vector<int>& input) {
    int gamma = 0;
    int power = 1;
    int bit;
    int ones;

    for (int i = 0; i < 11; i++) {
        
        ones = 0;
        
        for (int j = 0; j < input.size(); j++) {
            bit = (input.at(j) >> i) & 1;
            ones += bit;
        }
        
        if (ones >= input.size()/2)
            gamma += power;

        power *= 2;
    }

    int epsilon = ~gamma & 0xFFF;
    return gamma * epsilon;
}

int oxygen_rating(const vector<int>& input, int bitpos) {

    if (input.size() == 1)
        return input.front();

    vector<int> leading_ones;
    vector<int> leading_zeros;

    int bit;
    for (int i = 0; i < input.size(); i++) {
        bit = (input.at(i) >> bitpos) & 1;
        if (bit) leading_ones.push_back(input.at(i));
        else leading_zeros.push_back(input.at(i));
    }
    
    if (leading_ones.size() >= leading_zeros.size()) {
        return oxygen_rating(leading_ones, bitpos - 1);
    } else {
        return oxygen_rating(leading_zeros, bitpos - 1);
    }
}

int co2_rating(const vector<int>& input, int bitpos) {
    if (input.size() == 1)
        return input.front();

    vector<int> leading_ones;
    vector<int> leading_zeros;

    int bit;
    for (int i = 0; i < input.size(); i++) {
        bit = (input.at(i) >> bitpos) & 1;
        if (bit) leading_ones.push_back(input.at(i));
        else leading_zeros.push_back(input.at(i));
    }
    
    if (leading_ones.size() < leading_zeros.size()) {
        return co2_rating(leading_ones, bitpos - 1);
    } else {
        return co2_rating(leading_zeros, bitpos - 1);
    }
}

int part2(const vector<int>& input) {
     return oxygen_rating(input, 11) * co2_rating(input, 11);
}

int main() {
    fstream f("day3_input.txt");

    string str;
    int num;
    int bit;
    int power;
    vector<int> input;
    while (getline(f, str)) {
        num = 0;
        power = 1;
        for (int i = 0; i < str.length(); i++) {
            bit = (str.at(str.length() - 1 - i) - '0');
            num += bit * power;
            power *= 2;
        }
        input.push_back(num);
    }
        
    cout << "Part1: " << part1(input) << endl;
    cout << "Part2: " << part2(input) << endl;
}