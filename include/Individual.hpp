#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP
#include <string>

#define DIMENSIONS 1

class Individual {
    double fitness;
    double* chromosome;
    Individual(std::string chromosome);
    Individual mate(Individual parent2);
    void mutate();
    double calculateAndGetFitness();
};

#endif