#include <cmath>
#include <pmmintrin.h>

using float_simd = __m128;
using double_simd = __m128d;

float_simd sqrt(float_simd a) { return _mm_sqrt_ps(a); }
double_simd sqrt(double_simd a) { return _mm_sqrt_pd(a); }

template <typename T>
void do_fancy(T val) 
{
    using std::sqrt;
    auto ret = sqrt(val);
    (void)ret;
}

int main() {
    double testDouble = 1.0; 
    float testFloat = 1.0f;
    double_simd testSimdDouble;
    float_simd testSimdFloat;
    do_fancy(testDouble);
    do_fancy(testFloat);
    do_fancy(testSimdDouble);
    do_fancy(testSimdFloat);
    return 0;
}