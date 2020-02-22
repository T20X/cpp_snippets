#include <bits/stdc++.h>
using namespace std;

struct uf
{
    vector<int> _data;
    vector<int> _sz;
    
    uf(int N):_sz(N,1)
    {
        _data.reserve(N);
        for (int i = 0; i < N; i++)
          _data.emplace_back(i);
    }

    bool f(int l, int r)
    {
        return root(l) == root(r);        
    }

    int root(int v)
    {
        while (v != _data[v])
          v = _data[_data[v]];
        return v;
    }

    void un(int l, int r)
    {
        int lR = _data[root(l)];
        int rR = _data[root(r)];
        if (lR == rR)
           return;

        int lSz = _sz[lR];
        int rSz = _sz[rR];
        if (lSz >= rSz)
        { 
            _data[rR] = lR; 
            _sz[lR] += rSz;            
        }        
        else
        {
            _data[lR] = rR; 
            _sz[rR] += lSz;
        }
    }
    
    void dumpRaw(ostream& out)
    {
        cout << "\n ------------- \n";
        cout << "Data="; copy(_data.begin(), _data.end(), ostream_iterator<int>(out, ","));       
        cout << "\n Sz="; copy(_sz.begin(), _sz.end(), ostream_iterator<int>(out, ","));     
    }

    void dumpGroups(ostream& out)
    {
        cout << "\n ------------- \n";

        unordered_map<int, vector<int>> r;
        vector<int> tmp(_data);

        int next = 0;
        int i = 0;
        while (i<tmp.size())
        {
            r[root(i)].emplace_back(i++);
        }

        for (const auto& v : r)
        {
            cout << "\n" << "idx=" << v.first << ", sz=" << _sz[v.first] << " : ";            
            assert(_sz[v.first] == v.second.size());
            copy(cbegin(v.second), cend(v.second), ostream_iterator<int>(out, ","));
        }        
    }

};

int main()
{
    uf o1(10);
     o1.dumpGroups(cout);
    assert(o1.f(1,1));
    assert(o1.f(0,0));
    assert(!o1.f(1,3));

    o1.un(1,0);
    o1.un(0,1);
    o1.un(0,3);
     o1.dumpGroups(cout);
     o1.dumpRaw(cout);

    o1.un(4,5);
    o1.un(4,0);
    o1.un(2,3);
     o1.dumpGroups(cout);
     o1.dumpRaw(cout);


    assert(o1.f(0,1));
    assert(o1.f(1,0));
    assert(o1.f(1,3));
    assert(o1.f(0,3));
    assert(o1.f(3,1));
     o1.dumpGroups(cout);
     o1.dumpRaw(cout);

    o1.un(7,9);
    o1.un(8,7);
    o1.un(0,9);
    assert(o1.f(1,7));
    assert(o1.f(4,9));
     o1.dumpGroups(cout);
     o1.dumpRaw(cout);

    return 0;
}