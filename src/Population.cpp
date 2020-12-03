#include "Population.hpp"
#include "Utils.hpp"
#include <iostream>
#include <memory>
#include <algorithm>    
#include <cmath>
#include <fstream>


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
    
    //SELEKCJA PROGOWA zgodnie z tym, co było na wykładzie
    double maxIndex = LAMBDA * RHO;
    probabilityOfBeingChosen.resize(individuals.size());
    for(int i = 0; i < maxIndex; ++i) {
        probabilityOfBeingChosen[i] = 1/maxIndex;
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



void Population::reproduce()
{
    offspring.clear();
    
    while(offspring.size() < LAMBDA)
    {
        //wybierz losowych rodziców
        int nOfPossibleParents = temporaryGeneration.size();
        int parent1Index = randomIntInRange(0, nOfPossibleParents - 1);
        int parent2Index = randomIntInRange(0, nOfPossibleParents - 1);
        std::shared_ptr<Individual> parent1 = temporaryGeneration[parent1Index];
        std::shared_ptr<Individual> parent2 = temporaryGeneration[parent2Index];
        std::cout << "rodzic1 " << parent1 << std::endl;
        std::cout << "rodzic2 " << parent2 << std::endl;
        std::shared_ptr<Individual> child(new Individual(*(parent1->mate(parent2))));
std::cout << "Dziecko przed mutacją " << child << std::endl;
        child->mutate();
std::cout << "Dziecko po mutacji " << child << std::endl;
        //sprawdzamy, czy utworzone dziecko nie wyszło poza obszar poszukiwań
        bool isChildCorrect = true;
        for(int i = 0; i < DIMENSIONS; ++i) {
            if(child->getChromosome()[0].getGene()[i] > MAX_X_Y_VALUE || child->getChromosome()[0].getGene()[i] < MIN_X_Y_VALUE)
                isChildCorrect = false;
        }
        
        if(isChildCorrect)
            offspring.push_back(child);
    }

}



std::shared_ptr<Individual> Population::simulate(std::string fileName) {

    std::ofstream resultFile;
    resultFile.open(fileName);

    //populację tworzymy stosując posiew równomierny
    for(int i=0; i < MI; ++i)
    {
        std::shared_ptr<Individual> tmp (new Individual());
        individuals.push_back(tmp);
    }

    int generationsLeft = ITERATIONS;

    while(generationsLeft > 0) {
        
        generateTemporaryGeneration();
        
        reproduce();

        selectNextGeneration();
        
        std::cout << "Iteracja nr " << ITERATIONS - generationsLeft + 1<< " najlepszy osobnik to (x y f_celu)" << individuals[0]<< std::endl;
        resultFile << individuals[0] << std::endl;
        generationsLeft--;
    }
    resultFile.close();
    return individuals[0];   //zwracamy najlepszego

}

