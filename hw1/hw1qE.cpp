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

constexpr int MAX = 1000;
vll sol(MAX, 0);
vll matrix(MAX, 0);


void compute(int n, ll mod) {
    vll save(MAX, 0);
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j <= i; ++j) {
            sum += matrix[j] * sol[i - j];
        }
        for (int j = i + 1; j < n; ++j) {
            sum += matrix[j] * sol[i - j + n];
        }
        save[i] = sum;
    }
    for (int i = 0; i < n; ++i) {
        sol[i] = save[i] % mod;
    }
}

void adjust(int n, ll mod) {
    vll save(MAX, 0);
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j <= i; ++j) {
            sum += matrix[j] * matrix[i - j];
        }
        for (int j = i + 1; j < n; ++j) {
            sum += matrix[j] * matrix[i - j + n];
        }
        save[i] = sum;
    }
    for (int i = 0; i < n; ++i) {
        matrix[i] = save[i] % mod;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        matrix.clear();
        ll s;
        int n, l, r, x;
        cin >> n >> s >> l >> r >> x;
        ll mod = 1;
        for (int i = 0; i < x; ++i) {
            mod *= 10;
        }
        for (int i = 0; i < n; ++i) {
            cin >> sol[i];
            sol[i] %= mod;
        }
        matrix[0] = 1;
        matrix[1] = l;
        matrix[n - 1] = r;
        while (s) {
            if (s % 2) {
                compute(n, mod);
            }
            adjust(n, mod);
            s /= 2;
        }
        for (int i = 0; i < n; ++i) {
            if (n - 1 == i) {
                cout << sol[i] << endl;
                break;
            }
            cout << sol[i] << " ";
        }
    }
    return 0;
}

/*
5

3 1 1 1 3
1 1 1

3 0 1 1 3
23 42 0

3 1 1 1 3
23 42 0

4 10 2 1 9
1 2 3 4

5 999999999 3 8 7
8 7 8 7 12

    3 3 3
    23 42 0
    65 65 65
    2620960 2621920 2620896 2621984
    2425139 2372828 6040064 4331745 9713040
 */