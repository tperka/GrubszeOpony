#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include "Chromosome.hpp"
#include <memory>

#define N_OF_CHROMOSOMES 2


class Individual {
    double fitness;
    Chromosome chromosome[N_OF_CHROMOSOMES];

public:
    Individual();
    Individual(const Individual &individual);
    Individual(Chromosome chromosome[N_OF_CHROMOSOMES]);
    Individual(std::vector<Chromosome> chromosome);
    std::shared_ptr<Individual> mate(std::shared_ptr<Individual> partner);
    void mutate();
    double calculateFitness();
    double getFitness();
    Chromosome* getChromosome();

};

std::ostream& operator<<(std::ostream& os, std::shared_ptr<Individual>& individual);


#endif