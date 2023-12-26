#include "../Crossing.cpp"
#include "../Mutation.cpp"
#include "../GoLEngine.hpp"
#include "../TargetFunc.cpp"
#include "../Selection.cpp"
#include "../GeneticAlgo.cpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

#define N_SERIES 10
#define ITERS_PER_SERIES 10

std::mutex file_mutex;

void run_experiment(int i, double init_mut_prob, std::ofstream& file_data) {
    double mut_prob = init_mut_prob * pow(1.5, i);
    GoLEngine game;
    RouletteSelection sel(100);
    GoLTargetFunc target_func;
    Crosser cros;
    Mutator mut(mut_prob);

    for (int j = 0; j < ITERS_PER_SERIES; j++) {
        GeneticAlgo gen_algo(sel, mut, cros, target_func, 100, 50);
        auto t_start = std::chrono::high_resolution_clock::now();
        gen_algo.run_algorithm();
        auto t_end = std::chrono::high_resolution_clock::now();
        auto t_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start).count();

        auto best_individ = gen_algo.get_best_individ();
        auto best_criterion = gen_algo.get_best_criterion();
        std::string filename1 = "series_" + std::to_string(i) + "_run_" + std::to_string(j) + "_sol.txt";
        std::string filename2 = "series_" + std::to_string(i) + "_run_" + std::to_string(j) + "_sol_after100.txt";
        GoLEngine::individ_to_file(best_individ, filename1.c_str());
        auto best_after100 = game.get_next_generation(best_individ, 100);
        GoLEngine::individ_to_file(best_after100, filename2.c_str());

        std::lock_guard<std::mutex> guard(file_mutex);
        file_data << i << "," << j << "," << mut_prob << "," << t_duration / 1e9 << "," << best_criterion << "\n";
        file_data.flush();
    }
}

int main() {
    std::ofstream file_data("genetic_algo_research.csv");
    if (!file_data.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    file_data << "series,iter,mut_prob,time_sec,best_criterion\n";

    double init_mut_prob = 1.0 / (50 * 50);
    std::vector<std::thread> threads;

    for (int i = 0; i < N_SERIES; i++) {
        threads.emplace_back(run_experiment, i, init_mut_prob, std::ref(file_data));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    file_data.close();
    return 0;
}
