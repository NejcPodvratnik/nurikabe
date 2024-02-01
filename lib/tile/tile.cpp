#include "tile.h"

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
}

Region* Tile::getRegion() const
{
    return region;
}

Type Tile::getType() const
{
    return type;
}

void Tile::setCoord(int _x, int _y)
{
    x = _x;
    y = _y;
}

void Tile::setType(Type _type)
{
    type = _type;
}

void Tile::setRegion(Region* _region)
{
    region = _region;
}

bool Tile::isDuplicate(std::vector<Tile *> seaTiles, int _y, int _x)
{
    for (auto seaTile : seaTiles)
        if (seaTile->getX() == _x && seaTile->getY() == _y)
            return true;
    return false;
}

std::vector<Tile*> Tile::getSeaNeighbours(std::vector<std::vector<Tile *>> grid)
{
    std::vector<Tile*> seaTiles;
    
    if (grid[y - 1][x] -> getType() == Type::SEA && !isDuplicate(seaTiles, y - 1, x))
        seaTiles.push_back(grid[y - 1][x]);
    if (grid[y + 1][x] -> getType() == Type::SEA && !isDuplicate(seaTiles, y + 1, x))
        seaTiles.push_back(grid[y + 1][x]);
    if (grid[y][x - 1] -> getType() == Type::SEA && !isDuplicate(seaTiles, y, x - 1))
        seaTiles.push_back(grid[y][x - 1]);
    if (grid[y][x + 1] -> getType() == Type::SEA && !isDuplicate(seaTiles, y, x + 1))
        seaTiles.push_back(grid[y][x + 1]);
    return seaTiles;
}
