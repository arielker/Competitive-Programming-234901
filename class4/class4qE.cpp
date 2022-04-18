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

/**
 * r - is the number of different ingredients that exist
 * s,m,d - are the number of available starter dishes, main dishes, and desserts, respectively
 * n - the number of pairs of dishes that do not go well together.
 */
int r, s, m, d, n;

static inline bool find(set<pii> set, ll a, ll b) {
    return set.find({a, b}) != set.end() || set.find({b, a}) != set.end();
}

int main() {
    cin >> r >> s >> m >> d >> n;
    vi brands(r + 1);
    brands[0] = 0;
    for (int i = 1; i <= r; ++i) {
        cin >> brands[i];
    }
    ull MAX = pow(10,18);
    ull res = 1;
    vector<vector<ll>> starters(s + 1);
    vector<vector<ll>> mains(m + 1);
    vector<vector<ll>> deserts(d + 1);
    set<pii> bad;
    ///input of starters
    for (int i = 1; i <= s; ++i) {
        int k;
        cin >> k;
//        starters[i].insert(k);
        for (int j = 1; j <= k; ++j) {
            int f;
            cin >> f;
            starters[i].emplace_back(f);
        }
    }
    ///input of main dishes
    for (int i = 1; i <= m; ++i) {
        int k;
        cin >> k;
//        mains[i][0] = k;
        for (int j = 1; j <= k; ++j) {
            int f;
            cin >> f;
            mains[i].emplace_back(f);
        }
    }
    ///input of deserts
    for (int i = 1; i <= d; ++i) {
        ll k;
        cin >> k;
//        deserts[i][0] = k;
        for (int j = 1; j <= k; ++j) {
            ll f;
            cin >> f;
            deserts[i].emplace_back(f);
        }
    }
    ///input of bad pairs
    for (int i = 0; i < n; ++i) {
        ll f, se;
        cin >> f >> se;
        bad.insert({f, se});
    }
    for (ll i = 1; i <= s; ++i) {
        for (ll j = 1; j <= m; ++j) {
            for (ll k = 1; k <= d; ++k) {
                if (find(bad, i, s + j) ||
                    find(bad, i, s + m + k) ||
                    find(bad, s + j, s + m + k)) {
                    continue;
                }
                ull temp = 1;
                set<ll> ingredients;
                ingredients.insert(starters[i].begin(), starters[i].end());
                ingredients.insert(mains[j].begin(), mains[j].end());
                ingredients.insert(deserts[k].begin(), deserts[k].end());
                for (const auto &in: ingredients) {
                    temp *= brands[in];
                    if(temp > MAX){
                        cout << "too many" << endl;
                        return 0;
                    }
                }
                res += temp;
                if (res - 1 > MAX){
                    cout << "too many" << endl;
                    return 0;
                }
            }
        }
    }
    if (res - 1 > MAX) {
        cout << "too many" << endl;
    } else {
        cout << res - 1 << endl;
    }
    return 0;
}