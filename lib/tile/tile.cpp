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

// OPOZORILO: Ta funkcija deluje narobe ker nena pravilno odstrani duplikate
std::vector<Tile*> Tile::getSeaNeighbour(std::vector<std::vector<Tile *>> grid)
{
    std::vector<Tile*> seaTiles;
    if (grid[y - 1][x] -> getType() == Type::SEA)
    {
        for (auto seaTile : seaTiles)
            if (seaTile->getX() == x && seaTile->getY() == y - 1)
                continue;
        seaTiles.push_back(grid[y - 1][x]);
    }
    if (grid[y + 1][x] -> getType() == Type::SEA)
    {
        for (auto seaTile : seaTiles)
            if (seaTile->getX() == x && seaTile->getY() == y + 1)
                continue;
        seaTiles.push_back(grid[y + 1][x]);
    }
    if (grid[y][x - 1] -> getType() == Type::SEA)
    {
        for (auto seaTile : seaTiles)
            if (seaTile->getX() == x - 1 && seaTile->getY() == y)
                continue;
        seaTiles.push_back(grid[y][x - 1]);
    }
    if (grid[y][x + 1] -> getType() == Type::SEA)
    {
        for (auto seaTile : seaTiles)
            if (seaTile->getX() == x + 1 && seaTile->getY() == y)
                continue;
        seaTiles.push_back(grid[y][x + 1]);
    }
    return seaTiles;
}

