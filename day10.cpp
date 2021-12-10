#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <optional>
#include <algorithm>

using namespace std;

bool is_opening(const char& c) {
    string openings = "([{<";
    return openings.find(c) != string::npos;
}

char reverse(const char& c) {
    switch (c) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        default:  return '<'; 
    }
}

optional<char> find_first_illegal(const string& line) {
    
    stack<char> openings;

    for (const char& c : line) {
        if (is_opening(c)) {
            openings.push(c);
        } else {
            if (openings.top() != reverse(c)) return c;  
            openings.pop();
        }
    }

    return {};
}

optional<string> get_completion_string(const string& line) {
    
    stack<char> openings;

    for (const char& c : line) {
        if (is_opening(c)) {
            openings.push(c);
        } else {
            if (openings.top() != reverse(c)) return {};
            openings.pop();
        }
    }

    string completion;
    while (!openings.empty()) {
        completion += reverse(openings.top());
        openings.pop();
    }

    return completion;
}

long score(const string& closing) {
    
    long score = 0;
    
    for (const char& c : closing) {
        score *= 5;
        switch (c) {
            case ')':
                score += 1;
                break;
            case ']':
                score += 2;
                break;
            case '}':
                score += 3;
                break;
            case '>':
                score += 4;
        }
    }
    
    return score;
}

int part1(const vector<string>& input) {

    int points = 0;
    optional<char> illegal;

    for (const string& line : input) {
        illegal = find_first_illegal(line);
        if (!illegal) continue;

        switch (illegal.value()) {
            case ')':
                points += 3;
                break;
            case ']':
                points += 57;
                break;
            case '}':
                points += 1197;
                break;
            case '>':
                points += 25137;     
        }
    }

    return points;
}

long part2(const vector<string>& input) {
    
    vector<long> incomplete_scores;

    optional<string> completion;
    for (const string& line : input) {
        completion = get_completion_string(line);
        if (!completion) continue;

        incomplete_scores.push_back(score(completion.value()));
    }

    sort(incomplete_scores.begin(), incomplete_scores.end());

    int mid = incomplete_scores.size() / 2; 
    return incomplete_scores.at(mid);
}

int main() {
    
    vector<string> input;
    ifstream f("day10_input.txt");

    string line;
    while (getline(f, line)) {
        input.push_back(line);
    }

    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;
}