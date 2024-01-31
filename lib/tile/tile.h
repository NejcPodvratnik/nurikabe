#ifndef TILE_H
#define TILE_H

#include<vector>

//Classes
#include "../type.h"

class Region;

class Tile {
private:
    int x;
    int y;
    Type type;
    Region* region;


public:
    Tile() : x(0), y(0), type(Type::UNKNOWN), region(nullptr) {}
    Tile(int _x, int _y, Type _type) : x(_x), y(_y), type(_type), region(nullptr) {}

    // Getter methods
    int getX() const;
    int getY() const;
    Region* getRegion() const;
    Type getType() const;

    // Setter methods
    void setCoord(int _x, int _y);
    void setType(Type _type);
    void setRegion(Region* _region);

    // Methods
    std::vector<Tile*> getSeaNeighbour(std::vector<std::vector<Tile*>> grid);
    
};

#endif