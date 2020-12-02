#include <iostream>
#include "Population.hpp"
#include "Utils.hpp"

int main(int argc, const char** argv) {
    Population_lambdaplus1 population;
    Individual best = population.simulate();
    std::cout << "Najlepszym osobnikiem jest: " << best << std::endl;

    return 0;
}