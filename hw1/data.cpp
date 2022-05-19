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

constexpr int MAX = 14 * 1000;


ll mulmodn(ll a, ll b, ll n) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % n;
        a = (a * 2) % n;
        b >>= 1;
    }
    return res;
}

ll powmodn(ll a, ll q, ll n) {
    ll res = 1;
    while (q) {
        if (q & 1) res = mulmodn(res, a, n);
        a = mulmodn(a, a, n);
        q >>= 1;
    }
    return res;
}

bool MR(ll n, int k = 5) {
    if (n == 1 || n == 4)
        return false;
    if (n == 2 || n == 3)
        return true;
    ll m = n - 1;
    int r = 0;
    while (m % 2 == 0) {
        m >>= 1;
        r += 1;
    }
    /* !!! Deterministic version for n<2^64 !!! */
//    int dtrm_set[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
//    for(ll a: dtrm_set){
//        if(a >= n) break;
    /* !!! End of deterministic version !!! */

    /* !!! Probablistic version !!! */
    while (k--) {
        ll a = rand() % (n - 4) + 2;
        /* !!! end of probablisitic version !!! */
        a = powmodn(a, m, n);
        if (a == 1) continue;
        int i = r;
        while (i-- && a != n - 1) {
            a = mulmodn(a, a, n);
            if (a == 1) return false;
        }
        if (i == -1) return false;
    }
    return true;
}

bool isPrime(ll n) {
    if (n < 2)
        return false;
    ll sqrtn = sqrt(n);
    for (ll i = 2; i <= sqrtn; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

vector<bool> sieve(int n) {
    vector<bool> ps(n + 1, true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 0; i <= sqrtn; ++i) {
        if (ps[i]) {
            for (int j = i * i; j <= n; j += i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

vi subsetPrices(int n, const vi &numbers, const vector<bool> &primes);

int getDistinctPrimesOfSum(int accumulate, const vector<bool> &primes);

void DPfunction(int n, const vi &numbers, const vi &subset_prices);

void aux(const vi &numbers, const vi &subset_prices, vi &dp, int i);

bool isSubset(int i, int j);

int main() {
    int n;
    cin >> n;
    vi numbers(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    vector<bool> primes = sieve(MAX);
    vi subset_prices = subsetPrices(n, numbers, primes);
    DPfunction(n, numbers, subset_prices);
    return 0;
}

void DPfunction(int n, const vi &numbers, const vi &subset_prices) {
    int subset_amount = static_cast<int>(pow(2, n));
    vi dp(subset_amount, 0);
    for (int i = 1; i < subset_amount; ++i) {
        aux(numbers, subset_prices, dp, i);
    }
    cout << *(dp.end() - 1) << endl;
}

void aux(const vi &numbers, const vi &subset_prices, vi &dp, int i) {
    int x = 0;
    for (int j = 1; j <= i; ++j) {
        if (isSubset(i, j)) {
            if (subset_prices[j] + dp[i - j] > x) {
                x = subset_prices[j] + dp[i - j];
            }
        }
    }
    dp[i] = x;
}

bool isSubset(int i, int j) {
    while (0 != i) {
        if ((0 == i % 2) && (1 == j % 2)) {
            return false;
        }
        i /= 2;
        j /= 2;
    }
    return true;
}

vi subsetPrices(int n, const vi &numbers, const vector<bool> &primes) {
    int count = pow(2, n);
    vi prices;
    for (int i = 0; i < count; ++i) {
        int accumulate = 0;
        for (int j = 0; j < n; ++j) {
            if ((i & (1 << j)) != 0) { //found this code online
                accumulate += numbers[j];
            }
        }
        int x = getDistinctPrimesOfSum(accumulate, primes);
        prices.emplace_back(x);
    }
    return prices;
}

int getDistinctPrimesOfSum(int accumulate, const vector<bool> &primes) {
    int count = 0;
    for (int i = 2; i < accumulate + 1 && 0 != accumulate; ++i) {
        if (primes[i] && 0 == accumulate % i) {
            while (0 == accumulate % i) {
                accumulate /= i;
            }
            count++;
        }
    }
    return count;
}

/*
1
1

    0

3
4 7 8

    3

5
2 3 4 5 8

    5

10
1 2 3 4 5 6 7 8 9 10

    12
 */