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
#include <iomanip>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vd> vvd;
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

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1).
// output: the pairwise distances (d).
// time: O(V^3).
void FloydWarshall(const vvii &g, vvi &d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (int u = 0; u < g.size(); ++u) d[u][u] = 0;
    for (int u = 0; u < g.size(); ++u)
        for (ii e: g[u]) {
            int v = e.first;
            int w = e.second;
            d[u][v] = min(d[u][v], w);
        }
    // relax distances using the Floyd-Warshall algorithm
    for (int k = 0; k < g.size(); ++k)
        for (int u = 0; u < g.size(); ++u)
            for (int v = 0; v < g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
}

int n, r;

void calculate(vvd &dp);

int main() {
    int t;
    cin >> t;
    for (int k = 0; k < t; ++k) {
        cout << "Case " << k + 1 << endl;
        cin >> n >> r;
        vvii g(n, vii());
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < n; ++j) {
                if ('Y' == s[j]) {
                    g[i].emplace_back(j, 1);
                }
            }
        }

        vvi d(n, vi(n, 0));
        FloydWarshall(g, d);
        vvd dp(100 + 1, vd(10000 + 1, 0));
        dp[0][0] = 1.0;
        calculate(dp);

        int c;
        cin >> c;
        for (int i = 0; i < c; ++i) {
            int a, b, m;
            cin >> a >> b >> m;
            int dist = d[a - 1][b - 1];
            double p = accumulate(dp[dist].begin(), dp[dist].begin() + m + 1,0.0);
            cout << fixed << setprecision(10) << p << endl;
        }
        cout << endl;
    }
    return 0;
}

void calculate(vvd &dp) {
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < r + 1; ++j) {
            for (int k = j; k < n * r + 1; ++k) {
                ///double is necessary, otherwise nasty 'floor bug' appears
                dp[i][k] += (double(dp[i - 1][k - j]) / double(r));
            }
        }
    }
}

/*
Sample Input
2
3 4
NYY
YNY
YYN
1
1 3 1
4 7
NYNN
YNYN
NYNY
NNYN
2
1 3 10
1 4 10

Sample Output
    Case 1
    0.250000
    Case 2
    0.795918
    0.341108
 */