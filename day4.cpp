#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <optional>

using namespace std;
using Board = vector<tuple<int, bool>>;

void updateBoards(vector<Board>& boards, int current) {
    for (auto& board : boards) {
        for (auto& [num, marked] : board) {
            if (num == current) marked = true;
        }
    }
}

optional<Board> getWinner(vector<Board> boards) {
    for (auto& board : boards) {
        // check rows
        for (int i = 0; i < 25; i += 5) {
            int j;
            for (j = i; j < i + 5; j++) {
                auto& [_, marked] = board.at(j);
                if (!marked) break;
            }
            if (j == i + 5) return board;
        }

        // check columns
        for (int i = 0; i < 5; i++) {
            int j;
            for (j = i; j < i + 25; j += 5) {
                auto& [_, marked] = board.at(j);
                if (!marked) break;
            }
            if (j == i + 25) return board;
        }
    }

    return {};
}

int sum_of_unmarked(const Board& board) {
    int sum = 0;
    for (auto& [num, marked] : board) {
        if (!marked) sum += num;
    }
    return sum;
}

int part1(const vector<int>& numbers, vector<Board> boards) {

    for (int current : numbers) {

        updateBoards(boards, current);

        optional<Board> board = getWinner(boards);
        if (board.has_value()) {
            return sum_of_unmarked(board.value()) * current;
        }
    }

    return -1;
}

int part2(const vector<int>& numbers, vector<Board> boards) {

    for (int current : numbers) {
        
        updateBoards(boards, current);
        
        optional<Board> board = getWinner(boards);
        while (board.has_value()) {
            if (boards.size() == 1) {
                return sum_of_unmarked(board.value()) * current;
            }

            for (auto iter = boards.begin(); iter < boards.end(); iter++) {
                if (*iter == board) {
                    boards.erase(iter);
                }
            }

            board = getWinner(boards);
        }
    }

    return -1;
    
}

int main() {
    
    ifstream f("day4_input.txt");

    vector<int> numbers;
    vector<Board> boards;

    for (int num; f >> num;) {
        numbers.push_back(num);
        if (f.peek() == ',') f.ignore();
        else if (f.peek() == '\n') break;
    }

    Board board = *(new Board());
    for (int num, count = 1; f >> num; count++) {
        board.emplace_back(num, false);

        if (count == 25) {
            boards.push_back(board);
            board = *(new Board());
            count = 0;
        }
    }

    cout << part1(numbers, boards) << endl;
    cout << part2(numbers, boards) << endl;
}
