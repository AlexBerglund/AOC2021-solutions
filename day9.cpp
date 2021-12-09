#include <iostream>
#include <fstream>
#include <array>

using namespace std;

bool valid_point(int x, int y) {
    if (x < 0 || x >= 100 || y < 0 || y >= 100)
        return false;
    else return true;
}

bool is_lowpoint(int x, int y, const array<array<int, 100>, 100>& map) {
    int point = map[x][y];

    if (valid_point(x-1, y) && map[x-1][y] <= point) return false;
    if (valid_point(x+1, y) && map[x+1][y] <= point) return false;
    if (valid_point(x, y-1) && map[x][y-1] <= point) return false;
    if (valid_point(x, y+1) && map[x][y+1] <= point) return false;

    return true;
}

int flow_with_water(int x, int y, const array<array<int, 100>, 100>& map) {
    if (is_lowpoint(x, y, map)) return x*100 + y;

    int point = map[x][y];
    if (valid_point(x-1, y) && map[x-1][y] < point) 
        return flow_with_water(x-1, y, map);
    else if (valid_point(x+1, y) && map[x+1][y] < point) 
        return flow_with_water(x+1, y, map);
    else if (valid_point(x, y-1) && map[x][y-1] < point) 
        return flow_with_water(x, y-1, map);
    else return flow_with_water(x, y+1, map);
}

int find_largest(const array<array<int, 100>, 100> basin_sizes) {
    int largest = 0;
    int index;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (basin_sizes[i][j] > largest) {
                largest = basin_sizes[i][j];
                index = i*100 + j;
            }
        }
    }
    return index;
}

int part1(const array<array<int, 100>, 100>& map) {
    int risk_level_sum = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (is_lowpoint(i, j, map)) {
                risk_level_sum += map[i][j] + 1;
            }
        }
    }
    return risk_level_sum;
}

int part2(const array<array<int, 100>, 100>& map) {
    auto basin_sizes = *(new array<array<int, 100>, 100>());

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (map[i][j] == 9) continue;
            int low_point = flow_with_water(i, j, map);
            basin_sizes[low_point / 100][low_point % 100]++;
        }
    }

    int product = 1;

    int first = find_largest(basin_sizes);
    product *= basin_sizes[first / 100][first % 100];
    basin_sizes[first / 100][first % 100] = 0;

    int second = find_largest(basin_sizes);
    product *= basin_sizes[second / 100][second % 100];
    basin_sizes[second / 100][second % 100] = 0;

    int third = find_largest(basin_sizes);
    product *= basin_sizes[third / 100][third % 100];

    return product;
}

int main() {

    ifstream f("day9_input.txt");

    auto map = *(new array<array<int, 100>, 100>());

    char point;
    for (int i = 0, j = 0; f >> point; j++) {
        map[i][j] = point - '0';
        if (j == 99) {
            j = -1;
            i++;
        }
    }

    cout << "Part 1: " << part1(map) << endl;
    cout << "Part 2: " << part2(map) << endl;
    
}