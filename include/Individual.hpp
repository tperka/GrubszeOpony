#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include "Chromosome.hpp"



class Individual {
    double fitness;
    Chromosome chromosome;

public:
    Individual();
    Individual(Chromosome chromosome);
    //Individual mate(Individual parent2);
    Individual mutate(double sigma);
    double calculateFitness();
    double getFitness();
    Chromosome getChromosome();
};

bool operator<(Individual& a, Individual& b);


#endif