#pragma once
#include <memory>
#include <bitset>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>

class Selection{
public:
    virtual ~Selection() {};
    virtual std::unique_ptr<Selection> copy() const = 0;
    virtual std::vector<size_t> select(const std::vector<unsigned>& target_results) = 0;
};


class RouletteSelection : public Selection{
public:

    RouletteSelection(unsigned num_selections_) : num_selections(num_selections_) {}
    virtual std::unique_ptr<Selection> copy() const override{
        return std::make_unique<RouletteSelection>(*this);
    }

    virtual std::vector<size_t> select(const std::vector<unsigned>& target_results) override{
        int max_val = *std::max_element(target_results.begin(), target_results.end()) + 1;

        auto target_results_norm = target_results;
        for (size_t i = 0; i < target_results.size(); ++i) {
            target_results_norm[i] -= max_val;
        }
        unsigned total_fitness = std::accumulate(target_results_norm.begin(), target_results_norm.end(), 0.0);

        std::vector<double> probabilities(target_results_norm.size());
        for (size_t i = 0; i < target_results_norm.size(); ++i) {
            probabilities[i] = static_cast<double>(target_results_norm[i]) / total_fitness;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());

        std::vector<size_t> selected_indices;
        for (size_t i = 0; i < num_selections; ++i) {
            selected_indices.push_back(dist(gen));
        }

        return selected_indices;
    }
    private:
        unsigned num_selections;
};
