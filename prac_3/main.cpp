#include <iostream>
#include <vector>
#include "Factory.hpp"
// #include "NewOperators.h"
// #include "Root.h"

using namespace std;

int main() {

    std::vector<shared_ptr<TFunction>> cont;
    auto factory = TFactory();
    auto f = factory.Create("power", 2);
    std::cout << f->Deriative(1) << std::endl;
    cont.push_back(f);
    auto g = factory.Create("polynomial", {7, 0, 3, 15});
    std::cout << g->Deriative(1);
    cont.push_back(g);
    for (const auto ptr : cont) {
        std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
    }

    auto p = *f + *g;
    std::cout << p.ToString() << std::endl;
    std::cout << p.Deriative(1) << std::endl;
}
