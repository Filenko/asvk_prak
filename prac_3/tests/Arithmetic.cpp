#include "gtest/gtest.h"
#include "../Functions.hpp"
#include "../Factory.hpp"
#include <iostream>

class ArithmeticTests : public ::testing::Test {
public:
    TFactory factory;
    std::shared_ptr<TFunction> a, b, c, d;

    void SetUp() override
    {
        a = factory.Create("polynomial", {1, -2, 1});
        b = factory.Create("polynomial", {0, 0, 0, 2});
        c = factory.Create("polynomial", {0, 1, 0});
        d = factory.Create("exp", -2);
    }
};


TEST_F(ArithmeticTests, SumTests) {
    EXPECT_STREQ((*a + *b).ToString().c_str(), "(1-2x^1+x^2)+(2x^3)");
    EXPECT_DOUBLE_EQ((*a + *b).Deriative(1), 6);
    EXPECT_DOUBLE_EQ((*a + *b).Deriative(0), -2);

}


TEST_F(ArithmeticTests, ProdAndDivOnlyDerivatives) {
    EXPECT_DOUBLE_EQ(((*c)*(*b)).Deriative(1), 8);
    EXPECT_DOUBLE_EQ(((*b)/(*c)).Deriative(1), 4);
}

// TEST_F(ArithmeticTests, GetRootTests) {

//     auto r = getRoot(a, 10, 0.1, 220);
//     std::cout << r << std::endl;
//     EXPECT_NEAR(getRoot(a, 10, 0.1, 220), 1, 0.1);
//     EXPECT_NEAR(getRoot(b, 10, 0.1, 250), 0, 0.1);
//     EXPECT_NEAR(getRoot(c, 10, 0.1, 220), 0, 0.1);

// }

TEST(ErrorTests, TestOperationsErrors) {
    TFactory fact;
    auto fun = fact.Create("exp", 2);
    ASSERT_THROW(*fun + "Hello", std::logic_error);
    ASSERT_THROW(*fun - "Timofey", std::logic_error);
    ASSERT_THROW(*fun * "Bobo", std::logic_error);
    ASSERT_THROW(*fun / "QQ", std::logic_error);
}

TEST(Functions, TestPowerString) {
    TFactory fact;
    auto fun_1 = fact.Create("power", 3);
    ASSERT_EQ("x^(3.000000)", fun_1->ToString());
}

TEST(Functions, TestPolynomialString) {
    TFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 11, 0,  3, 1, 20});
    ASSERT_EQ("7+11x^1+3x^3+x^4+20x^5", fun_1->ToString());
}


TEST(Functions, TestIdentString) {
    TFactory fact;
    auto fun_1 = fact.Create("ident", 1);
    ASSERT_EQ("x^1", fun_1->ToString());
}

TEST(Functions, TestExpString) {
    TFactory fact;
    auto fun_1 = fact.Create("exp", 2);
    ASSERT_EQ("exp(2.000000*x)", fun_1->ToString());
}


TEST(Functions, TestConstString) {
    TFactory fact;
    auto fun_1 = fact.Create("const", 2);
    ASSERT_EQ("2", fun_1->ToString());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}