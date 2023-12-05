#include <iostream>
#include <vector>
#include "Factory.hpp"
// #include "NewOperators.h"
// #include "Root.h"

using namespace std;

int main() {
//     vector<double> v{0, 1};
//     vector<double> u{1, 0, 1};

//     vector<double> t = {1, -2, 1};
//     vector<double> t1 = {0, 0, 1};
//     vector<double> t2 = {0, 0,0,0,1};
//     vector<double> t3 = {0, 0, 0, 1};
//     vector<double> t4 = {3};
//     vector<double> t5 = {0, 0, 3};

//     auto factory = TFactory();
//     auto a = factory.Create("exp", -1.23);
//     auto b = factory.Create("polynomial", v);
//     auto c = factory.Create("polynomial", u);

//     auto d = factory.Create("polynomial", {1, -2, 1});

//     auto d1 = factory.Create("polynomial", t1);
//     auto d2 = factory.Create("polynomial", t2);
//     auto d3 = factory.Create("polynomial", t3);
//     auto d4 = factory.Create("power", t4);
//     auto d5 = factory.Create("polynomial", t5);
//    //  std::cout << std::is_base_of_v<TFunction, BaseArithmetic>;
//    //  d1+d2+d3;
//    //  return 0;
//    std::cout << c -> ToString() << "     "  << std::endl;

//    std::cout <<  getRoot(d, 10, 0.1, 220) << std::endl;
//    std::cout <<(d1 / d2) -> GetDerivativeAtPoint(1) << std::endl;
//    std::cout << ((d1 / d2)->copy() / d1) -> GetDerivativeAtPoint(1) << std::endl;
//    std::cout << getRoot(d3, 5, 0.1, 220) << std::endl;
//    std::cout << getRoot(d5-d4, 5, 0.1, 220) << std::endl;
//    std::cout << "END OF NEEDED RESULTS" << std::endl;

//     cout << c -> ToString() << "     " << c->GetDerivativeAtPoint(2) << endl
//          << a -> ToString() << "     " << a->GetDerivativeAtPoint(1) << endl << (c / a) -> GetDerivativeAtPoint(0) << endl;

    std::vector<shared_ptr<TFunction>> cont;
    auto factory = TFactory();
    auto f = factory.Create("power", 2);
    std::cout << f->Deriative(1) << std::endl;
    cont.push_back(f);
    auto g = factory.Create("polynomial", {7, 0, 3, 15});
    // 7 + 6x + 45x^2
    std::cout << g->Deriative(1);
    // cont.push_back(g);
    // for (const auto ptr : cont) {
    //     std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
    // }

    auto p = *f + *g;
    std::cout << p.ToString() << std::endl;
    std::cout << p.Deriative(1) << std::endl;
    // auto h = *f + "abc";
}
