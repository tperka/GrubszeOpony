#include <iostream>
#include "Population.hpp"
#include "Utils.hpp"

int main(int argc, const char** argv) {
    Population population;
    std::shared_ptr<Individual> best = (argc == 2 ? population.simulate(argv[1]) : population.simulate(""));
        
    std::cout << "Najlepszym osobnikiem jest: " << best << std::endl;

    return 0;
}