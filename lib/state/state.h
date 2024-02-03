#ifndef STATE_H
#define STATE_H

#include <vector>
#include <queue>


//Classes
#include"../region/region.h"
#include"../tile/tile.h"
#include"../potential_pool/potential_pool.h"

class State {
private:
    std::vector<std::vector<Tile*>> grid;
    std::vector<Region*> regions;
    std::vector<PotentialPool> potentialPools;

    bool setTileAsIsland(Region* region, Tile* tile);
    bool checkIfNeighboursIslands(Tile* tile);
    bool checkIfUnreachable(Tile* tile, int blockY = -1, int blockX = -1);
    int getMinDistance(Tile* startTile, Tile* endTile, int blockY = -1, int blockX = -1);

    bool fullIslandsExist();
    bool canExpandOnlyOneWay();
    bool islandsThatAreMissingOnlyOneCell();
    bool unreachableNodesExist();
    bool poolDangerExist();
    bool checkifCorrectlySolved();
    bool checkifErrors();

public:
    State(std::vector<std::vector<Tile*>> _grid, std::vector<Region*> _regions, std::vector<PotentialPool> _potentialPools) : grid(_grid), regions(_regions), potentialPools(_potentialPools) {};

    //Getters
    std::vector<std::vector<Tile*>> getGrid();
    std::vector<Region*> getRegions();
    std::vector<PotentialPool> getPotentialPools();

    // Methods
    void print();
    void solve();
    bool setTileAsSea(Tile* tile);
    bool setTileAsUnconnectedIsland(Tile* tile);
};

#endif