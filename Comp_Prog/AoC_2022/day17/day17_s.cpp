#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Coordinate
{
public:
    int x;
    int y;
    Coordinate(int, int);
    Coordinate();
};
class Shape
{
protected:
    Coordinate core;
    vector<Coordinate> coordinates;

public:
    Shape(Coordinate);
    virtual void generate_coordinates();
    int fall(vector<vector<char>>);
    void push(vector<vector<char>>, char);
};

Shape::Shape(Coordinate core)
{
    this->core = core;
    this->generate_coordinates();
};

void Shape::push(vector<vector<char>> grid, char direction)
{
    if (direction == '<')
    {
        for (int i = 0; i < coordinates.size(); i++)
        {
            if (grid[coordinates[i].y][coordinates[i].x - 1] == '#' || (coordinates[i].x - 1) < 0)
            {
                return;
            }
        }
        for (int i = 0; i < coordinates.size(); i++)
        {
            coordinates[i].x--;
        }
    }
    else
    {
        for (int i = 0; i < coordinates.size(); i++)
        {
            if (grid[coordinates[i].y][coordinates[i].x + 1] == '#' || (coordinates[i].x + 1) > 6)
            {
                return;
            }
        }
        for (int i = 0; i < coordinates.size(); i++)
        {
            coordinates[i].x++;
        }
    }
}

int Shape::fall(vector<vector<char>> grid)
{
    while (true)
    {
        for (int i = 0; i < coordinates.size(); i++)
        {
            if (grid[coordinates[i].y + 1][coordinates[i].x] == '#')
            {

                for (int i = 0; i < coordinates.size(); i++)
                {
                    grid[coordinates[i].y][coordinates[i].x] = '#';
                }
                // return co od with min y value
                int min_y = 100;
            
                for (int i = 0; i < coordinates.size(); i++)
                {
                    if (coordinates[i].y < min_y)
                    {
                        min_y = coordinates[i].y;
                    }
                }
                return min_y;
                
            }
        }
        for (int i = 0; i < coordinates.size(); i++)
        {
            coordinates[i].y++;
        }
    }
}

Coordinate::Coordinate()
{
    this->x = 0;
    this->y = 0;
}

Coordinate ::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

class HorizLine : public Shape
{
public:
    HorizLine(Coordinate core) : Shape(core){};
    void generate_coordinates()
    {
        //*#* ###
        coordinates.push_back(core);
        coordinates.push_back(Coordinate(core.x + 1, core.y));
        coordinates.push_back(Coordinate(core.x + 2, core.y));
        coordinates.push_back(Coordinate(core.x + 3, core.y));
    };
};

class VertLine : public Shape
{
public:
    VertLine(Coordinate core) : Shape(core){};
    void generate_coordinates()
    {
        // *#*
        // #
        // #
        // #
        coordinates.push_back(core);
        coordinates.push_back(Coordinate(core.x, core.y + 1));
        coordinates.push_back(Coordinate(core.x, core.y + 2));
        coordinates.push_back(Coordinate(core.x, core.y + 3));
    };
};

class Plus : public Shape
{
public:
    Plus(Coordinate core) : Shape(core){};
    void generate_coordinates()
    {
        //   #
        // #*#*#
        //   #
        coordinates.push_back(core);
        coordinates.push_back(Coordinate(core.x, core.y - 1));
        coordinates.push_back(Coordinate(core.x, core.y + 1));
        coordinates.push_back(Coordinate(core.x - 1, core.y));
        coordinates.push_back(Coordinate(core.x + 1, core.y));
    };
};

class Box : public Shape
{
public:
    Box(Coordinate core) : Shape(core){};
    void generate_coordinates()
    {
        // *#*#
        // ##
        coordinates.push_back(core);
        coordinates.push_back(Coordinate(core.x + 1, core.y));
        coordinates.push_back(Coordinate(core.x, core.y + 1));
        coordinates.push_back(Coordinate(core.x + 1, core.y + 1));
    };
};

class L : public Shape
{
public:
    L(Coordinate core) : Shape(core){};
    void generate_coordinates()
    {
        //    #
        //    #
        // #*#*#
        coordinates.push_back(core);
        coordinates.push_back(Coordinate(core.x + 1, core.y));
        coordinates.push_back(Coordinate(core.x - 1, core.y));
        coordinates.push_back(Coordinate(core.x + 1, core.y - 1));
        coordinates.push_back(Coordinate(core.x + 1, core.y - 2));
    };
};

int main()
{

    ifstream file("input.txt");
    string jet_pushes;
    string line;
    int rocks_done = 0;
    int drop_size = 60;
    int y_max = drop_size - 1;
    int jet_pointer = 0;
    int rock_selector = 0;
    vector<vector<char>> grid(drop_size, vector<char>(7, '.'));
    while (getline(file, line))
    {
        jet_pushes += line;
    }
    for (int i = 0; i < 7; i++)
    {
        grid[y_max][i] = '-';
    }
    // todo change core point to actual spawn point later
    while (rocks_done < 50)
    {
        if (jet_pointer == jet_pushes.size())
        {
            jet_pointer = 0;
        }
        if (rock_selector == 0)
        {
            HorizLine rock(Coordinate(2, y_max - 3));
            rock.push(grid, jet_pushes[jet_pointer]);
            y_max = rock.fall(grid);
            rock_selector++;
        }
        else if (rock_selector == 1)
        {
            Plus rock(Coordinate(3, y_max - 4));
            rock.push(grid, jet_pushes[jet_pointer]);
            y_max = rock.fall(grid);
            rock_selector++;
        }
        else if (rock_selector == 2)
        {
            L rock(Coordinate(3, y_max - 3));
            rock.push(grid, jet_pushes[jet_pointer]);
            y_max = rock.fall(grid);
            rock_selector++;
        }
        else if (rock_selector == 3)
        {
            VertLine rock(Coordinate(2, y_max - 6));
            rock.push(grid, jet_pushes[jet_pointer]);
            y_max = rock.fall(grid);
            rock_selector++;
        }
        else if (rock_selector == 4)
        {
            Box rock(Coordinate(2, y_max - 4));
            rock.push(grid, jet_pushes[jet_pointer]);
            y_max = rock.fall(grid);
            rock_selector = 0;
            rocks_done++;
        }
        jet_pointer++;
    }
    return 0;
}