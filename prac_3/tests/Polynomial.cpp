#include "gtest/gtest.h"
#include "../Functions.hpp"
#include "../Factory.hpp"

class PolynomialTests: public ::testing::Test {
public:
    std::shared_ptr<TFunction> c, d, e;
    void SetUp( ) {
        TFactory factory;
        c = factory.Create("polynomial", {-1, -1, 3, -4, 0, 1});
        d = factory.Create("ident", {1, 0, 1});
        e = factory.Create("const", 1.456);
    }

    void TearDown() {
    }

};

TEST_F(PolynomialTests, ToStringTest) {
    EXPECT_STREQ(c->ToString().c_str(), "-1-x^1+3x^2-4x^3+x^5");
    EXPECT_STREQ(d->ToString().c_str(), "x^1");
    EXPECT_STREQ(e->ToString().c_str(), "1.456");
}

TEST_F(PolynomialTests, OperatorParenthesesTest) {
    EXPECT_DOUBLE_EQ((*c)(1), -2);
    EXPECT_DOUBLE_EQ((*d)(-123), -123);
    EXPECT_DOUBLE_EQ((*e)(-123), 1.456);
}

TEST_F(PolynomialTests, DerivativesTest) {
    EXPECT_DOUBLE_EQ(c->Deriative(1), -2);
    EXPECT_DOUBLE_EQ(c->Deriative(0), -1);
    EXPECT_DOUBLE_EQ(c->Deriative(-1), -14);
}