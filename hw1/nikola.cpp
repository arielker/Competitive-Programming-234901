///------------------------------------
///  Nikola
///------------------------------------

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
typedef pair<int, int> pii;

constexpr int WORST = 500 * 1000;

int main() {
    int N;
    cin >> N;
    vi fees(N);
    for (int &fee: fees) {
        cin >> fee;
    }

    /// square -> (jump size -> fee)
    vector<vi> dist(N, vi(N + 1, WORST));

    /// logarithmic insertion and extraction
    /// (current paid fee, (square, jump size))
    priority_queue<pair<int, pii>> q;
    q.push(make_pair(0, make_pair(1, 1)));

    ///base cases
    dist[0][0] = 0;
    dist[1][1] = fees[1];

    ///starting to compute DP function
    while (!q.empty()) {
        ///square
        int c = q.top().second.first;
        ///jump size
        int t = q.top().second.second;
        q.pop();

        ///reached final square
        if (N - 1 == c) {
            cout << dist[c][t] << endl;
            return 0;
        }

        ///going backwards to square c - t
        int next = c - t;
        if (next >= 0 && WORST == dist[next][t]) {
            dist[next][t] = dist[c][t] + fees[next];
            q.push(make_pair(-dist[next][t], make_pair(next, t)));
        }

        ///going forward to square c + (t + 1)
        next = c + t + 1;
        if (next < N && WORST == dist[next][t + 1]) {
            dist[next][t + 1] = dist[c][t] + fees[next];
            q.push(make_pair(-dist[next][t + 1], make_pair(next, t + 1)));
        }
    }

    return 0;
}

/*
6
1
2
3
4
5
6

 -- 12
8
2
3
4
3
1
6
1
4

 -- 14
 */