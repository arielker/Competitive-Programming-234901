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

/**
 * r - is the number of different ingredients that exist
 * s,m,d - are the number of available starter dishes, main dishes, and desserts, respectively
 * n - the number of pairs of dishes that do not go well together.
 */

static inline bool find(set<pair<ll, ll>> set, ll a, ll b) {
    return set.find({a, b}) != set.end();
}

int main() {
    ll r, s, m, d, n, i, j, k, current, f, sec;
    bool check = true;
    ull MAX = 1e18;

    while (cin >> r >> s >> m >> d >> n) {
        ull res = 1;
        vll brands(r + 1);
        vector<sll> food(s + m + d + 1);
        set<pair<ll, ll>> bad;

        for (i = 1; i <= r; ++i) {
            cin >> brands[i];
        }

        for (i = 1; i <= s + m + d; ++i) {
            cin >> k;
            for (j = 1; j <= k; ++j) {
                cin >> current;
                food[i].insert(current);
            }
        }

        for (i = 1; i <= n; i++) {
            cin >> f >> sec;
            bad.insert({f < sec ? f : sec, f < sec ? sec : f});
        }

        for (i = 1; i <= s && check; ++i) {
            for (j = s + 1; j <= s + m && check; ++j) {
                for (k = s + m + 1; k <= s + m + d; ++k) {
                    if (find(bad, i, j) || find(bad, i, k) || find(bad, j, k)) {
                        continue;
                    }
                    ull x = 1;
                    set<ll> ingredients = food[i];
                    ingredients.insert(food[j].begin(), food[j].end());
                    ingredients.insert(food[k].begin(), food[k].end());
                    for (const auto &in: ingredients) {
                        if (MAX / brands[in] < x) {
                            check = false;
                            break;
                        } else {
                            x *= brands[in];
                        }
                    }
                    if (check) {
                        if (MAX - x >= res - 1) {
                            res += x;
                        } else {
                            check = false;
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
        if (res - 1 <= MAX && check) {
            cout << res - 1 << endl;
        } else {
            cout << "too many" << endl;
        }
    }
}

/*
6 1 1 1 0
2 3 1 5 3 2
2 1 2
3 3 4 5
1 6

    180

3 2 2 1 1
2 3 2
1 1
1 2
1 2
1 3
1 1
2 3

    22

3 1 1 1 1
5 5 5
3 1 2 3
3 1 2 3
3 1 2 3
2 1

    0

10 1 1 1 0
100 100 100 100 100 100 100 100 100 100
4 1 2 3 4
3 5 6 7
3 8 9 10

    too many

 */