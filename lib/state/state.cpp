#include "state.h"
#include <iostream>

std::vector<std::vector<Tile *>> State::getGrid()
{
    return grid;
}

std::vector<Region *> State::getRegions()
{
    return regions;
}

std::vector<PotentialPool> State::getPotentialPools()
{
    return potentialPools;
}

void State::print()
{
    for (auto row : grid)
    {
        for (auto tile : row)
        {
            if (tile -> getType() == Type::UNKNOWN)
                std::cout << "U ";
            else if (tile -> getType() == Type::SEA)
                std::cout << "0 ";
            else if (tile -> getType() == Type::UNCONNECTED_ISLAND)
                std::cout << "I ";
            else if (tile -> getType() == Type::BORDER)
                std::cout << "B ";
            else
                std::cout << tile -> getRegion()->getMaxSize() << " ";
        }
        std::cout << std::endl;
    }


    for (auto region : regions)
        region->print(grid);

    std::cout << "Stevilo vseh moznih bazenov je: " << potentialPools.size() << std::endl;
    for (int i = 0; i < potentialPools.size(); i++)
    {
        std::cout << "(" << potentialPools[i].getTopLeft() -> getY() << "," << potentialPools[i].getTopLeft() -> getX() << ") ";
        if ((i + 1) % 10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void State::solve()
{
    bool change;
    do 
    {
        if (checkifCorrectlySolved())
            std::cout << "Pravilno reseno." << std::endl;
        else if (checkifErrors())
            std::cout << "Napake najdene." << std::endl;
        change = false;
        change |= fullIslandsExist();
        change |= canExpandOnlyOneWay();
        change |= islandsThatAreMissingOnlyOneCell();
        change |= unreachableNodesExist();
        change |= poolDangerExist();
    } while(change);
}

bool State::setTileAsSea(Tile * tile)
{
    tile -> setType(Type::SEA);
    
    std::vector<Tile*> tiles = tile->getNeighboursWithType(grid, Type::SEA);
    if (tiles.size() == 0)
    {
        tile -> setRegion(new Region(0, Type::SEA, tile));
        regions.push_back(tile -> getRegion());
    }
    else if (tiles.size() == 1) // Ima enega soseda
    {
        tile -> setRegion(tiles[0] -> getRegion());
        tile -> getRegion() -> addTileToRegion(tile);
    }
    else // Ima več sosedov
    {
        tile -> setRegion(tiles[0] -> getRegion());
        tile -> getRegion() -> addTileToRegion(tile);
        for (int i = 1; i < tiles.size(); i++)
        {
            Region* reg =  tiles[i] -> getRegion();
            for (auto regionTile : reg -> getTiles())
            {
                tiles[0] -> getRegion() -> addTileToRegion(regionTile);
                regionTile->setRegion(tiles[0] -> getRegion());
            }
            int deleteID = reg -> getID();
            regions.erase(std::remove_if(regions.begin(), regions.end(), [deleteID](Region* pReg) {
                bool isDeleted = pReg->getID() == deleteID;
                if (isDeleted)
                    delete pReg;
                return isDeleted;
            }), regions.end());
        }
    }
    return true;
}

bool State::setTileAsIsland(Region* region, Tile* tile)
{
    tile -> setType(Type::ISLAND);
    tile -> setRegion(region);
    region -> addTileToRegion(tile);
    return true;

}

bool State::setTileAsUnconnectedIsland(Tile *tile)
{
    tile -> setType(Type::UNCONNECTED_ISLAND);
    
    std::vector<Tile*> tiles = tile->getNeighboursWithType(grid, Type::UNCONNECTED_ISLAND);
    std::vector<Tile*> island = tile->getNeighboursWithType(grid, Type::ISLAND);

    if (tiles.size() == 0 && island.size() >= 1)
        setTileAsIsland(island[0]->getRegion(), tile);
    else if (tiles.size() > 0 && island.size() >= 1)
    {
        setTileAsIsland(island[0]->getRegion(), tile);
        for (int i = 0; i < tiles.size(); i++)
        {
            Region* reg =  tiles[i] -> getRegion();
            for (auto regionTile : reg -> getTiles())
            {
                island[0] -> getRegion() -> addTileToRegion(regionTile);
                regionTile -> setType(Type::ISLAND);
                regionTile -> setRegion(island[0] -> getRegion());
            }
            int deleteID = reg -> getID();
            regions.erase(std::remove_if(regions.begin(), regions.end(), [deleteID](Region* pReg) {
                bool isDeleted = pReg->getID() == deleteID;
                if (isDeleted)
                    delete pReg;
                return isDeleted;
            }), regions.end());
        }
    }
    else if (tiles.size() == 0 && island.size() == 0)
    {
        tile -> setRegion(new Region(0, Type::UNCONNECTED_ISLAND, tile));
        regions.push_back(tile -> getRegion());
    }
    else if (tiles.size() == 1 && island.size() == 0)
    {
        tile -> setRegion(tiles[0] -> getRegion());
        tile -> getRegion() -> addTileToRegion(tile);
    }
    else if (tiles.size() > 1 && island.size() == 0)
    {
        tile -> setRegion(tiles[0] -> getRegion());
        tile -> getRegion() -> addTileToRegion(tile);
        for (int i = 1; i < tiles.size(); i++)
        {
            Region* reg =  tiles[i] -> getRegion();
            for (auto regionTile : reg -> getTiles())
            {
                tiles[0] -> getRegion() -> addTileToRegion(regionTile);
                regionTile->setRegion(tiles[0] -> getRegion());
            }
            int deleteID = reg -> getID();
            regions.erase(std::remove_if(regions.begin(), regions.end(), [deleteID](Region* pReg) {
                bool isDeleted = pReg->getID() == deleteID;
                if (isDeleted)
                    delete pReg;
                return isDeleted;
            }), regions.end());
        }
    }
    return true;
}

bool State::checkIfNeighboursIslands(Tile* tile)
{
    int y = tile->getY();
    int x = tile->getX();
    int id = -1;

    if (grid[y - 1][x]->getType() == Type::ISLAND)
        id = grid[y - 1][x] -> getRegion() -> getID();
    if (grid[y + 1][x]->getType() == Type::ISLAND)
    {
        if (id != -1 && id != grid[y + 1][x] -> getRegion() -> getID())
            return true;
        id = grid[y + 1][x] -> getRegion() -> getID();;
    }
    if (grid[y][x - 1]->getType() == Type::ISLAND)
    {
        if (id != -1 && id != grid[y][x - 1] -> getRegion() -> getID())
            return true;
        id = grid[y][x - 1] -> getRegion() -> getID();;
    }  
    if (grid[y][x + 1]->getType() == Type::ISLAND)
    {
        if (id != -1 && id != grid[y][x + 1] -> getRegion() -> getID())
            return true;
        id = grid[y][x + 1] -> getRegion() -> getID();;
    }     
    return false;
}

bool State::checkIfUnreachable(Tile *tile, int blockY, int blockX)
{
    for (int i = 0; i < regions.size(); i++)
    {
        if (regions[i]->getType() == Type::ISLAND)
        {
            int tilesLeft = regions[i] -> getMaxSize() - regions[i] -> getCurrentSize();
            for (auto startTile : regions[i] -> getAdjacentTiles(grid))
            {
                int L1 = abs(startTile -> getX() - tile -> getX()) + abs(startTile -> getY() - tile -> getY());
                if (L1 <= tilesLeft - 1 && getMinDistance(startTile, tile, blockY, blockX) <= tilesLeft - 1)
                    return false;
            }
        }
    }
    return true;
}

struct Point {
    int y, x, dist;
};

//POMEMBNO DOPOLNI: OMOGOČI DA JE DISTANCE OMEJEN NA MAXSIZE - CURRENZSIZE - 1
int State::getMinDistance(Tile *startTile, Tile *endTile, int blockY, int blockX)
{
    int y1 = startTile -> getY();
    int x1 = startTile -> getX();

    int y2 = endTile -> getY();
    int x2 = endTile -> getX();

    if (blockY == y1 && blockX == x1)
        return INT32_MAX;

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    std::vector<std::vector<int>> directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    std::queue<Point> q;
    q.push({y1, x1, 0}); // MOGOČE 1
    visited[y1][x1] = true;

    if (blockY != -1 && blockX != -1)
        visited[blockY][blockX] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.y == y2 && current.x == x2) {
            return current.dist; // Reached the destination
        }

        for (const auto& dir : directions) {
            int x3 = current.x + dir[0];
            int y3 = current.y + dir[1];

            if (visited[y3][x3] == false && (grid[y3][x3] -> getType() == Type::UNKNOWN || grid[y3][x3] -> getType() == Type::UNCONNECTED_ISLAND) && 
                grid[y3 - 1][x3]->getType() != Type::ISLAND && grid[y3 + 1][x3]->getType() != Type::ISLAND &&
                grid[y3][x3 - 1]->getType() != Type::ISLAND && grid[y3][x3 - 1]->getType() != Type::ISLAND) 
            {
                visited[y3][x3] = true;
                q.push({y3, x3, current.dist + 1});
            }
        }
    }

    return INT32_MAX; // No valid path found
}

bool State::fullIslandsExist()
{
    bool change = false;
    int size = regions.size();
    for (int i = 0; i  < size; i++)
        if (regions[i] -> getType() == Type::ISLAND && regions[i] -> getCurrentSize() == regions[i] -> getMaxSize())
            for (auto tile : regions[i] -> getAdjacentTiles(grid))
                change = setTileAsSea(tile);
    return change;
}

bool State::canExpandOnlyOneWay()
{
    bool change = false;
    for (auto region : regions)
    {
        std::vector<Tile*> adjacentTiles = region -> getAdjacentTiles(grid);
        if (adjacentTiles.size() == 1 && (region->getType() == Type::ISLAND || region->getType() == Type::UNCONNECTED_ISLAND))
            change = setTileAsUnconnectedIsland(adjacentTiles[0]);
        if (adjacentTiles.size() == 1 && region->getType() == Type::SEA)
            change = setTileAsSea(adjacentTiles[0]);

    }
    return change;
}

bool State::islandsThatAreMissingOnlyOneCell()
{
    bool change = false;
    for (auto region : regions)
    {
        if (region -> getType() == Type::ISLAND && region -> getCurrentSize() + 1 == region -> getMaxSize())
        {
            std::vector<Tile*> adjacentTiles = region -> getAdjacentTiles(grid);
            if (adjacentTiles.size() == 2)
            {
                Tile* tile1 = adjacentTiles[0];
                Tile* tile2 = adjacentTiles[1];
                if ((tile1 -> getX() + 1 == tile2 -> getX() && tile1 -> getY() + 1 == tile2 -> getY()) ||
                    (tile1 -> getX() - 1 == tile2 -> getX() && tile1 -> getY() - 1 == tile2 -> getY()) ||
                    (tile1 -> getX() - 1 == tile2 -> getX() && tile1 -> getY() + 1 == tile2 -> getY()) ||
                    (tile1 -> getX() + 1 == tile2 -> getX() && tile1 -> getY() - 1 == tile2 -> getY()))
                {
                    if (grid[tile1->getY()][tile2->getX()]->getType() == Type::UNKNOWN)
                        change = setTileAsSea(grid[tile1->getY()][tile2->getX()]);
                    else if (grid[tile2->getY()][tile1->getX()]->getType() == Type::UNKNOWN)
                        change = setTileAsSea(grid[tile2->getY()][tile1->getX()]);
                }
            }
        }
    }
    return change;
}

bool State::unreachableNodesExist()
{
    bool change = false;
    for (int y = 1; y < grid.size() - 1; y++)
    {
        for (int x = 1; x < grid[0].size() - 1; x++)
        {
            if (grid[y][x] -> getType() == Type::UNKNOWN)
            {
                //Če je obkoljeno s morjem
                if (grid[y - 1][x]->getType() == Type::SEA && grid[y + 1][x]->getType() == Type::SEA && 
                    grid[y][x - 1]->getType() == Type::SEA && grid[y][x + 1]->getType() == Type::SEA)
                    change = setTileAsSea(grid[y][x]);
                // Če je meja med dvema različnima otokoma
                else if (checkIfNeighboursIslands(grid[y][x]))
                    change = setTileAsSea(grid[y][x]);
                else if (checkIfUnreachable(grid[y][x]))
                    change = setTileAsSea(grid[y][x]);
            }
        }
    }
    return change;
}

bool State::poolDangerExist()
{
    bool change = false;
    for (auto potentialPool : potentialPools)
    {
        if (potentialPool.checkIf3SeaDanger())
        {
            Tile* unknownTile = potentialPool.getUnknowns()[0];
            change = setTileAsUnconnectedIsland(unknownTile);
        }
        else if (potentialPool.checkIf2SeaDanger())
        {
            std::vector<Tile*> tiles = potentialPool.getUnknowns();
            Tile* tile1 = tiles[0];
            Tile* tile2 = tiles[1];

            if (checkIfUnreachable(tile1, tile2 -> getY(), tile2 -> getX()))
            {
                change = setTileAsUnconnectedIsland(tile2);
                //change = setTileAsSea(tile1);
            }
            else if (checkIfUnreachable(tile2, tile1 -> getY(), tile1 -> getX()))
            {
                change = setTileAsUnconnectedIsland(tile1);
                //change = setTileAsSea(tile2);
            }
        }
    }
    return change;
}

bool State::checkifCorrectlySolved()
{
    int seaCount = 0;
    int tilesCount = 0;
    for (auto region : regions)
    {
        if (region->getType() == Type::ISLAND && region->getCurrentSize() != region->getMaxSize())
            return false;
        if (region-> getType() == Type::UNCONNECTED_ISLAND)
            return false;
        if (region-> getType() == Type::SEA)
            seaCount++;
        tilesCount += region -> getCurrentSize();
    }
    if (seaCount != 1 || tilesCount != (grid.size() - 2) * (grid[0].size() - 2))
        return false;

    for (auto potentialPool : potentialPools)
        if (potentialPool.checkIfPool())
            return false;

    return true;
}

bool State::checkifErrors()
{
    for (auto region : regions)
    {
        if (region->getType() == Type::ISLAND && region->getCurrentSize() > region->getMaxSize())
            return true;
        else if (region->getType() == Type::ISLAND && region->getCurrentSize() < region->getMaxSize() && region->getAdjacentTiles(grid).size() == 0)
            return true;
        else if (region-> getType() == Type::UNCONNECTED_ISLAND && region -> getAdjacentTiles(grid).size() == 0)
            return true;
        else if (region-> getType() == Type::SEA && region -> getAdjacentTiles(grid).size() == 0)
            return true;
    }

    for (auto potentialPool : potentialPools)
        if (potentialPool.checkIfPool())
            return true;

    return false;
}
