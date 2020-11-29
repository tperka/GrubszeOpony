#ifndef POPULATION_HPP
#define POPULATION_HPP

//zalecane parametry ze skryptu, str. 71 Tablica 9.
#define M 10
#define C1  0.82
#define C2  1.2
#define ITERATIONS 100
#define MAX_GEN_VALUE 20.5
#define MIN_GEN_VALUE -20.5
#define INITIAL_SIGMA 5

#include "Individual.hpp"
#include <vector>

class Population {
    Individual individuals;
    int betterChildCounter;
    int generationsLeft;
    double sigma;
public:
    Population();
    void newGeneration();
    Individual simulate();
};

#endif // POPULATION_HPP


