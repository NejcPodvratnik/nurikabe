#ifndef REGION_H
#define REGION_H

#include<vector>
#include<iostream>
#include<string>

//Classes
#include "../tile/tile.h"
#include "../type.h"

class Region {
private:
    int id;
    static int nextId;
    int currentSize;
    int maxSize;
    Type type;
    std::vector<Tile*> tiles;

    bool isDuplicate(std::vector<Tile*> adjacentTiles, int _y, int _x);


public:
    Region(int _maxSize, Type _type, Tile* tile) : id(nextId++), currentSize(1), maxSize(_maxSize), type(_type) {
        tiles.push_back(tile);
    }

    // Getter methods
    int getID() const;
    int getCurrentSize() const;
    int getMaxSize() const;
    Type getType() const;
    std::vector<Tile*> getTiles() const;

    // Setter methods

    // Methods
    void addTileToRegion(Tile* tile);
    std::vector<Tile*> getAdjacentTiles(std::vector<std::vector<Tile*>> grid);
    void print(std::vector<std::vector<Tile*>> grid);
};

#endif