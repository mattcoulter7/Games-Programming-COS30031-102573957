#include <iostream>
#include <array>
#include <vector>
#include <map>

class Map
{
public:
    Map()
    {
        // having issues initialising nicely...
        node_defs[35] = false; //#
        node_defs[45] = false; //-
        node_defs[80] = false; //P
        node_defs[83] = true;  //S
        node_defs[71] = true;  //G
        node_defs[68] = true;  //D
        node_defs[32] = true;  //::space::

        dirs[0] = std::array<int, 2>{{-1, 0}};
        dirs[1] = std::array<int, 2>{{0, 1}};
        dirs[2] = std::array<int, 2>{{1, 0}};
        dirs[3] = std::array<int, 2>{{0, -1}};

        InitGrid();
    };

    int GetWidth() { return grid.size(); };
    int GetHeight() { return grid[0].size(); };

    void Draw(std::array<int, 2> player)
    {
        for (int x = 0; x < grid.size(); x++)
        {
            for (int y = 0; y < grid[x].size(); y++)
            {
                char symbol = grid[x][y];
                // character isn't inside the grid, need to draw on top
                if (x == player[0] && y == player[1])
                    symbol = 'P';
                std::cout << symbol << ' ';
            }
            std::cout << "\n";
        }
    }
    bool LocationInMap(int x, int y)
    {
        int gridEndX = GetWidth();
        int gridStartX = 0;
        int gridEndY = GetHeight();
        int gridStartY = 0;

        // valid location?
        return !((x < gridStartX || x > gridEndX) || (y < gridStartY || y > gridEndY));
    };
    char Get(int x, int y)
    {
        if (!LocationInMap(x, y))
            return '-';
        return grid[x][y];
    };
    char Get(std::array<int, 2> pos)
    {
        if (!LocationInMap(pos[0], pos[1]))
            return '-';
        return grid[pos[0]][pos[1]];
    };
    std::array<int,2> FindStart(){
        for (int x = 0; x < GetWidth();x++){
            for (int y = 0; y < GetWidth();y++){
                if (Get(x,y) == 'S'){
                    return std::array<int,2>{x,y};
                }
            }
        }
        return std::array<int,2>{7,7}; // default  start if 'S' doesn't exist on map
    }
    std::array<int, 2> DirectionToXY(char dir)
    {
        std::array<int, 2> xy = {0, 0};
        switch (dir)
        {
        case 87: //W
            xy[1] = -1;
            break;
        case 83: //E
            xy[0] = 1;
            break;
        case 69: //S
            xy[1] = 1;
            break;
        case 78: //N
            xy[0] = -1;
            break;
        }
        return xy;
    };
    char XYToDirection(int x, int y)
    {
        if (x == 0 && y == 1)
        {
            return 'E';
        }
        else if (x == 0 && y == -1)
        {
            return 'W';
        }
        else if (x == 1 && y == 0)
        {
            return 'S';
        }
        else if (x == -1 && y == 0)
        {
            return 'N';
        }
        return ' ';
    }

    std::vector<std::array<int, 2>> GetAvailableDirections(std::array<int, 2> pos)
    {
        std::vector<std::array<int, 2>> available_dirs;

        for (std::array<int, 2> dir : dirs)
        {
            if (CanMoveDirection(pos, dir))
                available_dirs.push_back(dir);
        }

        return available_dirs;
    };
    bool CanMoveDirection(std::array<int, 2> pos, std::array<int, 2> dir)
    {
        // x and y after they have moved in particular direction
        int newPlayerPosX = pos[0] + dir[0];
        int newPlayerPosY = pos[1] + dir[1];

        char location = Get(newPlayerPosX, newPlayerPosY);
        return node_defs[location];
    }
    void PrintAvailableDirections(std::array<int, 2> pos)
    {
        std::vector<std::array<int, 2>> availableDirs = GetAvailableDirections(pos);
        std::cout << "You can move ";
        for (int i = 0; i < availableDirs.size(); i++)
        {
            std::array<int, 2> dir = availableDirs[i];
            std::cout << XYToDirection(dir[0], dir[1]);
            if (i < availableDirs.size() - 1)
                std::cout << ',';
            else
                std::cout << ":> ";
        }
    }

private:
    void InitGrid()
    {
        // create the border
        for (int x = 0; x < grid.size(); x++)
        {
            for (int y = 0; y < grid[x].size(); y++)
            {
                char symb = ' ';
                // is on the border
                if ((x == 0 || x == grid.size() - 1) || (y == 0 || y == grid[x].size() - 1))
                    symb = '#';
                grid[x][y] = symb;
            }
        }

        // hardcoded as suggested
        grid[7][2] = 'S';
        grid[1][4] = '#';
        grid[2][4] = '#';
        grid[3][4] = '#';
        grid[4][4] = '#';
        grid[5][2] = '#';
        grid[5][3] = '#';
        grid[5][4] = '#';
        grid[5][5] = '#';
        grid[3][1] = '#';
        grid[3][2] = '#';

        grid[3][6] = 'D';
        grid[1][5] = 'D';
        grid[1][3] = 'D';
        grid[1][1] = 'G';
    };

    std::array<std::array<int, 2>, 4> dirs;  // directions that can be moved in
    std::map<int, bool> node_defs;           // defines what tiles can and can't be moved onto ascii char is the key
    std::array<std::array<char, 8>, 8> grid; // 2-dimenstional array of the grid
};