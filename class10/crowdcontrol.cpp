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

struct unionfind {
    vector<int> rank;
    vector<int> parent;

    explicit unionfind(int size) {
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
int Kruskal(vector<iii> &edges, int n, vvi &mst) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e: edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst_cost += e.first;
            mst[e.second.first].emplace_back(e.second.second);
            mst[e.second.second].emplace_back(e.second.first);
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}

void bfs(const vvi &g, int s, vector<int> &d) {
    queue<int> q;
    q.push(s);
    vector<bool> visible(g.size(), false);
    visible[s] = true;
    d.assign(g.size(), INF);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: g[u])
            if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u] + 1;
                q.push(v);
            }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<iii> edges;
        vvii save(n);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            edges.emplace_back(-c, make_pair(a, b));
            save[a].emplace_back(b, i);
            save[b].emplace_back(a, i);
        }
        vvi mst(n, vi());
        Kruskal(edges, n, mst);
        vi d;
        bfs(mst, 0, d);

        si nodes_in_path;
        nodes_in_path.insert(0);
        int last_node = n - 1;
        while (last_node != 0) {
            nodes_in_path.insert(last_node);
            for (int i = 0; i < mst[last_node].size(); ++i) {
                ///lemma from Algo1 - retrieving path from 0 to n-1
                if (d[last_node] == 1 + d[mst[last_node][i]]) {
                    last_node = mst[last_node][i];
                    break;
                }
            }
        }

        si ret;
        for (const auto &v: nodes_in_path) {
            for (const auto &i: save[v]) {
                auto node = i.first;
                auto e = i.second;
                if (nodes_in_path.find(node) == nodes_in_path.end()) {
                    ret.insert(e);
                }
                if (abs(d[v] - d[node]) != 1) {
                    ret.insert(e);
                }
            }
        }
        if (ret.empty()) {
            cout << "none" << endl;
            continue;
        }
        for (const auto &item: ret) {
            cout << item << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
7 10
0 1 800
1 2 300
2 3 75
3 4 80
4 5 50
4 6 100
6 1 35
0 6 10
0 2 120
0 3 100
    --- 0 2 4 6 7 8

4 4
0 1 10
1 2 50
0 3 30
1 3 20
    --- 0 3

4 3
0 1 10
1 2 20
2 3 30
    --- none
 */