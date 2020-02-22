#include <iostream>
#include <atomic>
using namespace std;
//std::atomic_load
struct TestAtomic
{
    int * p1;
    //int p;
    int * p2;
};

int main()
{
    auto v = std::atomic<TestAtomic>{}.is_lock_free();
    cout << "\n" << v << "\n";
    return 0;
}
