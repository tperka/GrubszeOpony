#ifndef POPULATION_HPP
#define POPULATION_HPP

//zalecane parametry ze skryptu, str. 71 Tablica 9.
#define M 10
#define C1  0.82
#define C2  1.2
#define ITERATIONS 500
#define MAX_GEN_VALUE 3.5
#define MIN_GEN_VALUE -3.5
#define INITIAL_SIGMA 1
#define NO_OF_INDIVIDUALS 60;
#define LAMBDA 20;

#include "Individual.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    /* sort */

class Population1plus1{
    Individual individuals;
    int betterChildCounter;
    int generationsLeft;
    double sigma;
public:
    Population1plus1();
    void newGeneration();
    Individual simulate();

};

class Population_lambdaplus1{
   
   std::vector<std::shared_ptr<Individual> >individuals;
   std::vector<std::shared_ptr<Individual> >parents_of_new_children;

    int betterChildCounter;
    int generationsLeft;
    double sigma;

    void choose_new_parents();
    void breed_and_mutate();
    void sort_and_cut();
    void eval_individuals();

public:
    Population_lambdaplus1();
    void newGeneration();
    Individual simulate();

};

#endif // POPULATION_HPP


