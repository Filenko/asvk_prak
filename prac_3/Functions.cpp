#include <math.h>
#include <sstream>
#include "Functions.hpp"
#include <iostream>


Sum::Sum(TFunction& lf_, TFunction& rf_, std::string type_) :
    lf(lf_.Copy()), rf(rf_.Copy()), type(type_) {}

double Sum::Deriative(double x) const{
    if (type == "+") {
        return (*lf).Deriative(x) + (*rf).Deriative(x);
    } else if (type == "-") {
        return (*lf).Deriative(x) - (*rf).Deriative(x);
    } else if (type == "*") {
        return ((*lf).Deriative(x) * (*rf)(x) + (*rf).Deriative(x) * (*lf)(x));
    } else if (type == "/") {
        return ((*lf).Deriative(x) * (*rf)(x) - (*lf)(x) * (*rf).Deriative(x)) / ((*rf)(x) * (*rf)(x));
    } else {
        throw std::logic_error("Invalide type!");
    }
}

double Sum::operator()(double x) const{
    if (type == "+") {
        return (*lf)(x) + (*rf)(x);
    } else if (type == "-") {
        return (*lf)(x) - (*rf)(x);
    } else if (type == "*") {
        return (*lf)(x) * (*rf)(x);
    } else if (type == "/") {
        return (*lf)(x) / (*rf)(x);
    } else {
        throw std::logic_error("No such type!");
    }
}

std::string Sum::ToString() const {
    if (type == "+") {
        return "(" + (*lf).ToString() + ")" + "+" + "(" + (*rf).ToString() + ")";
    } else if (type == "-") {
        return "(" + (*lf).ToString() + ")" + "-" + "(" + (*rf).ToString() + ")";
    } else if (type == "*") {
        return "(" + (*lf).ToString() + ")" + "*" + "(" + (*rf).ToString() + ")";
    } else if (type == "/") {
        return "(" + (*lf).ToString() + ")" + "/" + "(" + (*rf).ToString() + ")";
    } else {
        throw std::logic_error("No such type!");
    }
}

std::shared_ptr<TFunction> Sum::Copy() const {
    return std::make_shared<Sum>(*lf, *rf, type);
}

Exponential::Exponential(std::vector<double> coefficient_) : coefficient(coefficient_[0]) {
    if (!coefficient_.empty())
        coefficient = coefficient_[0];
    else
        coefficient = 0;
}

double Exponential::Deriative(double x) const {
    return (coefficient * exp(coefficient * x));
}

double Exponential::operator()(double x) const {
    return (exp(coefficient * x));
}

std::string Exponential::ToString() const {
    if (coefficient == 0)
        return "1";
    else
        return "exp(" + std::to_string(coefficient) + "*x)";
}

std::shared_ptr<TFunction> Exponential::Copy() const {
    return std::make_shared<Exponential>(*this);
}

Polynomial::Polynomial() {
    polynomialVector = {0};
}

Polynomial::Polynomial(double coefficient_) {
    polynomialVector = {coefficient_};
}

Polynomial::Polynomial(std::vector<double>& coefficient_) {
    for (int idx = 0; idx < coefficient_.size(); idx++)
        polynomialVector.push_back(coefficient_[idx]);
}

double Polynomial::Deriative(double x) const {
    double res = 0;
    for (size_t i = 0; i < polynomialVector.size(); ++i) {
        if (i > 0) {
            res += i * polynomialVector[i] * pow(x, i - 1);
        }
    }
    return res;
}

double Polynomial::operator()(double x) const {
    double res = 0;
    for (size_t i = 0; i < polynomialVector.size(); ++i) {
        if (polynomialVector[i] != 0) {
            res += polynomialVector[i] * pow(x, i);
        }
    }
    return res;
}

std::string Polynomial::ToString() const {
    std::ostringstream result;
    bool first_function = true;
    for (size_t degree = 0; degree < polynomialVector.size(); ++degree) {
        const auto coefficient = polynomialVector[degree];
        const auto positive = coefficient >= 0;
        if (coefficient != 0) {
            if (degree == 0) {
                result << coefficient;
                first_function = false;
                continue;
            }
            if (positive) {
                if (coefficient == 1) {
                    const auto sign = first_function ? "" : "+";
                    result << sign << "x^" << degree;
                    first_function = false;
                } else {
                    const auto sign = first_function ? "" : "+";
                    result << sign << coefficient << "x^" << degree;
                    first_function = false;
                }
            } else {
                if (coefficient == -1) {
                    result << "-" << "x^" << degree;
                    first_function = false;
                } else {
                    result << coefficient << "x^" << degree;
                    first_function = false;
                }
            }
        }
    }
    return std::string(result.str());
}

std::shared_ptr<TFunction> Polynomial::Copy() const {
    return std::make_shared<Polynomial>(*this);
}

Power::Power(std::vector<double> v) {
    if (!v.empty()) {
        this->degree = int(v[0]);
    } else {
        this->degree = 0;
    }
}

std::string Power::ToString() const{
    if (degree == 0) {
        return "1";
    }
    return "x^(" + std::to_string(degree) + ")";
}

Identical::Identical() {
    polynomialVector = {0};
}

Identical::Identical(double) {
        polynomialVector = {0, 1};
}

Identical::Identical(std::vector<double>) {
        polynomialVector = {0, 1};
}

Constant::Constant(double x) {
    polynomialVector = {x};
}

Constant::Constant() {
    polynomialVector = {0};
}

Constant::Constant(std::vector<double> v) {
    !v.empty() ? polynomialVector = {v[0]} : polynomialVector = {0};
}

double Power::Deriative(double point) const {
    if (degree == 0) {
        return 0;
    }
    return degree * pow(point, degree-1);
}

double Power::operator()(double point) const {
    return pow(point, degree);
}

std::shared_ptr<TFunction> Power::Copy() const {
    return std::make_shared<Power>(*this);
}
