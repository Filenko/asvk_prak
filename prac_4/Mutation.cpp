#pragma once

#include <vector>
#include <random>
#include <memory>

class Mutation {
public:
    virtual std::vector<std::vector<bool>> mutate(const std::vector<std::vector<bool>>& individ) = 0;
    virtual std::unique_ptr<Mutation> copy() const = 0;
    virtual ~Mutation() {};
};

class Mutator: public Mutation{
public:
    Mutator(double probability_): probability(probability_){};

    std::unique_ptr<Mutation> copy() const override{
        return std::make_unique<Mutator>(*this);
    }

    std::vector<std::vector<bool>> mutate(const std::vector<std::vector<bool>>& individ) override{
        std::vector<std::vector<bool>> mutated = individ;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> mutation_prob(0, 1);

        for (size_t i = 0; i < mutated.size(); ++i){
            for (size_t j = 0; j < mutated.size(); ++j) {
                if (mutation_prob(gen) < probability){
                    mutated[i][j] = ~mutated[i][j];
                }
            }
        }
        return mutated;
    }
private:
    double probability;
};