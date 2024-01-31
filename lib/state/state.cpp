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
    //TODO: CHECK IF SOLVED AND CHECK IF BOARD IS CORRECT (NO POOLS ETC.)
    fullIslandsExist();
    canExpandOnlyOneWay();
    islandsThatAreMissingOnlyOneCell();
    //unreachableNodesExist();
}

void State::setTileAsSea(Tile * tile)
{
    tile -> setType(Type::SEA);
    
    std::vector<Tile*> tiles = tile->getSeaNeighbour(grid);
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
}

//TODO: NAREDI ŠE ZA "NEPRIPRADAJOČE" OTOKE
void State::setTileAsIsland(Region* region, Tile* tile)
{
    tile -> setType(Type::ISLAND);
    tile -> setRegion(region);
    region -> addTileToRegion(tile);

}

void State::fullIslandsExist()
{
    int size = regions.size();
    for (int i = 0; i  < size; i++)
        if (regions[i] -> getType() == Type::ISLAND && regions[i] -> getCurrentSize() == regions[i] -> getMaxSize())
            for (auto tile : regions[i] -> getAdjacentTiles(grid))
                setTileAsSea(tile);
}

void State::canExpandOnlyOneWay()
{
    for (auto region : regions)
    {
        std::vector<Tile*> adjacentTiles = region -> getAdjacentTiles(grid);
        if (adjacentTiles.size() == 1 && region->getType() == Type::ISLAND)
            setTileAsIsland(region, adjacentTiles[0]);
        if (adjacentTiles.size() == 1 && region->getType() == Type::SEA)
            setTileAsSea(adjacentTiles[0]);

    }
}

void State::islandsThatAreMissingOnlyOneCell()
{
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
                        setTileAsSea(grid[tile1->getY()][tile2->getX()]);
                    else if (grid[tile2->getY()][tile1->getX()]->getType() == Type::UNKNOWN)
                        setTileAsSea(grid[tile2->getY()][tile1->getX()]);
                }
            }
        }
    }
}

void State::unreachableNodesExist()
{
    for (int y = 1; y < grid.size() - 1; y++)
    {
        for (int x = 1; x < grid[0].size() - 1; x++)
        {
            true;
        }
    }
}
