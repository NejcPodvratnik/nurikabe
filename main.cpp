#include <iostream>
#include <string>

//Classes
#include "lib/nurikabe_solver/nurikabe_solver.h"

int Region::nextId = 1;

int main() {
    std::string filename = "./input/2.txt";

    NurikabeSolver NS = NurikabeSolver(filename);
    
    NS.init();
    NS.solve();
}
