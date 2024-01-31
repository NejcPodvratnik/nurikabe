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


// OPOZORILO: Ta funkcija deluje narobe ker nena pravilno odstrani duplikate
std::vector<Tile*> Region::getAdjacentTiles(std::vector<std::vector<Tile*>> grid)
{
    std::vector<Tile*> adjacentTiles;

    for (auto tile : tiles)
    {
        if (grid[tile->getY() - 1][tile->getX()] -> getType() == Type::UNKNOWN)
        {
            for (auto adjacentTile : adjacentTiles)
                if (adjacentTile->getX() == tile->getX() && adjacentTile->getY() == tile->getY() - 1)
                    continue;
            adjacentTiles.push_back(grid[tile->getY() - 1][tile->getX()]);
        }
        if (grid[tile->getY() + 1][tile->getX()] -> getType() == Type::UNKNOWN)
        {
            for (auto adjacentTile : adjacentTiles)
                if (adjacentTile->getX() == tile->getX() && adjacentTile->getY() == tile->getY() + 1)
                    continue;
            adjacentTiles.push_back(grid[tile->getY() + 1][tile->getX()]);
        }
        if (grid[tile->getY()][tile->getX() - 1] -> getType() == Type::UNKNOWN)
        {
            for (auto adjacentTile : adjacentTiles)
                if (adjacentTile->getX() == tile->getX() - 1 && adjacentTile->getY() == tile->getY())
                    continue;
            adjacentTiles.push_back(grid[tile->getY()][tile->getX() - 1]);
        }
        if (grid[tile->getY()][tile->getX() + 1] -> getType() == Type::UNKNOWN)
        {
            for (auto adjacentTile : adjacentTiles)
                if (adjacentTile->getX() == tile->getX() + 1 && adjacentTile->getY() == tile->getY())
                    continue;
            adjacentTiles.push_back(grid[tile->getY()][tile->getX() + 1]);
        }
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
