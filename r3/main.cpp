#include <thread>
#include <future>
#include <atomic>
#include <functional>
#include <bits/stdc++.h> 
using namespace std; 

unsigned maxDepth(const string& str)
{
    unsigned result = 0;    
    unsigned current = 0;
    for (auto c : str)
    {
        if (c == '(') current++;
        else if (c == ')') current--;
        result = max(result, current);
    }
    return result;
}

vector<unsigned> match(const string& str, const vector<unsigned>& openPositions)
{
   stack<unsigned> s;
   unordered_map<unsigned, unsigned> cache;
   for (auto it = str.begin(); it != str.end(); ++it)
   {
       if ('(' == *it) s.push(distance(str.begin(), it));
       else if (')' == *it)
       {
           unsigned openIdx = s.top();
           cache.emplace(openIdx, distance(str.begin(), it));
           s.pop();
       }
   }

   vector<unsigned> result;
   result.reserve(openPositions.size());
   for (auto v : openPositions)
       result.emplace_back(cache[v]);
   return result;
}

int main(int argc, char* argv[])
{ 
    int N = 0;
    cout << "\n#" << ++N << " : " << maxDepth("asdasd((asdasd))");
    cout << "\n#" << ++N << " : " << maxDepth("Sometimes (when I nest them (my parentheticals) too much (like this (and this))) they get confusing");
    cout << "\n#" << ++N << " : " << maxDepth("asdasd");
    
    const string str1 = "Sometimes (when I nest them (my parentheticals) too much (like this (and this))) they get confusing";
    auto r = match(str1, {10, 28});
    cout << "\n";
    std::copy(r.begin(), r.end(), ostream_iterator<unsigned>(cout, " ")); 
    return 0;
}
