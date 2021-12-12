#include <iostream>
#include <fstream>
#include <array>

using namespace std;

bool invalid(int y, int x) {
    return (x < 0 || x > 9 || y < 0 || y > 9);
}

int flash(int y, int x, array<array<int, 10>, 10>& grid) {
    int count = 1;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            int& a = grid[i][j];
            if (i == y && j == x || invalid(i, j) || a == 10) continue;

            a++;

            if (a == 10) 
                count += flash(i, j, grid);
        }
    }
    return count;
}

int update(array<array<int, 10>, 10>& grid) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int& a = grid[i][j];

            if (a == 10) continue;

            a++;

            if (a == 10) 
                count += flash(i, j, grid);   
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == 10) grid[i][j] = 0;
        }
    }

    return count;
} 

int part1(array<array<int, 10>, 10> grid) {
    
    int count = 0;

    for (int i = 0; i < 100; i++) {
        count += update(grid);
    }

    return count;
}

int part2(array<array<int, 10>, 10> grid) {
    
    int steps = 0;
    int count;

    while (true) {
        steps++;
        count = update(grid);
        if (count == 100) return steps;
    }
    
    return steps;
}

int main() {

    array<array<int, 10>, 10> grid;
    ifstream f("input/day11_input.txt");

    char num;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            f >> num;
            grid[i][j] = num - '0';
        }
    }

    cout << "Part 1: " << part1(grid) << endl;
    cout << "Part 2: " << part2(grid) << endl;

    return 0;
}