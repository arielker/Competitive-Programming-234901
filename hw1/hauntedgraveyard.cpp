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
typedef vector<ll> vll;
typedef set<ll> sll;
typedef pair<int, int> pii;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef set<vii> svii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source node (s).
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle.
// time: O(VE).
bool BellmanFord(const vvii &g, int s, vi &d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight w
        for (int u = 0; u < g.size(); ++u)
            for (ii e: g[u]) {
                int v = e.first;
                int w = e.second;
                // relax the edge
                if (d[u] < INF && d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    changed = true;
                }
            }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}

int w, h, g, e;

int getNodeFromCoords(int x, int y) {
    return x < 0 || y < 0 || x >= w || y >= h ? INF : (x * h) + y;
}

int main() {
    while (cin >> w >> h) {
        if (0 == w && 0 == h) {
            return 0;
        }
        cin >> g;
        int graves[30 * 30] = {0};
        for (int i = 0; i < g; ++i) {
            int x, y;
            cin >> x >> y;
            graves[getNodeFromCoords(x, y)] = 1;
        }
        cin >> e;
        map<int, ii> haunted_holes;
        for (int i = 0; i < e; ++i) {
            int x1, y1, x2, y2, t;
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            int u = getNodeFromCoords(x1, y1);
            int v = getNodeFromCoords(x2, y2);
            haunted_holes[u] = {v, t};
        }
        vvii graph(w * h, vii());
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                if (w - 1 == i && h - 1 == j){
                    continue;
                }
                int u = getNodeFromCoords(i, j);
                if (graves[u]) {
                    continue;
                }
                if (haunted_holes.find(u) != haunted_holes.end()) {
                    vii edge;
                    edge.emplace_back(haunted_holes[u].first,haunted_holes[u].second);
                    graph[u] = edge;
                    continue;
                }
                int neighbors[4] = {0};
                neighbors[0] = getNodeFromCoords(i - 1, j);
                neighbors[1] = getNodeFromCoords(i, j + 1);
                neighbors[2] = getNodeFromCoords(i + 1, j);
                neighbors[3] = getNodeFromCoords(i, j - 1);
                vii edges;
                for (int &neighbor: neighbors) {
                    if (INF == neighbor) {
                        continue;
                    }
                    if (!graves[neighbor]) {
                        edges.emplace_back(neighbor, 1);
                    }
                }
                graph[u] = edges;
            }
        }
        vi times;
        bool result = BellmanFord(graph, 0, times);
        if (result){
            cout << "Never" << endl;
        } else {
            if(*(times.end() - 1) == INF){
                cout << "Impossible" << endl;
            } else {
                cout << *(times.end() - 1) << endl;
            }
        }
    }
    return 0;
}

/*
3 3
2
2 1
1 2
0
4 3
2
2 1
3 1
1
3 0 2 2 0
4 2
0
1
2 0 1 0 -3
0 0

    Impossible
    4
    Never
 */