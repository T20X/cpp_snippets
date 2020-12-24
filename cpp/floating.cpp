#include "utils.h"
#include <iostream>
#include <cmath>
#include <cfloat>
#include <vector>
#include <cfenv>

using namespace std;

bool g(double l, double r) {
    return (l-r) > 1e-6;
}

int main()
{
    std::vector<int> v;
    const auto f1=1.10;
    auto f2=2/f1;
    cout << "\n f2=" << f2 << " same=" << is_same<double,decay<decltype(f1)>::type>::value;
    double zero = 1000000000.0;
    std::cout << "\n" << utils::printBits(127);
    std::cout << "\n" << utils::printBits(255);
    std::cout << "\n" << utils::printBits(zero);
    std::cout << "\n" << utils::printBits(std::numeric_limits<double>::signaling_NaN());
    std::cout << "\n" << " round 1.2=" << std::round(1.2);
    std::cout << "\n" << " round 1.5=" << std::round(1.5);
    std::cout << "\n" << " round 3.5=" << std::round(3.5);

    std::cout << "\n" << " ----------------------------- ";
    std::cout << "\n" << fegetround();
    std::cout << "\n" << " ----------------------------- ";
    #pragma STDC FENV_ACCESS ON
    std::fesetround(FE_TONEAREST);
    std::cout << "\n rounding using std::round" ;
    std::cout << "\n round(2.5)" << std::round(2.5);
    std::cout << "\n rounding to nearest (halfway cases to even):\n"
              << "rint(+2.3) = " << std::rint(2.3)
              << "  rint(+2.5) = " << std::rint(2.5)
              << "  rint(+2.5) = " << std::rint(2.5)
              << "  rint(+3.5) = " << std::rint(3.5) << '\n'
              << "  rint(+3.5) = " << std::rint(3.5) << '\n'
              << "  rint(+3.5) = " << std::rint(3.5) << '\n'
              << "rint(-2.3) = " << std::rint(-2.3)
              << "  rint(-2.5) = " << std::rint(-2.5)
              << "  rint(-3.5) = " << std::rint(-3.5) << '\n';

    if (zero < DBL_MIN/2) {
        cout << "\n greater 1";
    }


    if (g(DBL_MIN/2,zero)) {
         cout << "\n greater 2";
    }
    return 0;
}