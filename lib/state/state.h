#ifndef STATE_H
#define STATE_H

#include <vector>

//Classes
#include"../region/region.h"
#include"../tile/tile.h"
#include"../potential_pool/potential_pool.h"

class State {
private:
    std::vector<std::vector<Tile*>> grid;
    std::vector<Region*> regions;
    std::vector<PotentialPool> potentialPools;

    void setTileAsSea(Tile* tile);
    void setTileAsIsland(Region* region, Tile* tile);

    void fullIslandsExist();
    void canExpandOnlyOneWay();
    void islandsThatAreMissingOnlyOneCell();
    void unreachableNodesExist();

public:
    State(std::vector<std::vector<Tile*>> _grid, std::vector<Region*> _regions, std::vector<PotentialPool> _potentialPools) : grid(_grid), regions(_regions), potentialPools(_potentialPools) {};

    //Getters
    std::vector<std::vector<Tile*>> getGrid();
    std::vector<Region*> getRegions();
    std::vector<PotentialPool> getPotentialPools();

    // Methods
    void print();
    void solve();
};

#endif