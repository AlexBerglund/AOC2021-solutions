#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Line {
public:
    int x1, x2, y1, y2;

    bool is_diagonal() {
        return x1 != x2 && y1 != y2;
    }

    bool is_horizontal() {
        return y1 == y2;
    }
};

int count_overlaps(const vector<Line>& input, bool use_diagonals) {
    
    auto grid = new int[1000 * 1000];

    for (Line line : input) {

        if (line.is_diagonal()) {
            if (!use_diagonals) continue;

            int x = line.x1;
            int y = line.y1;
            int end_x = line.x2;
            int end_y = line.y2;
            int x_dir = x - end_x > 0 ? -1 : 1;
            int y_dir = y - end_y > 0 ? -1 : 1;

            while (x != end_x + x_dir) {
                grid[x + y*1000]++;
                x += x_dir;
                y += y_dir;
            }

        } else if (line.is_horizontal()) {
            int x = line.x1;
            int y = line.y1;
            int end_x = line.x2;
            int dir = x > end_x ? -1 : 1;

            while (x != end_x + dir) {
                grid[x + y*1000]++;
                x += dir;
            }

        } else {
            int x = line.x1;
            int y = line.y1;
            int end_y = line.y2;
            int dir = y > end_y ? -1 : 1;

            while (y != end_y + dir) {
                grid[x + y*1000]++;
                y += dir;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < 1000000; i++) {
        if (grid[i] >= 2) count++;
    }

    delete[] grid;

    return count;
}

int part1(const vector<Line>& input) {
    return count_overlaps(input, false);
}

int part2(const vector<Line>& input) {
    return count_overlaps(input, true);
}

int main() {

    ifstream f("day5_input.txt");

    vector<Line> input;

    Line line;
    while (f >> line.x1) {
        f.ignore();
        f >> line.y1;
        f.ignore(4);
        f >> line.x2;
        f.ignore();
        f >> line.y2;

        input.push_back(line);
    }

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;

    return 0;
}