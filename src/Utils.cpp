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

double variableDistribution() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::cauchy_distribution<double> cauchyDistribution(0.0, 1.0);
    return cauchyDistribution(generator);
}

double optimizedFunction(double* x){
    return -20*exp(-0.2 * sqrt(0.5 * (x[0] * x[0] + x[1] * x[1]))) - exp(0.5 * (cos(2*M_PI*x[0]) + cos(2*M_PI*x[1]))) + 20  + M_E;
}

int randomIntInRange(int min, int max) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> uniDistribution(min, max);
    return uniDistribution(generator);
}