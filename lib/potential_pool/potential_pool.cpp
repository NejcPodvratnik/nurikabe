#include "potential_pool.h"

Tile *PotentialPool::getTopLeft()
{
    return topLeft;
}

Tile *PotentialPool::getTopRight()
{
    return topRight;
}

Tile *PotentialPool::getBottomLeft()
{
    return bottomLeft;
}

Tile *PotentialPool::getBottomRight()
{
    return bottomRight;
}

bool PotentialPool::checkIfPool()
{
    return topRight -> getType() == Type::SEA && topLeft -> getType() == Type::SEA && bottomRight -> getType() == Type::SEA && bottomLeft -> getType() == Type::SEA;
}

bool PotentialPool::checkIfNoUnknowns()
{
    return topRight -> getType() != Type::UNKNOWN && topLeft -> getType() != Type::UNKNOWN && bottomRight -> getType() != Type::UNKNOWN && bottomLeft -> getType() != Type::UNKNOWN;
}

bool PotentialPool::checkIf3SeaDanger()
{
    int seaCount = (topRight -> getType() == Type::SEA) + (topLeft -> getType() == Type::SEA) + (bottomRight -> getType() == Type::SEA) + (bottomLeft -> getType() == Type::SEA);
    int unknownCount = (topRight -> getType() == Type::UNKNOWN) + (topLeft -> getType() == Type::UNKNOWN) + (bottomRight -> getType() == Type::UNKNOWN) + (bottomLeft -> getType() == Type::UNKNOWN);
    return seaCount == 3 && unknownCount == 1;
}

bool PotentialPool::checkIf2SeaDanger()
{
    bool topSea = (topRight -> getType() == Type::SEA) && (topLeft -> getType() == Type::SEA) && (bottomRight -> getType() == Type::UNKNOWN) && (bottomLeft -> getType() == Type::UNKNOWN);
    bool bottomSea = (topRight -> getType() == Type::UNKNOWN) && (topLeft -> getType() == Type::UNKNOWN) && (bottomRight -> getType() == Type::SEA) && (bottomLeft -> getType() == Type::SEA);
    bool leftSea = (topRight -> getType() == Type::UNKNOWN) && (topLeft -> getType() == Type::SEA) && (bottomRight -> getType() == Type::UNKNOWN) && (bottomLeft -> getType() == Type::SEA);
    bool rightSea = (topRight -> getType() == Type::SEA) && (topLeft -> getType() == Type::UNKNOWN) && (bottomRight -> getType() == Type::SEA) && (bottomLeft -> getType() == Type::UNKNOWN);
    return topSea || bottomSea || leftSea || rightSea;
}

std::vector<Tile *> PotentialPool::getUnknowns()
{
    std::vector<Tile*> unknowns;

    if (topRight -> getType() == Type::UNKNOWN)
        unknowns.push_back(topRight);
    if (topLeft -> getType() == Type::UNKNOWN)
        unknowns.push_back(topLeft);
    if (bottomRight -> getType() == Type::UNKNOWN)
        unknowns.push_back(bottomRight);
    if (bottomLeft -> getType() == Type::UNKNOWN)
        unknowns.push_back(bottomLeft);
    return unknowns;
}
