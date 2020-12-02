#include "Population.hpp"
#include "Utils.hpp"
#include <iostream>
#include <memory>
#include <algorithm>    /* sort */
#include <iostream>
#include <cmath>



bool sort_by_fittnes(const std::shared_ptr<Individual> lhs, const std::shared_ptr<Individual> rhs)
{
    
    return lhs->calculateFitness() > rhs->calculateFitness();

}


void Population_lambdaplus1::sort_and_cut()
{
    temporaryGeneration.clear();
    //łączymy pokolenie pierwotne z pochodnym
    individuals.insert(individuals.end(), offspring.begin(), offspring.end());
    //sortujemy, najlepsze osobniki są na początku
    sort(individuals.begin(), individuals.end(), sort_by_fittnes);
    //liczymy znormalizowaną wartość funkcji celu
    calculateNormalizedFitness(individuals);
    //obliczamy prawdopodobieństwo na podstawie stosunku wartości znormalizowanej funkcji celu do ich sumy (selekcja ruletkowa)
    double sumOfNormalizedFitness = 0;
    for(auto i : individuals) {
        sumOfNormalizedFitness += i->getNormalizedFitness();
    }
    probabilityOfBeingChosen.resize(individuals.size());
    for(int i = 0; i < (int)individuals.size(); i++) {
        probabilityOfBeingChosen[i] = individuals[i]->getNormalizedFitness() / sumOfNormalizedFitness;
    }

    while(temporaryGeneration.size() < MI) {
        double randomValue = randomFloatInRange(0.0, 1.0);
        double suffixSum = 0;
        int chosenPosition = -1;
        
        for(; suffixSum <= randomValue; chosenPosition++) {
            suffixSum += probabilityOfBeingChosen[chosenPosition];
        }

        temporaryGeneration.push_back(individuals[chosenPosition]);
    }
    individuals = temporaryGeneration;
    sort(individuals.begin(), individuals.end());
}

Population_lambdaplus1::Population_lambdaplus1() {
}

void Population_lambdaplus1::generateTemporaryGeneration() {
    
    temporaryGeneration.clear();
    while(temporaryGeneration.size() != LAMBDA)
    {
        std::shared_ptr<Individual> random = individuals[randomIntInRange(0, individuals.size() - 1)];
        temporaryGeneration.push_back(random);
    }
}

void Population_lambdaplus1::calculateNormalizedFitness(std::vector<std::shared_ptr<Individual>> generation) {
    //obliczanie średniej wartosci funkcji celu
    double sumOfFitness = 0;
    for(auto i : generation) {
        sumOfFitness += i->getFitness();
    }
    double meanFitness = sumOfFitness / generation.size();

    //obliczanie odchylenia standardowego funkcji celu
    double varianceOfFitness = 0;
    for(auto i : generation) {
        varianceOfFitness += pow(i->getFitness() - meanFitness, 2);
    }

    double standardDeviationOfFitness = sqrt(varianceOfFitness);
    //std::cout << "Prawdopodobienstwo wyboru osobnika to  " << probabilityOfBeingChosen << std::endl;
    for(auto i : generation) {
        i->setNormalizedFitness( (i->getFitness() - meanFitness) * RHO / standardDeviationOfFitness );
    }
}


void Population_lambdaplus1::breed_and_mutate() //Funkcja bierze dwóch wyznaczonych rodziców i tworzy nowe dziecko
{
    offspring.clear();

    while(offspring.size() < LAMBDA)
    {
        //wybierz losowych rodziców z wybranych do reprodukcji
        int nOfPossibleParents = temporaryGeneration.size();

        std::shared_ptr<Individual> parent1 = temporaryGeneration[randomIntInRange(0, nOfPossibleParents - 1)];
        std::shared_ptr<Individual> parent2 = temporaryGeneration[randomIntInRange(0, nOfPossibleParents - 1)];
        std::cout << "rodzic1: " <<*parent1 << std::endl << "rodzic2: " << *parent2 << std::endl;
   
        std::shared_ptr<Individual> child(new Individual(*(parent1->mate(parent2))));
        std::cout << "Dziecko przed mutacjo " <<*child << std::endl;
        child->mutate();
        std::cout << "Dziecko po mutacji " <<*child << std::endl;
        offspring.push_back(child);
    }

}



Individual Population_lambdaplus1::simulate() {

    //napełnianie tablicy populacją
    for(int i=0; i < MI; ++i)
    {
        std::shared_ptr<Individual> tmp (new Individual());
        individuals.push_back(tmp);
    }

    int generationsLeft = ITERATIONS;

    while(generationsLeft >= 0) {
        
        generateTemporaryGeneration();
        
        breed_and_mutate();

        sort_and_cut();
        
        std::cout << "Iteracja nr " << ITERATIONS - generationsLeft << " najlepszy osobnik to " << *individuals[0]<< std::endl;

        generationsLeft--;
    }

    return *(individuals[0].get());   //zwracamy najlepszego

}

