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


int augment(vector<map<int, int>> &res, int s, int t, const vi &p, int minEdge) {
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
ull EdmondsKarp(ull n, vector<iii> &edges, int s, int t, vector<map<int, int>> &res) {
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
    int testcases;
    cin >> testcases;
    while (testcases--) {
        int n, init_location, group, time_to_live, m;
        cin >> n >> init_location >> group >> time_to_live >> m;
        init_location--;
        si medical_places;
        for (int i = 0; i < m; ++i) {
            int x;
            cin >> x;
            medical_places.insert(--x);
        }
        int roads;
        cin >> roads;
        if (0 == roads) {
            cout << (medical_places.find(init_location) == medical_places.end() ? 0 : group) << endl;
            continue;
        }
        vector<vii> weighted_graph(n + 1);
        map<ii, ii> flows;
        for (int i = 0; i < roads; ++i) {
            int a, b, p, t;
            cin >> a >> b >> p >> t;
            auto nodes = make_pair(--a, --b);
            flows[nodes] = make_pair(p, t);
        }
        if (medical_places.find(init_location) != medical_places.end()) {
            cout << group << endl;
            continue;
        }
        int num_vertices = n * (time_to_live + 1) + 2;
        int source = n * (time_to_live + 1), target = n * (time_to_live + 1) + 1;
        vector<iii> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < time_to_live; ++j) {
                edges.emplace_back(INF, make_pair(i + j * n, i + (j + 1) * n));
            }
        }
        for (const auto &i: medical_places) {
            for (int j = 0; j < time_to_live + 1; ++j)
                edges.emplace_back(INF, make_pair(i + j * n, target));
        }
        for (const auto &i: flows) {
            int a = i.first.first, b = i.first.second, p = i.second.first, t = i.second.second;
            for (int j = 0; j < time_to_live + 1; ++j) {
                if (time_to_live < j + t) {
                    break;
                }
                edges.emplace_back(p, make_pair(a + j * n, b + (j + t) * n));
            }
        }
        edges.emplace_back(group, make_pair(source, init_location));
        vector<map<int, int>> res(num_vertices);
        cout << EdmondsKarp(num_vertices, edges, source, target, res) << endl;
    }
    return 0;
}

/*
2
4
3 8 5
2
2
4
5
1 2 1 3
3 2 1 4
3 1 2 1
1 4 1 3
3 4 1 3
4
3 10 5
2
2
4
5
1 2 1 3
3 2 1 4
3 1 2 1
1 4 1 3
3 4 1 3
    --- 8
        9

1
3
1 10 5
1
3
2
1 2 2 1
2 3 100 1
    --- 8
 */