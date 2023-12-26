#pragma once
#include <memory>
#include <vector>
#include "GoLEngine.hpp"

#define NIter 100

class TargetFunc{
public:
    virtual ~TargetFunc() {};
    virtual std::unique_ptr<TargetFunc> copy() const = 0;
    virtual int get_target_function(std::vector<std::vector<bool>>& individ) = 0;
};


class GoLTargetFunc : public TargetFunc{
public:
    GoLTargetFunc(): engine(){}

    virtual std::unique_ptr<TargetFunc> copy() const override{
        return std::make_unique<GoLTargetFunc>(*this);
    }

    virtual int get_target_function(std::vector<std::vector<bool>>& generation) override{
        auto target = engine.get_next_generation(generation, NIter);
        unsigned res = 0;
        for (const auto& row : target) {
            for (const auto cell : row) {
                res += cell;
            }
        }
        if (target == engine.get_next_generation(target, 1)){
            res += generation.size() * generation.size();
        }
        return res;
    }
private:
    GoLEngine engine;
};
