#include <iostream>
#include <vector>
using namespace std;

template <typename T>
size_t findPos(const vector<T>& d, T target)
{
    size_t lo = 0;
    size_t hi = d.size() - 1;
    size_t m = numeric_limits<size_t>::max();

    while (m && lo <= hi)
    {
        m = (lo + hi + 1) / 2;                            
        if (d[m] == target) return m;
        if (d[m] < target) lo = m + 1;
        if (d[m] > target) hi = m - 1;
    }

    return lo;
}

int main()
{
    int i = 0;
   /* cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 1) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 3) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 5) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 7) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 9) << "\n";*/

    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 0) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 2) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 8) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7,9}, 10) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7}, 10) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7}, 2) << "\n";
    cout << "#" << ++i << " : " << findPos({1,3,5,7}, 6) << "\n";
}