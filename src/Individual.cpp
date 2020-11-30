#include <cmath>
#include "Population.hpp"
#include "Utils.hpp"

Individual::Individual() {
    for(int i = 0; i < N_OF_CHROMOSOMES; i++)
        chromosome[i].generateRandomGenes(MIN_GEN_VALUE, MAX_GEN_VALUE);
    
    this->fitness = calculateFitness();
}

Individual::Individual(Chromosome chromosome[N_OF_CHROMOSOMES]) {
    for(int i = 0; i < N_OF_CHROMOSOMES; i++)
        this->chromosome[i] = chromosome[i];

    fitness = calculateFitness();
}

Individual Individual::mate(Individual partner){
    Chromosome childChromosomes[N_OF_CHROMOSOMES];
    double childGenes[DIMENSIONS];
    int lengthOfChromosome = DIMENSIONS;
    double weight = randomInRange(0.0, 1.0);
    for(int i = 0; i < N_OF_CHROMOSOMES; i++) {
        for(int j = 0; i < lengthOfChromosome; i++) {
            childGenes[j] = weight * chromosome[i].getGene()[j] + (1.0 - weight) * partner.getChromosome()[i].getGene()[j];
        }
        Chromosome temp(childGenes);
        childChromosomes[i] = temp;
    }
    
    Individual child(childChromosomes);
    return child;
}

Individual Individual::mutate(double sigma) {
    //TODO: strona 74 skryptu
    double childGenes[DIMENSIONS];
    for(int i = 0; i < DIMENSIONS; i++) {
        childGenes[i] = chromosome[1].getGene()[i] + sigma * standardCauchyDistribution();
    }
    Chromosome childChromosome(childGenes);
    Individual child(childChromosome);
    return child;
}

double Individual::calculateFitness() {
    //TODO: GENERALIZE
    return optimizedFunction(chromosome[0].getGene());
}

Chromosome* Individual::getChromosome(){
    return chromosome;
}

double Individual::getFitness() {
    return fitness;
}

bool operator<(Individual& a, Individual& b) {
    return a.getFitness() < b.getFitness();
}