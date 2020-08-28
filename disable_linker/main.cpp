#include <bits/stdc++.h>
#include "dynamic.h"
#include "static.h"
using namespace std;

#include "A.h"
extern void f();

int main()
{
    int64_t address = reinterpret_cast<int64_t>(g_str.c_str());
    cout << "\n" << g_str.c_str() << ", address=" << address << "g_str::i" << g_str.i << " , g_str2::i=" << g_str2.i;
    f();
    (void)g_str3.c_str();
    cout << "\ng_s" << g_s.c_str();
    cout << "\ng_s=" << globalGetter().c_str();
    return 0;
}
