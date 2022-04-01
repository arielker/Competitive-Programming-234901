#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    explicit unionfind(int size)
    {
        rank=vector<int>(size,1);
        parent=vector<int>(size + 1);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }
        if(rank[p] <= rank[q]) {
            parent[p] = q;
            rank[q] += rank[p];
        }
        else{
            parent[q] = p;
            rank[p] += rank[q];
        }
    }
    int size(int q) {
        return rank[find(q)];
    }
};

int main(){
    int n = 1, q = 1;
    cin >> n >> q;
    unionfind uf(n);
    while (q--) {
        char x;
        cin >> x;
        if('t' == x){
            int a = 1, b = 1;
            cin >> a >> b;
            uf.Union(uf.find(a), uf.find(b));
        } else {
            int a = 1;
            cin >> a;
            cout << uf.size(uf.find(a)) << endl;
        }
    }
    return 0;
}