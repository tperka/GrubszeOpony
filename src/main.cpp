#include <iostream>
#include "Population.hpp"

int main(int argc, const char** argv) {
    Population1plus1 population;
    Individual best = population.simulate();
    std::cout << "Minimum lokalnym naszej funkcji jest: " << best.getChromosome() << std::endl
    <<"O wartosci: " << best.getFitness() << std::endl;

    return 0;
}