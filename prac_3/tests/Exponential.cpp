#include "gtest/gtest.h"
#include "../Functions.hpp"
#include "../Factory.hpp"
#include <math.h>


class ExponentTests : public ::testing::Test {
protected:
    std::shared_ptr<TFunction> a, b, c;
    void SetUp() override {
        TFactory factory;
        a = factory.Create("exp", 0);
        b = factory.Create("exp", {0, 1});
        c = factory.Create("exp", {-1, -1, 2, -2, 0, 1});
    }
};


TEST_F(ExponentTests, ToStringTest) {
    EXPECT_STREQ(a->ToString().c_str(), "1");
    EXPECT_STREQ(b->ToString().c_str(), "1");
    EXPECT_STREQ(c->ToString().c_str(), "exp(-1.000000*x)");
}

TEST_F(ExponentTests, OperatorParenthesesTest) {
    EXPECT_DOUBLE_EQ((*a)(0), 1);
    EXPECT_DOUBLE_EQ((*a)(-12), 1);
    EXPECT_NEAR((*c)(-12), exp(12), 0.01);
    EXPECT_NEAR((*c)(12), exp(-12), 0.01);
}