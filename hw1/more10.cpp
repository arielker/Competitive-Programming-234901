///------------------------------------
///  Marten's theorem
///------------------------------------

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
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

constexpr int MAX = 100000 * 4 + 2;

int place = 0;

map<string, int> words;

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
};

int insert(const string& s){
    if(words.find(s) == words.end()){
        words[s] = place++;
        return (place - 1);
    }
    return words[s];
}

int main() {
    int N;
    cin >> N;
    vector<pii> negs;
    set<string> all;
    unionfind constraints(MAX);
    string lw, rule, rw;

    while(N--){
        cin >> lw >> rule >> rw;
        int i = insert(lw), j = insert(rw);
        if("is" == rule){
            constraints.Union(i,j);
        } else {
            negs.emplace_back(i,j);
        }
        all.insert(lw);
        all.insert(rw);
    }

    for(const auto& s: all){
        int ix = words[s], iex = 0;
        string ex;
        if(2 == s.size()){
            ex = s.substr(s.size() - 1);
            if(all.find(ex) != all.end()){
                constraints.Union(ix, words[ex]);
            }
        } else if(3 <= s.size()){
            ex = s.substr(s.size() - 3);
            iex = insert(ex);
            constraints.Union(ix, iex);

            ex = s.substr(s.size() - 2);
            if(all.find(ex) != all.end()){
                constraints.Union(ix, words[ex]);
            }

            ex = s.substr(s.size() - 1);
            if(all.find(ex) != all.end()){
                constraints.Union(ix, words[ex]);
            }
        }
    }
    for (const auto& p: negs){
        if(constraints.find(p.first) == constraints.find(p.second)){
            cout << "wait what?" << endl;
            return 0;
        }
    }
    cout << "yes" << endl;
    return 0;
}