#include <iostream>
#include <vector>
#include <iostream>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <list>
#include <vector>
#include <future>
#include <sys/mman.h>
#include <sys/stat.h>
#include <atomic>

#include "templates_export.h"

using namespace std;
int main()
{
    Foo<int> f1;    
    Foo<int> f2(Foo<double>());
    Foo<int> f3;
    f3 = Foo<double>();
   // Foo<int> f3 = Foo<int>();
    cout << "\nh   ello fuckers!";
    int i = 0;    
    vector<int> l{1,2,2,2,2,2,2};
    return 0;
}

