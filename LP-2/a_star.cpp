#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
class Co_od
{

public:
    int x = 0;
    int y = 0;
    Co_od(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    bool operator==(Co_od &Other)
    {
        if (this->x == Other.x && this->y == Other.y)
        {
            return true;
        }
        return false;
    }
    Co_od operator+(Co_od &Other)
    {
        return Co_od(this->x + Other.x, this->y + Other.y);
    }
    Co_od(){};
};

class Node
{
    Node *parent = nullptr;
    Co_od position = Co_od(0, 0);
    int h = 0;
    int g = 0;
    int f = 0;

public:
    Node(Node *parent, Co_od pos, int h, int g, int f)
    {
        this->parent = parent;
        this->position = pos;
        this->h = h;
        this->g = g;
        this->f = f;
    }
    Node(const Node& other)
    {
        this->parent = other.parent;
        this->position = other.position;
        this->h = other.h;
        this->g = other.g;
        this->f = other.f;
    }

    void a_star(std::vector<std::vector<int>> matrix, Co_od start_loc, Co_od end_loc)
    {
        std::vector<Node*> open_list;
        std::vector<Node*> closed_list;
        Node* start_node = new Node(nullptr, start_loc, 0, 0, 0);
        Node* end_node = new Node(nullptr, end_loc, 0, 0, 0);
        open_list.push_back(start_node);

        while (open_list.size() > 0)
        {
            Node* current_node = open_list[0];
            int current_index = 0;
           
            for (int i = 0; i < open_list.size(); i++)
            {
                
                if (open_list[i]->f < current_node->f)
                {
                    current_node = open_list[i];
                    current_index = i;
                }
            }
           
            open_list.erase(open_list.begin() + current_index);
            closed_list.push_back(current_node);
            if (current_node->position == end_node->position)
            {

                std::vector<Co_od> path;
                Node *current = current_node;
                while (current)
                {
                    path.push_back(current->position);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                // print the path here and return
                for (auto co_od : path)
                {
                    std::cout <<"("<< co_od.x << " " << co_od.y <<"),";
                }
                std::cout << std::endl;
                return;
            }
           
            std::vector<Node*> children;
            std::vector<Co_od> explore_delta_directions = {Co_od(0, -1), Co_od(0, 1), Co_od(-1, 0), Co_od(1, 0)};
            for (auto co_od : explore_delta_directions)
            {
                Co_od node_position = current_node->position + co_od;
                if (node_position.x > (matrix.size() - 1) || node_position.x < 0 || node_position.y > (matrix[0].size() - 1) || node_position.y < 0)
                {
                    continue;
                }
                if (matrix[node_position.x][node_position.y] != 0)
                {
                    continue;
                }
                Node* new_node = new Node(current_node, node_position, 0, 0, 0);
                children.push_back(new_node);
            }
           
            for (auto child : children)
            {
             
                for (auto closed_child : closed_list)
                {
                    if (child->position == closed_child->position)
                    {
                        continue;
                    }
                }
                child->g = current_node->g + 1;
                child->h = std::pow(abs(child->position.x - end_node->position.x),2) +std::pow( abs(child->position.y - end_node->position.y),2);
                child->f = child->g + child->h;
                for (auto open_node : open_list)
                {
                    if (child->position == open_node->position && child->g > open_node->g)
                    {
                        continue;
                    }
                }
                open_list.push_back(child);
              
            }
        }
    }
};

int main()
{
    std::vector<std::vector<int>> mat = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0}};
    Co_od Start = Co_od(0, 0);
    Co_od End = Co_od(5, 5);
    Node n = Node(nullptr, Start, 0, 0, 0);
    n.a_star(mat, Start, End);
    return 0;
}