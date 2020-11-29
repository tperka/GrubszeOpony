#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

double randomInRange(double min, double max) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniDistribution(min, max);
    return uniDistribution(generator);
}

double standardCauchyDistribution() {
    std::default_random_engine generator;
    std::cauchy_distribution<double> cauchyDistribution(0.0, 1.0);
    return cauchyDistribution(generator);
}

#endif