#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#define DIMENSIONS 2

#include <iostream>
#include <vector>

class Chromosome {
    double gene[DIMENSIONS];
public:
    Chromosome() {};
    Chromosome(double gene[DIMENSIONS]);
    Chromosome(std::vector<double> gene);
    void generateRandomGenes(double minValue, double maxValue);
    double* getGene();
    void setGene(double gene[DIMENSIONS]);
};

std::ostream& operator<<(std::ostream& os, Chromosome chromosome);
#endif // CHROMOSOME_HPP