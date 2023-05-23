#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm> 
struct Co_od {
    int x;
    int y;
    
    Co_od(int x, int y) : x(x), y(y) {}
    
    Co_od operator+(const Co_od& other) const {
        return Co_od(x + other.x, y + other.y);
    }
};

struct Node {
    Node* parent;
    Co_od position;
    int g;
    int h;
    int f;
    
    Node(Node* parent, Co_od position, int g, int h, int f)
        : parent(parent), position(position), g(g), h(h), f(f) {}
};

struct NodeComparator {
    bool operator()(const Node* a, const Node* b) const {
        return a->f < b->f;
    }
};

void printPath(const std::vector<Co_od>& path) {
    for (const auto& co_od : path) {
        std::cout << "(" << co_od.x << " " << co_od.y << "), ";
    }
    std::cout << std::endl;
}

void a_star(std::vector<std::vector<int>>& matrix, Co_od start_loc, Co_od end_loc) {
    std::vector<Node*> open_list;
    std::vector<Node*> closed_list;
    Node* start_node = new Node(nullptr, start_loc, 0, 0, 0);
    Node* end_node = new Node(nullptr, end_loc, 0, 0, 0);
    open_list.push_back(start_node);

    while (!open_list.empty()) {
        std::sort(open_list.begin(), open_list.end(), NodeComparator());
        Node* current_node = open_list.front();
        open_list.erase(open_list.begin());
        closed_list.push_back(current_node);

        if (current_node->position.x == end_node->position.x &&
            current_node->position.y == end_node->position.y) {
            std::vector<Co_od> path;
            Node* current = current_node;
            while (current) {
                path.push_back(current->position);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            printPath(path);

            // Clean up dynamically allocated nodes
            for (Node* node : open_list) {
                delete node;
            }
            for (Node* node : closed_list) {
                delete node;
            }
            return;
        }

        std::vector<Node*> children;
        std::vector<Co_od> explore_delta_directions = {Co_od(0, -1), Co_od(0, 1), Co_od(-1, 0), Co_od(1, 0)};
        for (const auto& co_od : explore_delta_directions) {
            Co_od node_position = current_node->position + co_od;
            if (node_position.x > (matrix.size() - 1) || node_position.x < 0 ||
                node_position.y > (matrix[0].size() - 1) || node_position.y < 0) {
                continue;
            }
            if (matrix[node_position.x][node_position.y] != 0) {
                continue;
            }
            Node* new_node = new Node(current_node, node_position, 0, 0, 0);
            children.push_back(new_node);
        }

        for (Node* child : children) {
            bool skip_child = false;

            for (Node* closed_child : closed_list) {
                if (child->position.x == closed_child->position.x &&
                    child->position.y == closed_child->position.y) {
                    skip_child = true;
                    break;
                }
            }
            if (skip_child) {
                delete child;
                continue;
            }

           child->g = current_node->g + 1;
           child->h = abs(child->position.x - end_node->position.x) + abs(child->position.y - end_node->position.y);
            child->f = child->g + child->h;

            for (Node* open_node : open_list) {
                if (child->position.x == open_node->position.x &&
                    child->position.y == open_node->position.y &&
                    child->g > open_node->g) {
                    skip_child = true;
                    break;
                }
            }
            if (skip_child) {
                delete child;
                continue;
            }

            open_list.push_back(child);
        }
    }

    // Path not found
    std::cout << "Path not found." << std::endl;

    // Clean up dynamically allocated nodes
    for (Node* node : open_list) {
        delete node;
    }
    for (Node* node : closed_list) {
        delete node;
    }
}

int main() {

    std::vector<std::vector<int>> mat = {
        {0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0}};
    Co_od Start = Co_od(0, 2);
    Co_od End = Co_od(5, 5);

    a_star(mat, Start, End);
    return 0;
}