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

const int INF = 1e9;
const int MAX = 32768;

void bfs(int s, vi &d) {
    queue<int> q;
    q.push(s);
    vector<bool> visible(MAX, false);
    visible[s] = true;
    d.assign(MAX, INF);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int n1 = (u * 2) % MAX;
        int n2 = (u + 1) % MAX;
        if (!visible[n1]) {
            q.push(n1);
            d[n1] = d[u] + 1;
            visible[n1] = true;
        }
        if (!visible[n2]) {
            q.push(n2);
            d[n2] = d[u] + 1;
            visible[n2] = true;
        }
        if (!n1 || !n2) {
            return;
        }
    }
}


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vi d;
        bfs(x, d);
        cout << d[0] << " ";
    }
    cout << endl;
    return 0;
}

/*
4
19 32764 10240 49

    14 4 4 15
 */