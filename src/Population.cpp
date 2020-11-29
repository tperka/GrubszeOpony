#include "Population.hpp"
#include <iostream>

Population::Population() {
    this->betterChildCounter = 0;
    this->generationsLeft = ITERATIONS;
    this->sigma = INITIAL_SIGMA;
}

void Population::newGeneration() {
    Individual child = individuals.mutate(sigma);
    if(child.getFitness() < individuals.getFitness()) {
        individuals = child;
        betterChildCounter++;
    }
        std::cout << "Dziecko" << child.getChromosome().getGene()[0] << std::endl
    <<"O wartosci: " << child.getFitness() << std::endl;
}

Individual Population::simulate() {
    while(generationsLeft >= 0) {
        newGeneration();
        generationsLeft--;
        if(generationsLeft % M == 0) {
            sigma *= (double) betterChildCounter / (double) M < 0.2 ? C1 : C2;
            betterChildCounter = 0;
        }
        std::cout << "Iteracja nr " << ITERATIONS - generationsLeft << " osobnik to " << individuals.getChromosome().getGene()[0] << std::endl
    <<"O wartosci: " << individuals.getFitness() << std::endl;
    }
    return individuals;
}

