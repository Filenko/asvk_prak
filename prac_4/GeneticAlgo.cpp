#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include "Mutation.cpp"
#include "Selection.cpp"
#include "TargetFunc.cpp"
#include "Crossing.cpp"

#define MAX_NON_BEST_ITER 50

class GeneticAlgo{
public:
    GeneticAlgo(Selection& _selector, Mutation& _mutator,
                   Crossing& _crosser, TargetFunc& _target_func, unsigned population_size_, unsigned field_size_):
    selector(_selector.copy()),
    mutator(_mutator.copy()),
    crosser(_crosser.copy()),
    target_function(_target_func.copy()),
    population_size(population_size_),
    field_size(field_size_),
    best_result(field_size_ * field_size_)
     {};

    void run_algorithm(){
        int stable_iter = 0;
        init();
        best_generation = population[0];
        std::vector<unsigned> target_function_results;
        while (stable_iter < MAX_NON_BEST_ITER){
            stable_iter++;
            target_function_results = population_survaival_func();
            if (is_new_best(target_function_results)){
                stable_iter = 0;
            }

            auto selected_individs = population_selection(target_function_results);
            population = std::move(population_crossing(selected_individs));
            population_mutation();
        }
    }

    std::vector<std::vector<bool>> get_best_individ() const{
        return best_generation;
    }

    int get_best_criterion() const{
        return best_result;
    }

private:
    std::shared_ptr<Selection> selector;
    std::shared_ptr<Mutation> mutator;
    std::shared_ptr<Crossing> crosser;
    std::shared_ptr<TargetFunc> target_function;
    std::vector<std::vector<std::vector<bool>>> population;
    std::vector<std::vector<bool>> best_generation;
    unsigned best_result;
    unsigned population_size;
    unsigned field_size;

    void init(){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<> dist(0, 1);
        std::vector<std::vector<bool>> generation;
        for (size_t i = 0; i < field_size; ++i) {
            std::vector<bool> row(field_size);
            generation.push_back(row);
        }
        for (size_t population_num = 0; population_num < population_size; ++population_num){
            for (size_t i = 0; i < field_size; ++i) {
                for (size_t j = 0; j < field_size; ++j) {
                    generation[i][j] = dist(rng);
                }
            }
            population.push_back(generation);
        }
    }

    std::vector <unsigned> population_survaival_func(){
        std::vector <unsigned> target_function_results (population_size);
        for (size_t i = 0; i < population_size; ++i){
            target_function_results[i] = target_function->get_target_function(population[i]);
        }
        return target_function_results;
    }

    std::vector<std::vector<std::vector<bool>>>
    population_selection(const std::vector<unsigned>& target_function_results){
        std::vector<size_t> indices = selector->select(target_function_results);
        std::vector<std::vector<std::vector<bool>>> selected_generations;
        for (unsigned i = 0; i < population_size; i++){
            selected_generations.push_back(population[indices[i]]);
        }
        return selected_generations;
    }

    std::vector<std::vector<std::vector<bool>>>
    population_crossing(const std::vector<std::vector<std::vector<bool>>>& selected_individs){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<> ind_dist(0, population_size - 1);
        std::uniform_real_distribution<> cross_prob_dist(0, 1);
        decltype(population) new_population;
        double cross_prob = 0.8;
        while (new_population.size() < population.size() - 1){
            size_t i = ind_dist(rng);
            size_t j = ind_dist(rng);
            while (selected_individs[i] == selected_individs[j]) {
                i = ind_dist(rng);
                j = ind_dist(rng);
            };

            if (cross_prob_dist(rng) < cross_prob){
                auto childrens = crosser->cross(selected_individs[i], selected_individs[j]);
                new_population.push_back(std::move(childrens.first));
                new_population.push_back(std::move(childrens.second));
            }

        }
        return new_population;
    }

    void population_mutation(){
        for(unsigned i = 0; i < population_size; i++){
            population[i] = mutator->mutate(population[i]);
        }
    }

    inline bool is_new_best(const std::vector<unsigned>& target_function_results){
        auto min_element_iterator = std::min_element(target_function_results.begin(), target_function_results.end());
        auto min_element_index = min_element_iterator - target_function_results.begin();
        auto min_element = *min_element_iterator;
        if(min_element < best_result){
            best_generation = population[min_element_index];
            best_result = target_function_results[min_element_index];
            return true;
        } else {
            return false;
        }
    }
};