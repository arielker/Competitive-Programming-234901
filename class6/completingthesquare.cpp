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
typedef pair<double, double> pdd;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

constexpr double EPS = 1e-16;

pdd getPoint4(double first, double second, int x1, int y1);

static inline double dist(int x, int y, int xx, int yy) {
    int delta1 = x - xx, delta2 = y - yy;
    return sqrt(delta1 * delta1 + delta2 * delta2);
}

static inline pdd getMiddle(int x, int y, int xx, int yy) {
    return {(double (x + xx)) / 2, (double (y + yy)) / 2};
}

int main() {
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    if (dist(x1, y1, x2, y2) == dist(x1, y1, x3, y3)) {
        //x1, y1
        pdd midpoint = getMiddle(x2, y2, x3, y3);
        pdd p4 = getPoint4(midpoint.first, midpoint.second, x1, y1);
        cout << p4.first << " " << p4.second << endl;
    } else if (dist(x2, y2, x1, y1) == dist(x2, y2, x3, y3)) {
        //x2, y2
        pdd midpoint = getMiddle(x1, y1, x3, y3);
        pdd p4 = getPoint4(midpoint.first, midpoint.second, x2, y2);
        cout << p4.first << " " << p4.second << endl;
    } else { //x3, y3
        pdd midpoint = getMiddle(x1, y1, x2, y2);
        pdd p4 = getPoint4(midpoint.first, midpoint.second, x3, y3);
        cout << p4.first << " " << p4.second << endl;
    }
    return 0;
}

pdd getPoint4(double first, double second, int x1, int y1) {
    double delta1 = first - x1, delta2 = second - y1;
    return {first + delta1, second + delta2};
}

/*
2 -5
-8 -1
-5 -8

    -1 2

0 0
1 0
1 1

    0 1

2 -1
-2 3
2 7

    6 3
 */