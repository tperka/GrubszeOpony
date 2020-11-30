#ifndef POPULATION_HPP
#define POPULATION_HPP

//zalecane parametry ze skryptu, str. 71 Tablica 9.
#define M 10
#define C1  0.82
#define C2  1.2
#define ITERATIONS 500
#define MAX_GEN_VALUE 3.5
#define MIN_GEN_VALUE -3.5
#define INITIAL_SIGMA 1

#include "Individual.hpp"
#include <vector>

class Population1plus1{
    Individual individuals;
    int betterChildCounter;
    int generationsLeft;
    double sigma;
public:
    Population1plus1();
    void newGeneration();
    Individual simulate();
};

#endif // POPULATION_HPP


