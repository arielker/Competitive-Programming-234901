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
int EdmondsKarp(int n, vector<iii> &edges, int s, int t, vvi &res) {
    // initialise adjacency list and residuals adjacency matrix
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
    int n, m, s, t;
    while (cin >> n >> m >> s >> t) {
        vector<iii> g;
        map<ii, int> save; //to save graph
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            g.emplace_back(c, make_pair(u, v));
            save[make_pair(u, v)] = c;
        }
        vvi res(n, vi(n, 0));
        int f = EdmondsKarp(n, g, s, t, res);
        int edges_flow = 0, a = res.size();
        set<iii> ret;
        for (int i = 0; i < a; ++i) {
            int b = res[i].size();
            for (int j = 0; j < b; ++j) {
                ii nodes = make_pair(i, j);
                if (save.end() == save.find(nodes)) {
                    continue;
                }
                if (0 < (save[nodes] - res[i][j])) {
                    ///was taken to the flow!!
                    ret.insert(make_pair(save[nodes] - res[i][j], nodes));
                    edges_flow++;
                }
            }
        }
        cout << n << " " << f << " " << edges_flow << endl;
        for (const auto &item: ret) {
            cout << item.second.first << " "
                 << item.second.second << " "
                 << item.first
                 << endl;
        }
    }
    return 0;
}
/*
4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10
    4 3 5
    0 1 2
    0 2 1
    1 2 1
    1 3 1
    2 3 2

2 1 0 1
0 1 100000
    2 100000 1
    0 1 100000

2 1 1 0
0 1 100000
    2 0 0
 */