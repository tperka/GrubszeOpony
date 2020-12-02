#include <cmath>
#include "Population.hpp"
#include "Utils.hpp"

Individual::Individual() {
    chromosome[0].generateRandomGenes(MIN_X_Y_VALUE, MAX_X_Y_VALUE);
    chromosome[1].generateRandomGenes(MIN_SIGMA_VALUE, MAX_SIGMA_VALUE);
    
    fitness = calculateFitness();
}

Individual::Individual(const Individual &individual) {
    for(int i = 0; i < N_OF_CHROMOSOMES; i++) 
        chromosome[i] = individual.chromosome[i];
    
    fitness = calculateFitness();
}

Individual::Individual(Chromosome chromosome[N_OF_CHROMOSOMES]) {
    for(int i = 0; i < N_OF_CHROMOSOMES; i++)
        this->chromosome[i] = chromosome[i];

    fitness = calculateFitness();
}

std::shared_ptr<Individual> Individual::mate(std::shared_ptr<Individual> partner){
    //nie ma sensu nic robić jeżeli osobnik ma się reprodukować z samym sobą
    if(partner.get() == this) {
        return partner;
    }

    Chromosome childChromosomes[N_OF_CHROMOSOMES];
    double childGenes[DIMENSIONS];
    int lengthOfChromosome = DIMENSIONS;
    
    //stosujemy krzyżowanie z losową wagą
    double weight = randomFloatInRange(0.0, 1.0);
    
    for(int i = 0; i < N_OF_CHROMOSOMES; i++) {
        for(int j = 0; j < lengthOfChromosome; j++) {
            childGenes[j] = weight * chromosome[i].getGene()[j] + (1.0 - weight) * partner->getChromosome()[i].getGene()[j];
        }
        childChromosomes[i] = Chromosome(childGenes);
    }
    
    std::shared_ptr<Individual> child(new Individual(childChromosomes));
    return child;
}

void Individual::mutate() {
    //strona 74 skryptu Podstawy Sztucznej Inteligencji autorstwa Pawła Wawrzyńskiego.
    double childDistributionGenes[DIMENSIONS];
    double childGenes[DIMENSIONS];
    double tauprim = 1/sqrt(2*DIMENSIONS);
    double tau = 1/sqrt(sqrt(DIMENSIONS));
    double ksi = variableDistribution();
    double ksi_i, ny_i;     //używane do losowania dla każdego wymiaru wektora genów oddzielnie

    for(int i = 0; i < DIMENSIONS; i++) {
        ksi_i = variableDistribution();
        childDistributionGenes[i] = chromosome[N_OF_CHROMOSOMES - 1].getGene()[i] * exp(tauprim*ksi + tau*ksi_i);   //w naszym przypadku ostatni chromosom jest tablicą odchyleń standardowych rozkładów używanych do mutacji.
        
        ny_i = variableDistribution();
        childGenes[i] = chromosome[0].getGene()[i] * childDistributionGenes[i] * ny_i;
    }

    Chromosome childChromosomes[N_OF_CHROMOSOMES] = {(childDistributionGenes), (childGenes)};
    for(int i = 0; i < N_OF_CHROMOSOMES; i++)
        chromosome[i] = childChromosomes[i];
    
    fitness = calculateFitness();
}

double Individual::calculateFitness() {
    return optimizedFunction(chromosome[0].getGene());
}

Chromosome* Individual::getChromosome(){
    return chromosome;
}

double Individual::getFitness() {
    return fitness;
}


std::ostream& operator<<(std::ostream&os, std::shared_ptr<Individual>& individual) {
    os << individual->getChromosome()[0] << " " << individual->getFitness();
    return os;
}