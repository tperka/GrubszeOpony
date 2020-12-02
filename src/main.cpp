#include <iostream>
#include "Population.hpp"
#include "Utils.hpp"

int main(int argc, const char** argv) {
    Population population;
    std::shared_ptr<Individual> best = population.simulate();
    std::cout << "Najlepszym osobnikiem jest: " << best << std::endl;

    return 0;
}