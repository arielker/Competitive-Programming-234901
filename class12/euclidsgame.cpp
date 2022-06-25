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

const string stan = "Stan wins";
const string ollie = "Ollie wins";


string euclidsGame(ll a, ll b);

int main() {
    ll a, b;
    while (cin >> a >> b) {
        if (!a && !b) {
            break;
        }
        cout << euclidsGame(max(a, b), min(a, b)) << endl;
    }
    return 0;
}

string euclidsGame(ll a, ll b) {
    if (0 == a % b || a > 2 * b) {
        return stan;
    }
    return euclidsGame(b, a % b) == ollie ? stan : ollie;
}
/*
34 12
15 24
0 0
    ---
    Stan wins
    Ollie wins
 */