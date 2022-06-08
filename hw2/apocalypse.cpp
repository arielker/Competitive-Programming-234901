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
#include <limits>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<ll> sll;
typedef pair<int, int> pii;
typedef pair<int, int> ii;
typedef pair<double, double> pdd;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;
#define EPS 1e-9

/********** Min Spanning Tree **********/


struct unionfind {
    vector<int> rank;
    vector<int> parent;

    unionfind(int size) {
        rank = vector<int>(size, 0);
        parent = vector<int>(size);
        for (int i = 0; i < size; i++) parent[i] = i;
    }

    int find(int x) {
        int tmp = x;
        while (x != parent[x]) x = parent[x];
        while (tmp != x) {
            int remember = parent[tmp];
            parent[tmp] = x;
            tmp = remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if (q == p) return;
        if (rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if (rank[p] == rank[q]) rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii> &edges, int n) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e: edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}


/********** Max Flow **********/


int augment(vvi &res, int s, int t, const vi &p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp(int n, vector<iii> &edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n, vi(n, 0));
    vvi adj(n);
    for (iii e: edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (int v: adj[u])
                if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}

int main() {

    return 0;
}