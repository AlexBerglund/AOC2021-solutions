#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <set>

using namespace std;

bool invalid(int y, int x) {
    return (x < 0 || x > 9 || y < 0 || y > 9);
}

void flash(int y, int x, array<array<int, 10>, 10>& grid, const set<int>& flashed) {
    grid[y][x] = 0;
    for (int i = y-1; i <= y+1; i++) {
        for (int j = x-1; j <= x+1; j++) {
            bool already_flashed = flashed.find(i*10 + j) != flashed.end();
            if (i == y && j == x || invalid(i, j) || already_flashed) continue;
            grid[i][j]++;
        }
    }
}

int update_tick(array<array<int, 10>, 10>& grid, set<int>& flashed) {
    int flash_count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j]++;
            if (grid[i][j] > 9) {
                flash(i, j, grid, flashed);
                flashed.insert(i*10 + j);
                flash_count++;
            }
        }
    }
    return flash_count;
} 

int update_aftermath(array<array<int, 10>, 10>& grid, set<int>& flashed) {
    int flash_count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] > 9) {
                flash(i, j, grid, flashed);
                flashed.insert(i*10 + j);
                flash_count++;
            }
        }
    }
    return flash_count;
}

int part1(array<array<int, 10>, 10> grid) {
    set<int> flashed;
    int total_flashes = 0;
    int flash_count;
    
    for (int i = 0; i < 100; i++) {
    
        total_flashes += update_tick(grid, flashed);
        do {
            flash_count = update_aftermath(grid, flashed);
            total_flashes += flash_count;
        } while (flash_count);

        flashed.clear();
    }
    
    return total_flashes;
}

int part2(array<array<int, 10>, 10>& grid) {
    set<int> flashed;
    bool any_flashed;

    int step = 0;
    while (true) {
        step++;

        update_tick(grid, flashed);
        do {
            any_flashed = update_aftermath(grid, flashed);
        } while (any_flashed);

        if (flashed.size() == 100) return step;

        flashed.clear();
    }
}

int main() {

    array<array<int, 10>, 10> input;
    ifstream f("day11_input.txt");

    char num;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            f >> num;
            input[i][j] = num - '0';
        }
    }

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;
}