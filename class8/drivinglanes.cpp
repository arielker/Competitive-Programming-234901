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


int main() {
    int n, m, k, r;
    while (cin >> n >> m >> k >> r) {
        vi straightways, stretches, curves;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            straightways.emplace_back(x);
        }
        for (int i = 0; i < n - 1; ++i) {
            int x, y;
            cin >> x >> y;
            stretches.emplace_back(x);
            curves.emplace_back(y);
        }
        stretches.emplace_back(0);
        curves.emplace_back(0);
        vvi f(n + 1, vi(m + 1, 1e9));
        f[n][1] = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; j < m + 1; ++j) {
                for (int l = 1; l < m + 1; ++l) {
                    if (straightways[i] >= k * abs(j - l)) {
                        int x = f[i + 1][l] + straightways[i] + r * abs(j - l) + stretches[i] + curves[i] * l;
                        if (x < f[i][j]){
                            f[i][j] = x;
                        }
                    }
                }
            }
        }
        cout << f[0][1] << endl;
    }
    return 0;
}
/*
4 3
5 2
10
10
10
10
4 -1
4 -1
4 1
    --- 51

4 3
5 2
10
10
10
10
10 -3
10 -3
10 1
    --- 61
 */