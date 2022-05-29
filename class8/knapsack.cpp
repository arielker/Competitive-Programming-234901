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
    int c, n;
    while (cin >> c >> n) {
        vvi f(n + 1, vi(c + 1, 0));
        vi w(n + 1, 0), v(n + 1, 0);
        for (int i = 1; i < n + 1; ++i) {
            cin >> v[i] >> w[i];
        }
        for (int i = 1; i < n + 1; ++i) {
            for (int j = 1; j < c + 1; ++j) {
                f[i][j] = w[i] > j ? f[i - 1][j] : max(f[i - 1][j], v[i] + f[i - 1][j - w[i]]);
            }
        }
        int sol = f[n][c], save = c, i = n;
        vi solution;
        while (sol > 0 && i > 0) {
            if (f[i - 1][save] != sol) {
                solution.emplace_back(i);
                sol -= v[i];
                save -= w[i];
            }
            i--;
        }
        cout << solution.size() << endl;
        for (const auto &item: solution){
            cout << item - 1 << " ";
        }
        cout << endl;
    }
    return 0;
}

/*
5 3
1 5
10 5
100 5
6 4
5 4
4 3
3 2
2 1
    ---
        1
        2
        3
        1 2 3

 */