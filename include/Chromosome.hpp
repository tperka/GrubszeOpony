#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#define DIMENSIONS 1



#include <iostream>

class Chromosome {
    double gene[DIMENSIONS];
public:
    Chromosome() {};
    Chromosome(double gene[DIMENSIONS]);
    void generateRandomGenes(double minValue, double maxValue);
    double* getGene();
};

std::ostream& operator<<(std::ostream& os, Chromosome chromosome);
#endif // CHROMOSOME_HPP