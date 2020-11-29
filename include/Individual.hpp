#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP
#include <string>
#include "Chromosome.hpp"
#define DIMENSIONS 1
#define SIGMA 1.0

class Individual {
    double fitness;
    Chromosome chromosome;

public:

    Individual(Chromosome chromosome);
    //Individual mate(Individual parent2);
    Individual mutate();
    double calculateFitness();
};

#endif