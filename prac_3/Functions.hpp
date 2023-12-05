#pragma once

#include <string>
#include <memory>
#include <vector>

class TFunction {
public:
    virtual std::string ToString() const = 0;
    virtual double Deriative(double) const = 0;
    virtual double operator()(double) const = 0;
    virtual std::shared_ptr<TFunction> Copy() const = 0;
};

class Sum : public TFunction {
public:
    Sum(TFunction& lf_, TFunction& rf_, std::string type_);
    std::string ToString() const override;
    double Deriative(double x) const override;
    double operator()(double x) const override;
    std::shared_ptr<TFunction> Copy() const override;

private:
    std::shared_ptr<TFunction> lf, rf;
    std::string type;
};


class Exponential : public TFunction {
public:
    Exponential() : coefficient(0) {};
    explicit Exponential(double x) : coefficient(x) {};
    explicit Exponential(std::vector<double>);
    std::string ToString() const override;
    double Deriative(double) const override;
    auto operator()(double) const -> double override;
    auto Copy() const -> std::shared_ptr<TFunction> override;
private:
    double coefficient;
};

class Polynomial : public TFunction {
private:
    auto removeTrailingZeroes() -> void;
protected:
    std::vector<double> polynomialVector;
public:
    Polynomial();
    Polynomial(double);
    Polynomial(std::vector<double>&);

    std::string ToString() const override;
    double Deriative(double) const override;
    double operator()(double) const override;
    std::shared_ptr<TFunction> Copy() const override;
};

class Identical: public Polynomial {
public:
    Identical();
    explicit Identical(double);
    explicit Identical(std::vector<double>);
};

class Constant: public Polynomial {
public:
    explicit Constant(double);
    Constant();
    explicit Constant(std::vector<double> v);
};

class Power : public TFunction {
private:
    double degree;
public:
    explicit Power(double degree) : degree(degree) {};
    explicit Power(std::vector<double> v);
    Power() : degree(0) {};
    auto ToString() const -> std::string override;
    double Deriative(double) const override;
    double operator()(double) const override;
    std::shared_ptr<TFunction> Copy() const override;
};


template <typename T>
Sum operator+(TFunction& lf, T& rf) {
    if constexpr (std::is_base_of_v<TFunction, T>) {
        return Sum(lf, rf, "+");
    } else {
        throw std::logic_error("Invalide type!");
    }
}

template <typename T>
Sum operator-(TFunction& lf, T& rf) {
    if constexpr (std::is_base_of_v<TFunction, T>) {
        return Sum(lf, rf, "-");
    } else {
        throw std::logic_error("Invalide type!");
    }
}

template <typename T>
Sum operator*(TFunction& lf, T& rf) {
    if constexpr (std::is_base_of_v<TFunction, T>) {
        return Sum(lf, rf, "*");
    } else {
        throw std::logic_error("Invalide type!");
    }
}

template <typename T>
Sum operator/(TFunction& lf, T& rf) {
    if constexpr (std::is_base_of_v<TFunction, T>) {
        return Sum(lf, rf, "/");
    } else {
        throw std::logic_error("Invalide type!");
    }
}
