#include "Population.hpp"
#include "Utils.hpp"
#include <iostream>
#include <memory>
#include <algorithm>    /* sort */
#include <iostream>
#include <cmath>



bool sort_by_fittnes(const std::shared_ptr<Individual> lhs, const std::shared_ptr<Individual> rhs)
{
    
    return MAXIMIZATION ? lhs->calculateFitness() > rhs->calculateFitness() : lhs->calculateFitness() < rhs->calculateFitness();

}


void Population::selectNextGeneration()
{
    temporaryGeneration.clear();
    //łączymy pokolenie pierwotne z pochodnym
    individuals.insert(individuals.end(), std::make_move_iterator(offspring.begin()), std::make_move_iterator(offspring.end()));
    //sortujemy, najlepsze osobniki są na początku
    sort(individuals.begin(), individuals.end(), sort_by_fittnes);

    //obliczamy prawdopodobieństwo na podstawie stosunku wartości znormalizowanej funkcji celu do ich sumy (selekcja ruletkowa)
    double sumOfFitness = 0;
    for(auto i : individuals) {
        sumOfFitness += i->getFitness();
    }
    // TODO: OGARNIJ PRAWDOPODOBIEŃSTWA
    probabilityOfBeingChosen.resize(individuals.size());
    for(int i = 0; i < (int)individuals.size(); i++) {
        probabilityOfBeingChosen[i] = individuals[i]->getFitness() / sumOfFitness;
        //if(!MAXIMIZATION)
        //    probabilityOfBeingChosen[i] = 1 - probabilityOfBeingChosen[i];
        std::cout << "prawdopodobienstwo wyboru rowne" << probabilityOfBeingChosen[i] << std::endl;
    }

    /*
        wybór losowego osobnika z nierównym prawdopodobieństwem można potraktować jako ułożenie w rzędzie wszystkich prawdopodobieństw 
        pojedynczych osobników (zajmą one na osi liczbowej cały zbiór [0;1]), a następnie wylosowanie losowej liczby z tego zbioru i wzięcie osobnika,
        który pokrywa obszar, w który strzeliliśmy. W tym wypadku dokonujemy tego za pomocą sumowania prawdopodobieństw od lewej strony, dopóki nie 
        uzyskamy liczby większej od wylosowanej, co mówi, że ostatni badany osobnik pokrywa obszar, na którym znalazła się wylosowana liczba

    */
    while(temporaryGeneration.size() < MI) {
        double randomValue = randomFloatInRange(0.0, 1.0);
        double suffixSum = probabilityOfBeingChosen[0];
        int chosenPosition = 0;
        
        for(; suffixSum <= randomValue; chosenPosition++) {
            suffixSum += probabilityOfBeingChosen[chosenPosition+1];
        }

        temporaryGeneration.push_back(individuals[chosenPosition]);
    }
    individuals = temporaryGeneration;
    sort(individuals.begin(), individuals.end());
}

Population::Population() {
}

void Population::generateTemporaryGeneration() {
    
    temporaryGeneration.clear();
    while(temporaryGeneration.size() < LAMBDA)
    {
        std::shared_ptr<Individual> random = individuals[randomIntInRange(0, individuals.size() - 1)];
        temporaryGeneration.push_back(random);
    }
}

void Population::calculateNormalizedFitness(std::vector<std::shared_ptr<Individual>> generation) {
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


void Population::reproduce() //Funkcja bierze dwóch wyznaczonych rodziców i tworzy nowe dziecko
{
    offspring.clear();
    
    while(offspring.size() < LAMBDA)
    {
        //wybierz losowych rodziców z wybranych do reprodukcji
        int nOfPossibleParents = temporaryGeneration.size();
        int parent1Index = randomIntInRange(0, nOfPossibleParents - 1);
        int parent2Index = randomIntInRange(0, nOfPossibleParents - 1);
        std::shared_ptr<Individual> parent1 = temporaryGeneration[parent1Index];
        std::shared_ptr<Individual> parent2 = temporaryGeneration[parent2Index];

        
        std::shared_ptr<Individual> child(new Individual(*(parent1->mate(parent2))));

        child->mutate();

        offspring.push_back(child);
    }

}



std::shared_ptr<Individual> Population::simulate() {

    //napełnianie tablicy populacją
    for(int i=0; i < MI; ++i)
    {
        std::shared_ptr<Individual> tmp (new Individual());
        individuals.push_back(tmp);
    }

    int generationsLeft = ITERATIONS;

    while(generationsLeft >= 0) {
        
        generateTemporaryGeneration();
        
        reproduce();

        selectNextGeneration();
        
        std::cout << "Iteracja nr " << ITERATIONS - generationsLeft << " najlepszy osobnik to " << individuals[0]<< std::endl;

        generationsLeft--;
    }

    return individuals[0];   //zwracamy najlepszego

}

