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

bool PotentialPool::checkIf3Sea()
{
    int i = (topRight -> getType() == Type::SEA) + (topLeft -> getType() == Type::SEA) + (bottomRight -> getType() == Type::SEA) + (bottomLeft -> getType() == Type::SEA);
    return i == 3;
}

bool PotentialPool::checkIf2Sea()
{
    int i = (topRight -> getType() == Type::SEA) + (topLeft -> getType() == Type::SEA) + (bottomRight -> getType() == Type::SEA) + (bottomLeft -> getType() == Type::SEA);
    return i == 2;
}
