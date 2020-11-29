#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#define DIMENSIONS 1


#include <Utils.hpp>

class Chromosome {
    double gene[DIMENSIONS];
public:
    Chromosome() {};
    Chromosome(double gene[DIMENSIONS]) {for(int i = 0; i < DIMENSIONS; i++) this->gene[i] = gene[i];};
    void generateRandomGenes(double minValue, double maxValue){for(int i = 0; i < DIMENSIONS; i++) this->gene[i] = randomInRange(minValue, maxValue);};
    double* getGene() {return gene;}
};

#endif // CHROMOSOME_HPP