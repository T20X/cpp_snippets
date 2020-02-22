#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
    int N = 0;
    vector<int> data_;
    vector<int> heap_;    
    vector<int> m_;

    SegmentTree(const vector<int>& data)
      :N(data.size()),  data_(data), heap_(4*N + 1, -1), m_(N, -1)
    {
        build(1, 0, N - 1);
    }

    int left(int parent) { return parent << 1; }
    int right(int parent) { return left(parent) + 1; }

    void build(int parent, int L, int R)
    {
        
           if (L == R)
           {
               heap_[parent] = data_[L];
               m_[L] = parent;
           }
           else
           {
               build(left(parent), L, (L + R) / 2);
               build(right(parent), (L + R) / 2 + 1, R);
               heap_[parent] = heap_[left(parent)] + 
                               heap_[right(parent)];
           }

           cout << "\n build" << " p=" << parent << ", L=" << L << ", R=" << R << ", sum=" << heap_[parent];
    }

    void update(int i, int v)
    {
        int heapIdx = m_[i];
        int prevValue = data_[i];
        data_[heapIdx] = v;
        rebalance(heapIdx, v - prevValue);
    }   

    void rebalance(int p, int delta)
    {
        if (p < 1 || !delta)
         return;

        heap_[p] += delta;
        rebalance(p / 2, delta);
    } 

    int trq(int L, int R)
    {
        return doTrq(1, 0, N - 1, L, R);
    }

    int doTrq(int parent, int limitL, int limitR, int L, int R)
    {
        cout << "\n trq(1) p=" << parent << ", limitL=" << limitL
             << ", limitR=" << limitR << ", L=" << L << ", R=" << R;

       
        if (L > limitR || R < limitL || R > limitR || L < limitL)
         return -1;  

       int sum = -1;
       if (limitL == L && limitR == R)
          sum = heap_[parent];       
        else
        {
           auto newLimitR = (limitL + limitR ) / 2;
           auto newLimitL = newLimitR + 1;

           auto lsum = doTrq(left(parent), limitL, newLimitR, L, min(newLimitR, R));
           auto rsum = doTrq(right(parent), newLimitL, limitR, max(newLimitL, L), R);

                if (lsum == -1) sum = rsum;           
           else if (rsum == -1) sum = lsum;           
           else sum = rsum + lsum;           
        }

        cout << "\n trq(2) p=" << parent << ", limitL=" << limitL
             << ", limitR=" << limitR << ", L=" << L << ", R=" << R << ", sum=" << sum;
        return sum;
    }

    void dumpMapping()
    {
         cout << "\n******MAPING*******\n";
        copy(m_.begin(), m_.end(), ostream_iterator<int>(cout, ","));
    }

    void dump()
    {
        cout << "\n*************";
        queue<int> q;
        q.emplace(1);        
        while (!q.empty())
        {
            list<int> level;
            while (!q.empty())
            {
                auto v = q.front();
                level.emplace_back(v);
                q.pop();
            }

            cout << "\n*************";
            for (auto v : level)
            {
                cout << " | p=" << v << ", sum=" << heap_[v] << " ***** ";
                if (heap_[v] != -1)
                {
                    assert(v < heap_.size());
                    auto l = 2*v;
                    auto r = l + 1;
                    if (l < heap_.size()) q.emplace(l);
                    if (r < heap_.size()) q.emplace(r);
                }
            }
        }
    }

    void dumpRaw()
    {
        cout << "\n*************";
        copy(heap_.begin(), heap_.end(), ostream_iterator<int>(cout," | "));
    }
};

int main()
{
     {
        vector<int> v = {2,3,7,1,8,10};
        SegmentTree t(v);
        t.dumpRaw();
        t.dump();
        assert(t.trq(0,5) == 31);
        assert(t.trq(0,3) == 13);
        assert(t.trq(0,4) == 21);
        assert(t.trq(2,4) == 16);
        t.dumpMapping();
        t.update(2, 9);
        assert(t.trq(2,4) == 18);
        assert(t.trq(0,5) == 33);

    }
    {
        vector<int> v = {2,3};
        SegmentTree t(v);
        t.dumpRaw();
        t.dump();
        assert(t.trq(0,1) == 5);
        assert(t.trq(0,2) == -1);
    }
    return 0;
}