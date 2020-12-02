#include "Utils.hpp"
#include <random>
#include <chrono>
#include <iostream>

double randomFloatInRange(double min, double max) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> uniDistribution(min, max);
    return uniDistribution(generator);
}

double standardCauchyDistribution() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::cauchy_distribution<double> cauchyDistribution(0.0, 1.0);
    return cauchyDistribution(generator);
}

double optimizedFunction(double* x){
    return -exp(-sqrt((x[0] * x[0] + x[1] * x[1]) / 2)) - exp((cos(2*M_PI*x[0]) + cos(2*M_PI*x[1]))/2) + 1 + exp(1);
}

int randomIntInRange(int min, int max) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> uniDistribution(min, max);
    return uniDistribution(generator);
}