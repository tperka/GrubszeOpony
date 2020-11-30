#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include "Chromosome.hpp"

#define N_OF_CHROMOSOMES 2


class Individual {
    double fitness;
    Chromosome chromosome[N_OF_CHROMOSOMES];

public:
    Individual();
    Individual(Chromosome chromosome[N_OF_CHROMOSOMES]);
    Individual mate(Individual parent2);
    Individual mutate(double sigma);
    double calculateFitness();
    double getFitness();
    Chromosome* getChromosome();
};

bool operator<(Individual& a, Individual& b);


#endif