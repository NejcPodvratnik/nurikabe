#include "nurikabe_solver.h"


void NurikabeSolver::getDataFromFile(std::vector<std::vector<int>> &data)
{
    std::ifstream myfile(filename);

    if (!myfile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        exit(-1);
    }

    std::string line;
    while (std::getline(myfile, line)) {
        std::vector<int> row;

        std::istringstream iss(line);
        int value;

        while (iss >> value)
            row.push_back(value);
        data.push_back(row);
    }

    myfile.close();
}

void NurikabeSolver::init()
{
    std::vector<std::vector<int>> data; 
    getDataFromFile(data);

    int h = data.size();
    int w = data[0].size();

    std::vector<std::vector<Tile*>> grid(h + 2, std::vector<Tile*>(w + 2));
    std::vector<Region*> regions;
    std::vector<PotentialPool> potentialPools;

    for (int y = 0; y < h + 2; y++)
    {
        for (int x = 0; x < w + 2; x++)
        {
            if (x == 0 || x == grid[0].size() - 1 || y == 0 || y == grid.size() - 1)
                grid[y][x] = new Tile(x, y, Type::BORDER);
            else
            {
                if (data[y - 1][x - 1] == 0)
                    grid[y][x] = new Tile(x, y, Type::UNKNOWN);
                else 
                {
                    grid[y][x] = new Tile(x, y, Type::ISLAND);
                    grid[y][x] -> setRegion(new Region(data[y - 1][x - 1], Type::ISLAND, grid[y][x]));
                    regions.push_back(grid[y][x] -> getRegion());
                }
            }
        }
    }

    for (int y = 0; y < h - 1; y++)
        for (int x = 0; x < w - 1; x++)
                if (data[y][x] == 0 && data[y][x + 1] == 0 && data[y + 1][x] == 0 && data[y + 1][x + 1] == 0)
                    potentialPools.push_back(PotentialPool(grid[y + 1][x + 1], grid[y + 1][x + 2], grid[y + 2][x + 1], grid[y + 2][x + 2]));

    states.push(State(grid, regions, potentialPools));
}


State NurikabeSolver::getState()
{
    return states.front();
}