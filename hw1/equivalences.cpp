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
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvi &g, int u, vi &S, vi &colorMap, int color) {
    // DFS on digraph g from node u:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (auto &v: g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
int findSCC(const vvi &g, vi &components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (int i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(), vi());
    for (int u = 0; u < g.size(); u++)
        for (int v: g[u])
            reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    int numSCC = 0;
    for (int i = (int) g.size() - 1; i >= 0; --i)
        if (components[postOrder[i]] == UNSEEN)
            KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
    return numSCC;
}

// Computes the SCC graph of a given digraph.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: strongly connected components graph of g (sccg).
// time: O(V+E).
int findSCCgraph(const vvi &g, vsi &sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u = 0; u < g.size(); u++)
        for (int v: g[u]) // for every edge u->v
            if (component[u] != component[v])
                sccg[component[u]].insert(component[v]);
    return n;
}



int main() {
    int testcases;
    cin >> testcases;
    while (testcases--) {
        int n, m;
        cin >> n >> m;
        vvi graph(n, vi());
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            graph[from - 1].emplace_back(to - 1);
        }
        vsi sccg{};
        int sccs = findSCCgraph(graph, sccg);
        if (1 == sccs){
            cout << "0" << endl;
            return 0;
        }

        vi in_degree(sccs, 0);
        vi out_degree(sccs, 0);
        for (int i = 0; i < sccs; ++i) {
            for (const auto& v: sccg[i]) {
                out_degree[i] = 1;
                in_degree[v] = 1;
            }
        }
        int totalIn = 0, totalOut = 0;
        for (int i = 0; i < sccs; ++i) {
            totalIn += in_degree[i];
            totalOut += out_degree[i];
        }
        int minEdges = max(sccs - totalIn, sccs - totalOut);
        cout << minEdges << endl;
    }
    return 0;
}

/*
2
4 0
3 2
1 2
1 3

    4
    2
 */