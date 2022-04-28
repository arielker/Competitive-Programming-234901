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
typedef long long int lli;
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

constexpr int MAX = 2022;

int main() {
    ll r, n, m;
    cin >> r >> n >> m;
    vector<vector<lli>> ps(MAX, vector<lli>(MAX));
    int i = 2;
    ps[1][1] = 1;
    while (i <= n) {
        ps[i][i] = 1;
        if (i != r) {
            int j = 1;
            while (j < i) {
                lli last_possibles = ps[i - 1][j - 1];
                lli possibles_with_j = j * ps[i - 1][j] % m;
                lli possible_without_j = j * (j + 1) / 2 % m * ps[i - 1][j + 1] % m;
                ps[i][j] = (last_possibles + possibles_with_j + possible_without_j) % m;
                j++;
            }
        } else {
            int j = 1;
            while (j < i) {
                // mr pickles will not mentor so the number is the same
                ps[i][j] = ps[i - 1][j - 1];
                j++;
            }
        }
        i++;
    }
    cout << ps[n][1] << endl;
    return 0;
}