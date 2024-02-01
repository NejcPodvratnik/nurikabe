#include "region.h"

int Region::getID() const
{
    return id;
}

int Region::getCurrentSize() const
{
    return currentSize;
}

int Region::getMaxSize() const
{
    return maxSize;
}

Type Region::getType() const
{
    return type;
}

std::vector<Tile*> Region::getTiles() const
{
    return tiles;
}

void Region::addTileToRegion(Tile *tile)
{
    tiles.push_back(tile);
    currentSize++;
}

bool Region::isDuplicate(std::vector<Tile*> adjacentTiles, int _y, int _x)
{
    for (auto adjacentTile : adjacentTiles)
        if (adjacentTile->getX() == _x && adjacentTile->getY() == _y)
            return true;
    return false;
}

std::vector<Tile*> Region::getAdjacentTiles(std::vector<std::vector<Tile*>> grid)
{
    std::vector<Tile*> adjacentTiles;

    for (auto tile : tiles)
    {
        int _y = tile->getY();
        int _x = tile->getX();

        if (grid[_y - 1][_x] -> getType() == Type::UNKNOWN && !isDuplicate(adjacentTiles, _y - 1, _x))
            adjacentTiles.push_back(grid[_y - 1][_x]);
        if (grid[_y + 1][_x] -> getType() == Type::UNKNOWN && !isDuplicate(adjacentTiles, _y + 1, _x))
            adjacentTiles.push_back(grid[_y + 1][_x]);
        if (grid[_y][_x - 1] -> getType() == Type::UNKNOWN && !isDuplicate(adjacentTiles, _y, _x - 1))
            adjacentTiles.push_back(grid[_y][_x - 1]);
        if (grid[_y][_x + 1] -> getType() == Type::UNKNOWN && !isDuplicate(adjacentTiles, _y, _x + 1))
            adjacentTiles.push_back(grid[_y][_x + 1]);

    }
    return adjacentTiles;
}

void Region::print(std::vector<std::vector<Tile*>> grid)
{
    std::string typeS = type == Type::SEA ? "Sea" : "Island";
    std::cout << typeS << " " << id << " Size: " << currentSize << "/" << maxSize;
    std::cout << " Tiles: ";
    for (auto tile : tiles)
    std::cout << "(" << tile -> getY() << "," << tile -> getX() << ") ";
    std::cout << std::endl;
    std::cout << "Adjacent Tiles: ";
    for (auto tile : getAdjacentTiles(grid))
    std::cout << "(" << tile -> getY() << "," << tile -> getX() << ") ";
    std::cout << std::endl;
    std::cout << std::endl;
}
