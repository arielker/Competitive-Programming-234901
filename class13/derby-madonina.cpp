#include<bits/stdc++.h>

#define int long long
using namespace std;
int const N = 500010;
int n, v, tot, a[N], b[N], s[N];
pair<int, int> p[N];

signed main() {
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        p[i] = make_pair(v * a[i] - b[i], v * a[i] + b[i]);
    }
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++) {
        if (p[i].first < 0 || p[i].second < 0) {
            continue;
        }
        int t = p[i].second;
        if (t >= s[tot]) {
            tot++;
            s[tot] = t;
        } else {
            *upper_bound(s + 1, s + 1 + tot, t) = t;
        }
    }
    cout << tot << endl;
}
