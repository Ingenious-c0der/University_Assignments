#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Co_od {
    int x;
    int y;
    Co_od(int x_, int y_) : x(x_), y(y_) {}
};

struct Node {
    Node* parent;
    Co_od position;
    int g;
    int h;
    int f;
    Node(Node* parent_, Co_od pos, int g_, int h_) : parent(parent_), position(pos), g(g_), h(h_), f(g_ + h_) {}
};

std::vector<Co_od> a_star(std::vector<std::vector<int>> matrix, Co_od start_loc, Co_od end_loc) {
    std::vector<Node*> open_list;
    std::vector<Node*> closed_list;
    Node* start_node = new Node(nullptr, start_loc, 0, 0);
    Node* end_node = new Node(nullptr, end_loc, 0, 0);
    open_list.push_back(start_node);

    while (!open_list.empty()) {
        Node* current_node = open_list[0];
        int current_index = 0;

        for (int i = 0; i < open_list.size(); i++) {
            if (open_list[i]->f < current_node->f) {
                current_node = open_list[i];
                current_index = i;
            }
        }

        open_list.erase(open_list.begin() + current_index);
        closed_list.push_back(current_node);

        if (current_node->position.x == end_node->position.x && current_node->position.y == end_node->position.y) {
            std::vector<Co_od> path;
            Node* current = current_node;
            while (current != nullptr) {
                path.push_back(current->position);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        std::vector<Co_od> explore_delta_directions = {Co_od(0, -1), Co_od(0, 1), Co_od(-1, 0), Co_od(1, 0)};
        for (auto delta : explore_delta_directions) {
            Co_od node_position(current_node->position.x + delta.x, current_node->position.y + delta.y);
            if (node_position.x < 0 || node_position.x >= matrix.size() || node_position.y < 0 || node_position.y >= matrix[0].size() || matrix[node_position.x][node_position.y] != 0) {
                continue;
            }
            Node* new_node = new Node(current_node, node_position, current_node->g + 1, abs(node_position.x - end_loc.x) + abs(node_position.y - end_loc.y));
            open_list.push_back(new_node);
        }
    }

    return {}; // Return an empty vector if no path is found
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };

    Co_od start_loc(0, 0);
    Co_od end_loc(5, 5);
  std::vector<Co_od> path = a_star(matrix, start_loc, end_loc);

    if (!path.empty()) {
        std::cout << "Path found: ";
        for (const auto& co_od : path) {
            std::cout << "(" << co_od.x << " " << co_od.y << "), ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}