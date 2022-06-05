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

typedef pair<point, point> pp;

double dist(point p1, point p2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y);
}           // return double

pp bruteForce(const vector<point> &points) {
    double min_dist = numeric_limits<double>::max();
    point p1, p2;
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            if (dist(points[i], points[j]) < min_dist) {
                min_dist = dist(points[i], points[j]);
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return {p1, p2};
}

pp stripClosest(vector<point> &points, double d, const pp &pp1) {
    double min_dist = d;
    point p1 = pp1.first, p2 = pp1.second;
    sort(points.begin(), points.end(),
         [](point a, point b) { return a.y < b.y; });
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size() && (points[j].y - points[i].y) < min_dist; ++j) {
            if (dist(points[i], points[j]) < min_dist) {
                min_dist = dist(points[i], points[j]);
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return {p1, p2};
}

pp closest(vector<point> &points) {
    if (points.size() <= 3) {
        ///if amount of points is less than or equal to 3, BF can be used.
        return bruteForce(points);
    }
    int mid = points.size() / 2;
    point mid_point = points[mid];
    vector<point> left(points.begin(), points.begin() + mid);
    pp ppl = closest(left);
    vector<point> right(points.begin() + mid, points.end());
    pp ppr = closest(right);

    double min_dist;
    pp ret;
    if (dist(ppl.first, ppl.second) < dist(ppr.first, ppr.second)) {
        min_dist = dist(ppl.first, ppl.second);
        ret = ppl;
    } else {
        min_dist = dist(ppr.first, ppr.second);
        ret = ppr;
    }

    vector<point> strip;
    for (auto &point: points) {
        if (fabs(point.x - mid_point.x) < min_dist) {
            strip.emplace_back(point);
        }
    }
    pp other_pp = stripClosest(strip, min_dist, ret);
    return min_dist < dist(other_pp.first, other_pp.second) ? ret : other_pp;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<point> points;
        for (int i = 0; i < n; ++i) {
            double x, y;
            cin >> x >> y;
            points.emplace_back(point(x, y));
        }
        sort(points.begin(), points.end());
        pp pp1 = closest(points);
        cout << fixed << setprecision(3)
             << pp1.first.x << " " << pp1.first.y << " "
             << pp1.second.x << " " << pp1.second.y << endl;
    }
    return 0;
}
/*
2
1.12 0
0 0.51
3
158 12
123 15
1859 -1489
3
21.12 -884.2
18.18 43.34
21.12 -884.2
0
    ---
    0.0 0.51 1.12 0.00
    123 15 158 12.00
    21.12 -884.20 21.12 -884.20
 */