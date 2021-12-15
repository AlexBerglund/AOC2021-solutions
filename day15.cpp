#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <set>

using namespace std;

class Node {
public:
    int risk;
    int cost_to_here;
    int index;
    Node(int risk, int cost, int index)
        : risk(risk), cost_to_here(cost), index(index) {}
};

class Edge {
public:
    Node from, to;
    Edge(Node from, Node to)
        : from(from), to(to) {}
    
    bool operator<(const Edge& e) const {
        return from.index + to.index + (from.index * to.index) < e.from.index + e.to.index + (e.from.index * e.to.index);
    }
};

class Compare {
public:
    bool operator() (const Node& n1, const Node& n2) const {
        return n1.cost_to_here > n2.cost_to_here;
    }
};

template<size_t N>
bool valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

template<size_t N>
vector<Edge> outgoing_edges(const array<array<int, N>, N>& grid, const Node& from) {
    int x = from.index % N;
    int y = from.index / N;
    
    vector<Edge> outgoing;
    
    if (valid<N>(x+1, y)) outgoing.push_back(Edge(from, Node(grid[y][x+1], from.cost_to_here + grid[y][x+1], y*N + x+1)));
    if (valid<N>(x-1, y)) outgoing.push_back(Edge(from, Node(grid[y][x-1], from.cost_to_here + grid[y][x-1], y*N + x-1)));
    if (valid<N>(x, y+1)) outgoing.push_back(Edge(from, Node(grid[y+1][x], from.cost_to_here + grid[y+1][x], (y+1)*N + x)));
    if (valid<N>(x, y-1)) outgoing.push_back(Edge(from, Node(grid[y-1][x], from.cost_to_here + grid[y-1][x], (y-1)*N + x)));

    return outgoing;
}

template<size_t N>
int pathfind(const array<array<int, N>, N>& grid) {
    
    auto queue = new priority_queue<Node, vector<Node>, Compare>();
    auto visited = new set<Edge>();

    Node current(grid[0][0], 0, 0);
    queue->push(current);

    while (!queue->empty()) {

        current = queue->top();
        queue->pop();

        if (current.index == N*N - 1) {
            return current.cost_to_here;
        }

        for (auto& edge : outgoing_edges<N>(grid, current)) {
            if (visited->find(edge) != visited->end()) continue;

            queue->push(edge.to);
            visited->insert(edge);
        }
    }

    return -1;
}

int main() {

    ifstream f("input/day15_input.txt");

    auto small_grid = *(new array<array<int, 100>, 100>());

    char num;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            f >> num;
            small_grid[i][j] = num - '0';
        }
    }

    auto large_grid = *(new array<array<int, 500>, 500>());
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            int x_dist = j / 100;
            int y_dist = i / 100;
            int reference_risk = small_grid[i % 100][j % 100];
            int new_risk = reference_risk + x_dist + y_dist;
            if (new_risk > 9) new_risk = new_risk % 10 + 1;
            large_grid[i][j] = new_risk;
        }
    }


    cout << "Part 1: " << pathfind<100>(small_grid) << endl;
    cout << "Part 2: " << pathfind<500>(large_grid) << endl;
}