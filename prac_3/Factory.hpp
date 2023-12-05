#pragma once

#include <string>
#include <map>
#include <utility>
#include <vector>
#include "Functions.hpp"


class TFactory {
private:
    class ICreator {
    public:
        virtual ~ICreator(){}
        virtual std::shared_ptr<TFunction> Create(double coefficient) = 0;
        virtual std::shared_ptr<TFunction> Create() = 0;
        virtual std::shared_ptr<TFunction> Create(std::vector<double> coefficients) = 0;
    };

    template<class T>
    class TCreator: public ICreator {
    public:
        std::shared_ptr<TFunction> Create(double coefficient) override {
            return std::make_shared<T>(coefficient);
        }

        std::shared_ptr<TFunction> Create() override {
            return std::make_shared<T>();
        }

        std::shared_ptr<TFunction> Create(std::vector<double> coefficients) override {
            return std::make_shared<T>(coefficients);
        }
    };

    std::map<std::string, std::shared_ptr<ICreator>> RegisteredCreators;

    template <class T>
    void RegisterCreator(const std::string& name) {
        RegisteredCreators[name] = std::make_shared<TCreator<T>>();
    }

    void RegisterAll() {
        RegisterCreator<Identical>("ident");
        RegisterCreator<Constant>("const");
        RegisterCreator<Polynomial>("polynomial");
        RegisterCreator<Power>("power");
        RegisterCreator<Exponential>("exp");
    }

public:
    TFactory() {
        RegisterAll();
    }

    std::shared_ptr<TFunction> Create(const std::string& type, double coefficient) {
        return RegisteredCreators[type]->Create(coefficient);
    }

    std::shared_ptr<TFunction> Create(const std::string& type) {
        return RegisteredCreators[type]->Create();
    }

    std::shared_ptr<TFunction> Create(const std::string& type, std::vector<double> coefficients) {
        return RegisteredCreators[type]->Create(coefficients);
    }
};
