#ifndef POPULATION_HPP
#define POPULATION_HPP

#define USE_CAUCHY_DISTRIBUTION 0
#define MAXIMIZATION 0

#define ITERATIONS 1

#define START_POINT_X 10.0
#define START_POINT_Y 10.0

#define MAX_X_Y_VALUE 100000
#define MIN_X_Y_VALUE -100000

#define MAX_SIGMA_VALUE 0.5
#define MIN_SIGMA_VALUE 0.1


//proporcja zaproponowana na wykładzie
#define MI 50
#define LAMBDA 350

//nacisk selekcyjny do selekcji progowej
#define RHO 0.75



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


public:
    Population();
    std::shared_ptr<Individual> simulate(std::string fileName = "result.txt");

};

#endif // POPULATION_HPP


