#ifndef POTENTIAL_POOL_H
#define POTENTIAL_POOL_H

// Classes
#include "../tile/tile.h"

class PotentialPool {
private:
    Tile* topLeft;
    Tile* topRight;
    Tile* bottomLeft;
    Tile* bottomRight;

public:
    PotentialPool(Tile* _topLeft, Tile* _topRight, Tile* _bottomLeft, Tile* _bottomRight) {
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
        5+5;
    }

    // Getter methods
    Tile* getTopLeft();
    Tile* getTopRight();
    Tile* getBottomLeft();
    Tile* getBottomRight();

    // Methods
    bool checkIfPool();
    bool checkIfNoUnknowns();
    bool checkIf2SeaDanger();
    bool checkIf3SeaDanger();
    std::vector<Tile*> getUnknowns();
};

#endif