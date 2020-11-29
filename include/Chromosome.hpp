#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP


class Chromosome {
    double gene;
public:
    Chromosome(double gene = 0.0) {this->gene = gene;};
    void generateRandomGenes();
    double getGene() {return gene;}
};

#endif // CHROMOSOME_HPP