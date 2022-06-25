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

const set<int> happy_primes = {7, 13, 19, 23, 31, 79, 97, 103, 109, 139, 167,
                               193,
                               239, 263,
                               293, 313, 331, 367, 379, 383, 397, 409, 487, 563,
                               617,
                               653,
                               673, 683, 709, 739, 761, 863, 881, 907, 937,
                               1009,
                               1033,
                               1039, 1093, 1151, 1277, 1303, 1373, 1427, 1447,
                               1481,
                               1487,
                               1511, 1607, 1663};

void print(int i, int x, const string &a = "NO") {
    cout << i << " " << x << " " << a << endl;
}

bool checkHappy(int x) {
    set<int> cache;
    while (x != 1) {
        if (happy_primes.find(x) != happy_primes.end()) {
            return true;
        }
        if (cache.find(x) != cache.end()) {
            return false;
        }
        cache.insert(x);
        int tmp = 0;
        while (x) {
            int i = x % 10;
            tmp += i * i;
            x /= 10;
        }
        x = tmp;
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

int main() {
    int p;
    cin >> p;
    while (p--) {
        int i, x;
        cin >> i >> x;
        if (x < 7 || !isPrime(x)) {
            print(i, x);
            continue;
        }
        print(i, x, checkHappy(x) ? "YES" : "NO");
    }
    return 0;
}
/*
4
1 1
2 7
3 383
4 1000
    --- 1 1 NO
        2 7 YES
        3 383 YES
        4 1000 NO
 */
