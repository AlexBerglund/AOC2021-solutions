#include <iostream>
#include <fstream>
#include <array>

using namespace std;

bool invalid(int y, int x) {
    return (x < 0 || x > 9 || y < 0 || y > 9);
}

void flash(int y, int x, array<array<int, 10>, 10>& grid, bool first_iter) {
    grid[y][x] = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i == y && j == x || invalid(i, j)) continue;

            if (!first_iter && grid[i][j] == 0) continue;

            if (grid[i][j] == 0 && i*10 + j < y*10 + x) continue;

            grid[i][j]++;
        }
    }
}

int update_tick(array<array<int, 10>, 10>& grid) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j]++;
            if (grid[i][j] > 9) {
                flash(i, j, grid, true);  
                count++;  
            }
        }
    }
    return count;
} 

int update_aftermath(array<array<int, 10>, 10>& grid) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] > 9) {
                flash(i, j, grid, false);
                count++;
            }
        }
    }
    return count;
}

bool all_zero(const array<array<int, 10>, 10>& grid) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] != 0) return false;
        }
    }
    return true;
}

int part1(array<array<int, 10>, 10> grid, int steps) {
    int total_count = 0;
    int count;
    while (steps > 0) {
        total_count += update_tick(grid);
        do {
            count = update_aftermath(grid);
            total_count += count;
        } while (count);
        steps--;
    }
    return total_count;
}

int part2(array<array<int, 10>, 10> grid) {
    int steps = 0;
    bool any_flashed;
    while (true) {
        steps++;
        update_tick(grid);
        do {
            any_flashed = update_aftermath(grid);
        } while (any_flashed);
        if (all_zero(grid)) return steps;
    }
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

    cout << "Part 1: " << part1(grid, 100) << endl;
    cout << "Part 2: " << part2(grid) << endl;

    return 0;
}