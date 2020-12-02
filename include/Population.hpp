#ifndef POPULATION_HPP
#define POPULATION_HPP


#define MAXIMIZATION 0

#define ITERATIONS 1

#define MAX_GEN_VALUE 10
#define MIN_GEN_VALUE -10
#define MAX_SIGMA_VALUE 5
#define MIN_SIGMA_VALUE 0.1



#define MI 20
#define LAMBDA 140

//rho używane do selekcji progowej osobników do reprodukcji
#define RHO 1.0


#include "Individual.hpp"

#include <vector>
#include <memory>



class Population_lambdaplus1{
   
   std::vector<std::shared_ptr<Individual>> individuals;
   std::vector<std::shared_ptr<Individual>> temporaryGeneration;
   std::vector<std::shared_ptr<Individual>> offspring;
    std::vector<double> probabilityOfBeingChosen;


    void breed_and_mutate();
    void sort_and_cut();
    void selectForReproduction();
    void generateTemporaryGeneration();
    void calculateNormalizedFitness(std::vector<std::shared_ptr<Individual>> generation);

public:
    Population_lambdaplus1();
    void newGeneration();
    Individual simulate();

};

#endif // POPULATION_HPP


