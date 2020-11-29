#include <iostream>
#include "Population.hpp"

int main(int argc, const char** argv) {
    Population population;
    Individual best = population.simulate();
    std::cout << "Minimum lokalnym sinusa jest: " << best.getChromosome().getGene()[0] << std::endl
    <<"O wartosci: " << best.getFitness() << std::endl;

    return 0;
}