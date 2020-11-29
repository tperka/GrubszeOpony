#include <cmath>
#include "Population.hpp"

Individual::Individual() {
    this->chromosome.generateRandomGenes(MIN_GEN_VALUE, MAX_GEN_VALUE);
    this->fitness = calculateFitness();
}

Individual::Individual(Chromosome chromosome) {
    this->chromosome = chromosome;
    fitness = calculateFitness();
}

// Individual Individual::mate(Individual partner){
//     Chromosome childChromosome;
//     int lengthOfChromosome = DIMENSIONS;
//     for(int i = 0; i < lengthOfChromosome; i++) {
//         double probability = randomInRange(0, 1.0);

//     }
// }

Individual Individual::mutate(double sigma) {
    double childGenes[DIMENSIONS];
    for(int i = 0; i < DIMENSIONS; i++) {
        childGenes[i] = this->chromosome.getGene()[i] + sigma * standardCauchyDistribution();
    }
    Chromosome childChromosome(childGenes);
    Individual child(childChromosome);
    return child;
}

double Individual::calculateFitness() {
    //TODO: GENERALIZE
    return sin(this->chromosome.getGene()[0]);
}

Chromosome Individual::getChromosome(){
    return this->chromosome;
}

double Individual::getFitness() {
    return this->fitness;
}

bool operator<(Individual& a, Individual& b) {
    return a.getFitness() < b.getFitness();
}