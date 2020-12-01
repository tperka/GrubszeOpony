#include "Population.hpp"
#include <iostream>

Population1plus1::Population1plus1() {
    this->betterChildCounter = 0;
    this->generationsLeft = ITERATIONS;
    this->sigma = INITIAL_SIGMA;
}

void Population1plus1::newGeneration() {
    Individual child = individuals.mutate(sigma);
    if(child.getFitness() < individuals.getFitness()) {
        individuals = child;
        betterChildCounter++;
    }
        std::cout << "Dziecko: " << child.getChromosome() << std::endl
    <<"O wartosci: " << child.getFitness() << std::endl;
}

Individual Population1plus1::simulate() {
    while(generationsLeft >= 0) {
        newGeneration();
        generationsLeft--;
        if(generationsLeft % M == 0) {
            sigma *= (double) betterChildCounter / (double) M < 0.2 ? C1 : C2;
            betterChildCounter = 0;
        }
        std::cout << "Iteracja nr " << ITERATIONS - generationsLeft << " osobnik to " << individuals.getChromosome() << std::endl
    <<"O wartosci: " << individuals.getFitness() << std::endl;
    }
    return individuals;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool sort_by_fittnes(const std::shared_ptr<Individual> lhs, const std::shared_ptr<Individual> rhs)
{
return lhs->calculateFitness()> rhs->calculateFitness();

}


void Population_lambdaplus1::sort_and_cut()
{
    //sorting
   sort(individuals.begin(), individuals.end(), sort_by_fittnes);

for(int i = individuals.size()-NO_OF_INDIVIDUALS;i>0;--i)
{
    individuals.pop_back();//usuwamy lambda najgorszych osobnikow
}

}
Population_lambdaplus1::Population_lambdaplus1() {
    this->betterChildCounter = 0;
    this->generationsLeft = ITERATIONS;
    this->sigma = INITIAL_SIGMA;
}

void Population_lambdaplus1::choose_new_parents()
{
srand (time(NULL));
parents_of_new_children.clear();

for(int i=0 ; i<=LAMBDA ; ++i)
{
    int parent_1= rand() % 59 ;
    int parent_2= rand() % 59 ;
    parents_of_new_children.push_back(individuals[parent_1]);
    parents_of_new_children.push_back(individuals[parent_2]);
}
}
void Population_lambdaplus1::breed_and_mutate() //Funkcja bierze dwóch wyznaczonych rodziców i tworzy nowe dziecko
{

for(int i=0 ; i<=LAMBDA ; ++i)
{
    //tutaj trzeba trochę magii wskaźnikowej.
individuals.push_back(
                        std::shared_ptr<Individual> A(
                        parents_of_new_children[i]->mate(
                            *parents_of_new_children[i+1].get()
                            )   
                        )
                    );
}



}



Individual Population_lambdaplus1::simulate() {

    //napełnianie tablicy populacją
    for(int i=0; i<NO_OF_INDIVIDUALS; ++i)
    {
        std::shared_ptr<Individual> tmp (new Individual);
        individuals.push_back(tmp);
    }

    while(generationsLeft >= 0) {
        choose_new_parents();
        breed_and_mutate();
        eval_individuals();
        sort_and_cut();
        std::cout << "Iteracja nr " << ITERATIONS - generationsLeft << " osobnik to " << individuals.getChromosome() << std::endl
    <<"O wartosci: " << individuals[0]->getFitness() << std::endl;
    }
    return *individuals[0].get();   //zwracamy najlepszego

}

