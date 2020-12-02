#ifndef POPULATION_HPP
#define POPULATION_HPP


#define MAXIMIZATION 0

#define ITERATIONS 3

#define MAX_X_Y_VALUE 100
#define MIN_X_Y_VALUE -100

#define MAX_SIGMA_VALUE 2
#define MIN_SIGMA_VALUE 0.1



#define MI 5
#define LAMBDA 25

//rho używane do selekcji progowej osobników do reprodukcji
#define RHO 1.0


#include "Individual.hpp"

#include <vector>
#include <memory>



class Population{
   
   std::vector<std::shared_ptr<Individual>> individuals;
   std::vector<std::shared_ptr<Individual>> temporaryGeneration;
   std::vector<std::shared_ptr<Individual>> offspring;
    std::vector<double> probabilityOfBeingChosen;


    void reproduce();
    void selectNextGeneration();
    void selectForReproduction();
    void generateTemporaryGeneration();
    void calculateNormalizedFitness(std::vector<std::shared_ptr<Individual>> generation);

public:
    Population();
    std::shared_ptr<Individual> simulate();

};

#endif // POPULATION_HPP


