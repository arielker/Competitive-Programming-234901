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

int main() {
    //file();
    //fast();
    int n, m;
    cin >> n >> m;

    vector<vector<char>> v;
    v.resize(n, vector<char>(m));

    for (auto &i: v) {
        for (auto &j: i) {
            cin >> j;
        }
    }

    string s;
    cin >> s;
    s += "*";

    vector<vector<vector<int>>> vis;
    vis.resize(n, vector<vector<int>>(m, vector<int>(s.size() + 1, INF)));

    queue<tuple<int, int, int>> q;
    vis[0][0][0] = 0;
    q.push({0, 0, 0});

    int dist = INF;
    while (!q.empty()) {
        int x, y, l;
        tie(x, y, l) = q.front();
        q.pop();

        if (l == s.length()) {
            dist = vis[x][y][l];
            break;
        }

        if (v[x][y] == s[l]) {
            if (vis[x][y][l + 1] > vis[x][y][l] + 1) {
                vis[x][y][l + 1] = vis[x][y][l] + 1;
                q.push({x, y, l + 1});
            }
        }

        int nextx, nexty;

        nextx = x;
        while (true) {
            nextx--;
            if (nextx < 0) {
                break;
            }

            if (v[x][y] != v[nextx][y]) {
                if (vis[nextx][y][l] > vis[x][y][l] + 1) {
                    vis[nextx][y][l] = vis[x][y][l] + 1;
                    q.push({nextx, y, l});
                }
                break;
            }
        }

        nextx = x;
        while (true) {
            nextx++;
            if (nextx >= n) {
                break;
            }

            if (v[x][y] != v[nextx][y]) {
                if (vis[nextx][y][l] > vis[x][y][l] + 1) {
                    vis[nextx][y][l] = vis[x][y][l] + 1;
                    q.push({nextx, y, l});
                }
                break;
            }
        }

        nexty = y;
        while (true) {
            nexty--;
            if (nexty < 0) {
                break;
            }

            if (v[x][y] != v[x][nexty]) {
                if (vis[x][nexty][l] > vis[x][y][l] + 1) {
                    vis[x][nexty][l] = vis[x][y][l] + 1;
                    q.push({x, nexty, l});
                }
                break;
            }
        }

        nexty = y;
        while (true) {
            nexty++;
            if (nexty >= m) {
                break;
            }

            if (v[x][y] != v[x][nexty]) {
                if (vis[x][nexty][l] > vis[x][y][l] + 1) {
                    vis[x][nexty][l] = vis[x][y][l] + 1;
                    q.push({x, nexty, l});
                }
                break;
            }
        }
    }

    cout << dist << endl;

    return 0;
}