#include <bits/stdc++.h>
using namespace std;



int main()
{
    int r[]{0,1,2};
    std::vector<int> v(r,r+sizeof(r)/4);
    cout << v.size() << " last=" << v.back();
    return 0;
}