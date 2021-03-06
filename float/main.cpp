#include <bits/stdc++.h>
#include <fenv.h>
#include <list>
#include <utils.h>
#include <assert.h>
#include <vector>


int main()
{
    std::vector<int> v1;
    v1.clear();
    using namespace std;
    auto dec = 0.2/1.0;
    std::cout <<  std::setprecision(20) ;
    std::cout << "\n default decimal type is = " << utils::typeName<decltype(dec)>() << "\n";
    float dec2 = dec;
    std::cout << "\n bits of dec = " << utils::printBits(dec) ;
    std::cout << "\n bits of dec2 = " << utils::printBits(dec2) << "\n";
    std::cout << "\n bits of 1 " << utils::printBits(1) << "\n";
    std::cout << "\n Next after 1.1=" << std::nextafter(1.1, 1.5);
    std::cout << "\n Next after 10000000000.1=" << 10000000000.1- std::nextafter(10000000000.1, 1.5);
    //assert(dec2 == dec);
    
    //feenableexcept(FE_ALL_EXCEPT);
    //fedisableexcept(FE_DIVBYZERO);
    //feenableexcept(FE_DIVBYZERO);
    //
    double one = 1.0;
   try {
   double f1=10.0/0.0;
    if(std::fetestexcept(FE_DIVBYZERO)) {
        std::cout << "division by zero reported , f1=" << f1 << "\n";
    } else {
        std::cout << "divsion by zero not reported\n";
    }
   }
   catch (...) {
       cout << "\n e=";
   }

   try {
    std::feclearexcept(FE_ALL_EXCEPT);
    double ret=one/10.0;
    std::cout << "1.0/10 = " << ret << '\n';
    if(std::fetestexcept(FE_INEXACT)) {
        std::cout << "inexact result reported\n";
    } else {
        std::cout << "inexact result not reported\n";
    }
   } 
   catch (...) {
       cout << "\n e=";
   }
   std::feclearexcept(FE_ALL_EXCEPT);
   {
    double ret=one*10.0;
    if(std::fetestexcept(FE_INEXACT)) {
        std::cout << "(2) inexact result reported\n";
    } else {
        std::cout << "(2) inexact result not reported\n";
    } 
   }

try {
    throw std::runtime_error("asdf");
} catch (const std::exception& e) {
    //std::string("asdf") << e.what();
}
   cout << "\n round mode=" << fegetround(); 
   cout << "\n def rounding 12.5 = " << std::nearbyint(12.5);
   std::fesetround(FE_TONEAREST);
   cout << "\n round mode=" << fegetround(); 
   cout << "\n FE_TONEAREST rounding 12.5 = " << std::nearbyint(12.5);
   std::fesetround(FE_UPWARD);
   cout << "\n round mode=" << fegetround(); 
   cout << "\n FE_UPWARD rounding 12.5 = " << std::nearbyint(12.5);
   std::fesetround(FE_TOWARDZERO);
   cout << "\n round mode=" << fegetround(); 
   cout << "\n FE_TOWARDZERO rounding 12.5 = " << std::nearbyint(12.5); 
   return 0;
}
