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

int main() {
    int h, u, d, f;
    while (cin >> h >> u >> d >> f) {
        if (0 == h) {
            break;
        }
        int day = 1;
        auto dist = (float) u, curr_u = float(u);
        while (dist <= h) {
            dist -= d;
            if (dist < 0) {
                break;
            }
            day++;
            curr_u -= f * u * 0.01;
            if (curr_u < 0) {
                curr_u = 0;
            }
            dist += curr_u;
        }
        if (dist >= u) {
            cout << "success on day " << day << endl;
        } else {
            cout << "failure on day " << day << endl;
        }
    }
    return 0;
}
