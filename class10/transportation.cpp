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
    int s, r, f, t, source = 0, target = 1;
    while (cin >> s >> r >> f >> t) {
        int node_id = 2;
        vector<iii> edges;
        map<string, int> state_to_ids;
        for (int i = 0; i < r; ++i) {
            string a;
            cin >> a;
            state_to_ids[a] = node_id;
            edges.emplace_back(1, make_pair(source, node_id));
            node_id++;
        }
        for (int i = 0; i < f; ++i) {
            string a;
            cin >> a;
            state_to_ids[a] = node_id;
            edges.emplace_back(1, make_pair(node_id, target));
            node_id++;
        }
        for (int i = 0; i < t; ++i) {
            int n;
            cin >> n;
            int to_id = node_id++, from_id = node_id++;
            edges.emplace_back(1, make_pair(to_id, from_id));
            for (int j = 0; j < n; ++j) {
                string a;
                cin >> a;
                if (state_to_ids.find(a) == state_to_ids.end()) {
                    state_to_ids[a] = node_id++;
                }
                edges.emplace_back(1, make_pair(state_to_ids[a], to_id));
                edges.emplace_back(1, make_pair(from_id, state_to_ids[a]));
            }
        }
        cout << EdmondsKarp(node_id, edges, source, target) << endl;
    }
    return 0;
}

/*
7 3 3 3
A B C
D E F
3 A E G
3 A C E
3 B D F
    --- 2

7 3 3 4
A B C
D E F
3 A E G
3 A C E
3 B D F
2 G F
    --- 3
 */
