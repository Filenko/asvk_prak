#pragma once
#include <vector>
#include <memory>

using field_type = std::vector<std::vector<bool>>;

class Crossing{
public:
    virtual std::pair<field_type, field_type> cross(const field_type& lhs, const field_type& rhs) = 0;
    virtual std::unique_ptr<Crossing> copy() const = 0;
    virtual ~Crossing() {};
};

class Crosser : public Crossing{
public:

    std::unique_ptr<Crossing> copy() const override{
        return std::make_unique<Crosser>(*this);
    }

    std::pair<field_type, field_type> cross(const field_type& lhs, const field_type& rhs) override{
        field_type children1 = lhs;
        field_type children2 = rhs;
        unsigned point = lhs.size() * lhs.size() / 3;
        for(size_t i = 0; i < lhs.size(); ++i) {
            for(size_t j = 0; j < rhs.size(); ++j) {
                if (i * lhs.size() + j > point) {
                    children1[i][j] = rhs[i][j];
                    children2[i][j] = lhs[i][j];
                }
            }
        }
        return {children1, children2};
    }
};