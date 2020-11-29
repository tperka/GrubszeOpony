#include "Utils.hpp"
#include <random>
#include <chrono>

double randomInRange(double min, double max) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> uniDistribution(min, max);
    return uniDistribution(generator);
}

double standardCauchyDistribution() {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::cauchy_distribution<double> cauchyDistribution(0.0, 1.0);
    return cauchyDistribution(generator);
}