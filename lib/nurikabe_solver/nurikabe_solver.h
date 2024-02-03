#ifndef NURIKABE_SOLVER_H
#define NURIKABE_SOLVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>

//Classes
#include "../state/state.h"

class NurikabeSolver {
private:
    std::string filename;
    std::queue<State> states;

    void getDataFromFile(std::vector<std::vector<int>> &data);
    bool isDuplicate(std::vector<Tile*> guessTiles, int _y, int _x);

public:
    NurikabeSolver(std::string _filename) : filename(_filename) {}

    State getState();

    // Methods
    void init();
    
    void solve();
    //void printSolution();
};

#endif