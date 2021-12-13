#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <tuple>
#include <array>

using namespace std;

void fold_x(set<tuple<int, int>>& dots, int x_coord) {
    
    auto dots_copy = new set<tuple<int, int>>(dots);
    dots.clear();

    for (const auto& dot : *dots_copy) {
        auto& [x, y] = dot;
        if (x <= x_coord) {
            dots.emplace(dot);
        } else {
            dots.emplace(x - (x - x_coord)*2, y);
        }
    }

    delete dots_copy;
}

void fold_y(set<tuple<int, int>>& dots, int y_coord) {
    
    auto dots_copy = new set<tuple<int, int>>(dots);
    dots.clear();

    for (const auto& dot : *dots_copy) {
        auto& [x, y] = dot;
        if (y <= y_coord) {
            dots.emplace(dot);
        } else {
            dots.emplace(x, y - (y - y_coord)*2);
        }
    }

    delete dots_copy;
}

int part1(const set<tuple<int, int>>& dots, const tuple<int, int>& folding) {

    auto& [axis, coord] = folding;
    auto folded = new set<tuple<int, int>>(dots);

    if (axis == 'x') {
        fold_x(*folded, coord);
    } else {
        fold_y(*folded, coord);
    }    

    int size = folded->size();
    delete folded;
    return size;
}

void part2(const set<tuple<int, int>>& dots, const vector<tuple<char, int>>& folding) {

    auto folded = new set<tuple<int, int>>(dots);

    for (auto& [axis, coord] : folding) {
        if (axis == 'x') {
            fold_x(*folded, coord);
        } else {
            fold_y(*folded, coord);
        }    
    }

    auto grid = new int[6][40];
    for (auto& [x, y] : *folded) {
        grid[y][x] = 1;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            grid[i][j] ? cout << '#' : cout << ' ';
        }
        cout << endl;
    }

    delete folded;
    delete grid;
}

int main() {

    ifstream f("input/day13_input.txt");

    auto dots = *(new set<tuple<int, int>>());
    int x;
    int y; 
    while (f >> x && f.ignore() && f >> y) {
        dots.emplace(x, y);

        if (f.ignore() && f.peek() == '\n') break;
    }
    
    vector<tuple<char, int>> folding;
    char axis;
    int coord;
    while (f.ignore(11) && f >> axis && f.ignore() && f >> coord) {
        folding.emplace_back(axis, coord);
    }

    cout << "Part 1: " << part1(dots, folding.at(0)) << endl;
    cout << "Part 2: " << endl;
    part2(dots, folding);
}