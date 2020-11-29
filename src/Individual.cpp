#include "Individual.hpp"
#include "Utils.hpp"

Individual::Individual(Chromosome chromosome) {
    this->chromosome = chromosome;
    fitness = calculateFitness();
}

// Individual Individual::mate(Individual partner){
//     Chromosome childChromosome;
//     int lengthOfChromosome = DIMENSIONS;
//     for(int i = 0; i < lengthOfChromosome; i++) {
//         double probability = randomInRange(0, 1.0);

//     }
// }

Individual Individual::mutate() {
    Chromosome childChromosome(this->chromosome.getGene() + SIGMA * standardCauchyDistribution());
    Individual child(childChromosome);
    return child;
}