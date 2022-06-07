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

#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point {
    double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator<(point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y;
    }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator==(point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);    // multiply theta with PI / 180.0
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad));
}

int main() {
    int n;
    double r, a, b;
    cin >> n >> r >> a >> b;
    vector<point> boats(n);
    for (auto &item: boats) {
        cin >> item.x >> item.y;
    }
    double degree = 0 == a ? 90 : RAD_to_DEG(atan(b / a));
    for_each(boats.begin(), boats.end(),
             [&degree](point &p) { p = rotate(p, -degree); });
    vector<pair<double, int>> segments;
    for (const auto &item: boats) {
        double v1 = item.x - sqrt(r * r - item.y * item.y);
        double v2 = item.x + sqrt(r * r - item.y * item.y);
        if (r * r - item.y * item.y >= 0) {
            segments.emplace_back(v1, 1);
            segments.emplace_back(v2, 0);
        }
    }
    sort(segments.begin(), segments.end(),
         [](pair<double, int> a, pair<double, int> b) -> bool {
             return (a.first - b.first < -EPS) ||
                    (a.first - b.first < EPS && a.second);
         });
    int c = 0, ret = 0;
    for (const auto &item: segments) {
        item.second ? c++ : c--;
        if (c > ret) {
            ret = c;
        }
    }
    cout << ret << endl;
    return 0;
}
/*
7 5 0 1
-1 -1
1 -1
0 0
2 3
3 4
10 10
2 12
    --- 5

3 1 1 0
0 0
2 0
4 0
    --- 2

4 1 1 0
0 0
1 1
1 -1
2 0
    --- 4
 */