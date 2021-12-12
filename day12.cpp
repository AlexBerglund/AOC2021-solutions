#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <ctype.h>
#include <vector>

using namespace std;

int number_of_paths(const map<string, set<string>>& graph, set<string>* visited, const string& from, bool allow_twice) {

    if (from == "end") {
        delete visited;
        return 1;
    }

    if (islower(from[0])) visited->insert(from);

    auto adjacent = graph.find(from)->second;
    int path_count = 0;

    for (auto& node : adjacent) {
        if (visited->find(node) == visited->end()) {
            path_count += number_of_paths(graph, new set<string>(*visited), node, allow_twice);
        } else if (allow_twice && node != "start") {
            path_count += number_of_paths(graph, new set<string>(*visited), node, false);
        }
    }

    delete visited;
    return path_count;
} 

int part1(const map<string, set<string>>& graph) {
    return number_of_paths(graph, new set<string>, "start", false);
}

int part2(const map<string, set<string>>& graph) {
    return number_of_paths(graph, new set<string>, "start", true);
}

int main() {

    ifstream f("input/day12_input.txt");

    map<string, set<string>> graph;

    string str;
    string node1;
    string node2;

    while (getline(f, node1, '-') && getline(f, node2)) {

        if (graph.find(node1) == graph.end()) {
            // if not in graph
            set<string> adjacent;
            adjacent.insert(node2);
            graph.emplace(node1, adjacent);
        } else {
            // if already in graph
            graph.find(node1)->second.insert(node2);
        }

        if (graph.find(node2) == graph.end()) {
            // if not in graph
            set<string> adjacent;
            adjacent.insert(node1);
            graph.emplace(node2, adjacent);
        } else {
            // if already in graph
            graph.find(node2)->second.insert(node1);
        }
    } 

    cout << "Part 1: " << part1(graph) << endl;
    cout << "Part 2: " << part2(graph) << endl;

}