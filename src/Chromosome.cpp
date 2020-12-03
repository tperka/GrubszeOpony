#include "Chromosome.hpp"
#include "Utils.hpp"

Chromosome::Chromosome(std::vector<double> gene) {
    for(int i = 0; i < DIMENSIONS; i++) 
        this->gene[i] = gene[i];
}

Chromosome::Chromosome(double gene[DIMENSIONS]) {
    for(int i = 0; i < DIMENSIONS; i++) 
        this->gene[i] = gene[i];
}

void Chromosome::generateRandomGenes(double minValue, double maxValue) {
    for(int i = 0; i < DIMENSIONS; i++) 
        gene[i] = randomFloatInRange(minValue, maxValue);
}

double* Chromosome::getGene() {
    return gene;
}

void Chromosome::setGene(double gene[DIMENSIONS]) {
    for(int i = 0; i < DIMENSIONS; i++)
        this->gene[i] = gene[i];
    
}

std::ostream& operator<<(std::ostream& os, Chromosome chromosome) {
    double* gene = chromosome.getGene();
    for(int i = 0; i < DIMENSIONS; i++) {
        if(i != 0)  os << " ";
            os << gene[i];
    }
    return os;
}