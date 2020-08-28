#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

bool g(double l, double r) {
    return (l-r) > 1e-6;
}

int main()
{
    const auto f1=1.10;
    auto f2=2/f1;
    cout << "\n f2=" << f2 << " same=" << is_same<double,decay<decltype(f1)>::type>::value;
    double zero = 0.0;
    if (zero < DBL_MIN/2) {
        cout << "\n greater 1";
    }
    if (g(DBL_MIN/2,zero)) {
         cout << "\n greater 2";
    }
    return 0;
}