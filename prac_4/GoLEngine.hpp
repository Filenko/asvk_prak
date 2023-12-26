#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class GoLEngine {
private:
    using field_type = std::vector<std::vector<bool>>;

    bool get_cell_next_state(const field_type& field, size_t x, size_t y) {
        int live_neighbors = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0)
                    continue;
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < field.size() && ny >= 0 && ny < field[0].size()) {
                    live_neighbors += field[nx][ny];
                }
            }
        }
        return (field[x][y] && (live_neighbors == 2 || live_neighbors == 3)) || (!field[x][y] && live_neighbors == 3);
    }

public:
    field_type get_next_generation(const field_type& field, int num_of_steps) {
        auto new_field = field;
        for (size_t step = 0; step < num_of_steps; ++step) {
            auto tmp_field = new_field;
            for (size_t x = 0; x < field.size(); ++x) {
                for (size_t y = 0; y < field[x].size(); ++y) {
                    new_field[x][y] = get_cell_next_state(tmp_field, x, y);
                }
            }
        }
        return new_field;
    }

    void print_field(const field_type& field) {
        for (const auto& row : field) {
            for (bool cell : row) {
                std::cout << (cell ? 'X' : '-') << ' ';
            }
            std::cout << std::endl;
        }
    }
    static void individ_to_file(const field_type& generation, const char* filename){
        std::ofstream file_data;
        file_data.open(filename);
        if (!file_data.is_open()){
            throw std::runtime_error("Fail opening file: ");
        }

        for(unsigned i = 0; i < generation.size(); i++){
            for (unsigned j=0; j < generation.size(); j++){
                file_data << ((generation[i][j]) ? 'X' : '-' ) << " ";
            }
            file_data << "\n";
        }

        file_data.close();
    }

};


