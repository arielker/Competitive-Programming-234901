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
#include <iomanip>

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

#define EPS 1e-9
#define MAX_SIZE 100

struct PT {
    double x, y;

    explicit PT(double d = 0.0, double d1 = 0.0): x(d), y(d1){}


    // compare the lexicographic order of 2 points
    // first compare x, if 2 x's are equal, compare y
    bool operator<(const PT &_p) const {
        if (fabs(x - _p.x) > EPS) {
            return (x < _p.x);
        } else {
            return (y < _p.y);
        }
    }
};

// check p3 (leftmost) -> p2 -> p1 (rightmost) left turn (not right turn)
bool left(PT &p1, PT &p2, PT &p3) {
    double cross =
            (p2.x - p3.x) * (p1.y - p3.y) - (p2.y - p3.y) * (p1.x - p3.x);
    if (fabs(cross) <= EPS)
        return true;    // to delete p2
    if (cross > 0)
        return true;
    return false;
}

vector<PT> convex_hull(vector<PT> &Points) {
    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<PT> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i = 2; i < Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            PT p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (!left(Points[i], p2, p3)) {
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (int i = 0; i < Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<PT> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i = 2; i < Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            PT p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (!left(Points[i], p2, p3)) {
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<PT> CH;
    stk_low.pop();
    PT p;
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    reverse(CH.begin(), CH.end());  // ccw -> cw
    return CH;
}

double area(const vector<PT>& points) {
    double area = 0.0;
    int x = static_cast<int>(points.size() - 1);
    for (int i = 0; i < points.size(); ++i) {
        area += (points[x].x + points[i].x) * (points[x].y - points[i].y);
        x = i;
    }
    return abs(area / 2.0);
}

int main() {
    int n;
    while (cin >> n){
        if (0 == n){
            return 0;
        }
        vector<PT> points(n, PT());
        for (int i = 0; i < n; ++i) {
            double x, y;
            cin >> x >> y;
            points[i].x = x;
            points[i].y = y;
        }
        cout << 1.0 * area(convex_hull(points)) * 1.0 << endl;
    }
    return 0;
}

/*
5
0 0
10 10
0 10
10 0
5 5
10
6 39
28 25
28 13
31 3
11 19
31 17
26 19
18 13
30 11
25 20
0
    100.0
    406.0
 */