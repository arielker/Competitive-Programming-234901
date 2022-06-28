#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

typedef long long ll;

// bool
typedef pair<bool, bool> bb;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<bb> vbb;
typedef vector<vbb> vvbb;

// int
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

// double
typedef pair<double, double> dd;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<dd> vdd;
typedef vector<vdd> vvdd;

// ll
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;

// set
typedef set<int> si;
typedef set<ll> sll;
typedef set<vii> svii;
typedef vector<si> vsi;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }


/// classes
struct Point {
    double x, y; // cartesian values
    double radius, alpha; // polar values

    Point(double x, double y) : x(x), y(y) {
        // polar values
        radius = sqrt(x * x + y * y);

        alpha = atan2(y, x);
        if (alpha < 0) alpha += 2 * PI;
    };

    Point() {
        x = 0;
        y = 0;
        radius = 0;
        alpha = 0;
    };

    // compare the lexicographic order of 2 points
    // first compare x, if 2 x's are equal, compare y
    bool operator<(const Point &_p) const {
        if (fabs(x - _p.x) > EPS) {
            return (x < _p.x);
        } else {
            return (y < _p.y);
        }
    }

    bool operator==(const Point &other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }

    Point operator+(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    double dot(const Point &p) const {
        return (x * p.x + y * p.y);
    }

    Point operator*(const double val) const {
        return Point(x * val, y * val);
    }

    Point operator/(const double val) const {
        return Point(x / val, y / val);
    }

    double dist_to(const Point &p) const {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }

    double cross(const Point &p) const {
        return (x * p.y - y * p.x);
    }

    double slope_with(Point p) {
        return (y - p.y) / (x - p.x);
    }

    Point rotate(double theta) {
        // rotate p by theta degrees CCW w.r.t origin (0, 0)
        double rad = DEG_to_RAD(theta);    // multiply theta with PI / 180.0
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }
};

struct Segment {
    Point p1, p2;

    Segment(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

    double cross(const Segment &seg) const {
        return (p2 - p1).cross(seg.p2 - seg.p1);
    }

    double dot(const Segment &seg) const {
        return (p2 - p1).dot(seg.p2 - seg.p1);
    }

    double slope() {
        return (p2.y - p1.y) / (p2.x - p1.x);
    }
};

struct Line {
    double m, n; // y = mx + n
    double A, B, C; // Ax + By + C = 0

    Line(const Point &p1, const Point &p2) {
        // initialize first method y = mx + n
        if (abs(p1.x - p2.x) < EPS) {          // special case: vertical line
            m = INF;                    // l contains m = INF and c = x_value
            n = p1.x;                  // to denote vertical line x = x_value
        } else {
            m = (double) (p1.y - p2.y) / (p1.x - p2.x);
            n = p1.y - m * p1.x;
        }

        // initialize second method Ax + By + C = 0
        if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
            A = 1.0;
            B = 0.0;
            C = -p1.x;           // default values
        } else {
            A = -(double) (p1.y - p2.y) / (p1.x - p2.x);
            B = 1.0;              // IMPORTANT: we fix the value of b to 1.0
            C = -(double) (A * p1.x) - p1.y;
        }
    }

    Line(Point p, double _m) {
        // initialize first method y = mx + n
        m = _m;
        n = p.y - _m * p.x;

        // initialize second method Ax + By + C = 0
        A = -_m;                                               // always -m
        B = 1;                                                // always 1
        C = -((A * p.x) + (B * p.y));                     // compute this
    }

    bool areParallel(Line l) {       // check coefficients a & b
        return (fabs(A - l.A) < EPS) && (fabs(B - l.B) < EPS);
    }

    bool areSame(Line l) {           // also check coefficient c
        return this->areParallel(l) && (fabs(C - l.C) < EPS);
    }

// returns true (+ intersection point) if two lines are intersect
    bool areIntersect(Line l, Point &p) {
        if (this->areParallel(l))
            return false;            // no intersection

        // solve system of 2 linear algebraic equations with 2 unknowns
        p.x = (l.B * C - B * C) / (l.A * B - A * l.B);
        // special case: test for vertical line to avoid division by zero
        if (fabs(B) > EPS)
            p.y = -(A * p.x + C);
        else
            p.y = -(l.A * p.x + l.C);
        return true;
    }

    double operator()(double x) {
        return m * x + n;
        return (A * x + C) / -B;
    }
};

struct Vec {
    double x, y;

    Vec(double x, double y) : x(x), y(y) {};

    Vec(Point p1, Point p2) {       // convert 2 points to vector p1->p2
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }

    Vec scale(double s) const {        // nonnegative s = [<1 .. 1 .. >1]
        return Vec(x * s, y * s);  // shorter.same.longer
    }

    double operator*(Vec v) const {
        return x * v.x + y * v.y;
    }

    double dot(Vec v) const {
        return x * v.x + y * v.y;
    }

    double norm() const {
        return sqrt(x * x + y * y);
    }

    double norm_sq() const {
        return x * x + y * y;
    }

    double cross(const Vec &v) const {
        return x * v.y - y * v.x;
    }

    double angle(const Vec &u, const Vec &v) {
        return acos(min(1.0, std::max(-1.0, u.dot(v) / (u.norm() * v.norm()))));
    }

    void rotate_vec(Vec &u, double angle) {
        // rotate vector (x1, y1) clockwise by the given angle (angle in radians)
        angle *= -1;
        double newX = u.x * cos(angle) - u.y * sin(angle);
        double newY = u.x * sin(angle) + u.y * cos(angle);

        u.x = newX;
        u.y = newY;
    }
};

// point
typedef vector<Point> vp;
typedef vector<vp> vvp;


/// utils

// check p3 (leftmost) -> p2 -> p1 (rightmost) left turn (not right turn)
bool left(const Point &p1, const Point &p2, const Point &p3) {
    double cross =
            (p2.x - p3.x) * (p1.y - p3.y) - (p2.y - p3.y) * (p1.x - p3.x);

    if (fabs(cross) <= EPS)
        return true;    // to delete p2
    if (cross > 0)
        return true;
    return false;
}

Point translate(Point p, Vec v) {        // translate p according to v
    return Point(p.x + v.x, p.y + v.y);
}

void closestPoint(Line l, Point p, Point &ans) {
    if (fabs(l.B) < EPS) {              // special case 1: vertical line
        ans.x = -(l.C);
        ans.y = p.y;
        return;
    }

    if (fabs(l.A) < EPS) {            // special case 2: horizontal line
        ans.x = p.x;
        ans.y = -(l.C);
        return;
    }

    Line perpendicular(p, 1 /
                          l.A);         // normal line perpendicular to l and pass through p
    // intersect line l with this perpendicular line
    // the intersection point is the closest point
    l.areIntersect(perpendicular, ans);
}

// returns the reflection of point on a line
void reflectionPoint(Line l, Point p, Point &ans) {
    Point b;
    closestPoint(l, p, b);                     // similar to distToLine
    Vec v = Vec(p, b);                             // create a vector
    ans = translate(translate(p, v), v); // translate p twice
}

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(Point p, Point a, Point b, Point &c) {
    // formula: c = a + u * ab
    Vec ap = Vec(a, p), ab = Vec(a, b);
    double u = ab.dot(ap) / ab.norm_sq();
    c = translate(a, ab.scale(u));                  // translate a to c
    return p.dist_to(c);
}           // Euclidean distance between p and c

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(Point p, Point a, Point b, Point &c) {
    Vec ap = Vec(a, p), ab = Vec(a, b);
    double u = ab.dot(ap) / ab.norm_sq();
    if (u < 0.0) {
        c = Point(a.x, a.y);                   // closer to a
        return p.dist_to(a);
    }         // Euclidean distance between p and a
    if (u > 1.0) {
        c = Point(b.x, b.y);                   // closer to b
        return p.dist_to(b);
    }         // Euclidean distance between p and b
    return distToLine(p, a, b, c);
}          // run distToLine as above

double angle(Point a, Point o, Point b) {  // returns angle aob in rad
    Vec oa = Vec(o, a), ob = Vec(o, b);
    return acos(oa.dot(ob) / sqrt(oa.norm_sq() * ob.norm_sq()));
}

int triangle_area(Point p, Point q,
                  Point r) { // returns 'twice' the area of this triangle A-B-c
    return (p.x * q.y - p.y * q.x +
            q.x * r.y - q.y * r.x +
            r.x * p.y - r.y * p.x) / 2;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(Point p, Point q, Point r) {
    return Vec(p, q).cross(Vec(p, r)) > 0;
}

// returns true if point r is on the same line as the line pq
bool collinear(Point p, Point q, Point r) {
    return fabs(Vec(p, q).cross(Vec(p, r))) < EPS;
}


/// check point on/in/out polygon/segment/triangle

bool check_point_on_segment(const Segment &seg, const Point &p) {
    if (p.dist_to(seg.p1) < EPS || p.dist_to(seg.p2) < EPS) {
        return true;
    }

    Segment seg1 = Segment(seg.p1, p);
    Segment seg2 = Segment(seg.p2, p);
    if (abs(seg1.cross(seg2)) < EPS // check parallel
        && seg1.dot(seg2) < 0) {
        return true;
    }
    return false;
}

bool check_point_on_polygon(vp &points, const Point &p) {
    for (int i = 0; i < points.size(); ++i) {
        Segment seg = Segment(points[i], points[(i + 1) % points.size()]);
        if (check_point_on_segment(seg, p)) {
            return true;
        }
    }
    return false;
}

bool check_point_in_polygon(vp &points, const Point &p) {
    int count = 0;
    for (int i = 0; i < points.size(); ++i) {
        int j = (i + 1) % points.size();
        Point p1 = points[i];
        Point p2 = points[j];
        if ((p.y < p1.y != p.y < p2.y) &&
            ((p.x - p1.x) < (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y))) {
//            ((p.x - p1.x) / (p.y - p1.y) < (p2.x - p1.x) / (p2.y - p1.y))) {
            count += 1;
        }
    }
    return count % 2;
}

string check_point(vp &points, const Point &p) {
    if (check_point_on_polygon(points, p)) {
        return "on";
    } else if (check_point_in_polygon(points, p)) {
        return "in";
    } else {
        return "out";
    }
}

bool check_point_in_triangle(Point p, Point triangle_p1, Point triangle_p2,
                             Point triangle_p3) {
    bool b0 = (Vec(p.x - triangle_p1.x, p.y - triangle_p1.y) *
               Vec(triangle_p1.y - triangle_p2.y,
                   triangle_p2.x - triangle_p1.x) > 0);
    bool b1 = (Vec(p.x - triangle_p2.x, p.y - triangle_p2.y) *
               Vec(triangle_p2.y - triangle_p3.y,
                   triangle_p3.x - triangle_p2.x) > 0);
    bool b2 = (Vec(p.x - triangle_p3.x, p.y - triangle_p3.y) *
               Vec(triangle_p3.y - triangle_p1.y,
                   triangle_p1.x - triangle_p3.x) > 0);
    return (b0 == b1 && b1 == b2);
}

bool check_point_in_convex_polygon(Point &p, vp &polygon) {
    // 1. Partition into wedges with vertex p0
    // 2. Binary search to find the wedge p lies in
    // 3. Check if p lies in the triangle
    int lo = 1, hi = polygon.size() - 1, mid = 0, ans = 0;
    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        Line l = Line(polygon[mid], polygon[0]);
        if (l(p.x) >= p.y) lo = mid;
        else hi = mid;
    }
    return check_point_in_triangle(p, polygon[0], polygon[lo], polygon[hi]);
}

/// calculate polygon area

vp convex_hull(vp &Points) {
    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<Point> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i = 2; i < Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            Point p2, p3;
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
    stack<Point> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i = 2; i < Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            Point p2, p3;
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
    vp CH;
    Point p;
    stk_low.pop();
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
//    for (vp::const_iterator iter = CH.begin(); iter != CH.end(); iter++)
//        cout << (*iter).x << ' ' << (*iter).y << endl;
    return CH;
}

// calculate the area of the convex hull consists of all points
long double calculate_polygon_area(vp &CH) {
//    vp CH = convex_hull(points); // check if needed

    // Shoelace formula
    long double area = 0.0;
    int j = CH.size() - 1;
    for (int i = 0; i < CH.size(); i++) {
        area += (CH[j].x + CH[i].x) * (CH[j].y - CH[i].y);
        j = i;
    }

    return abs(area / 2.0);
}


int main() {
    ll N;
    cin >> N;

    long double area = 0.0;
    for (int i = 0; i < N; ++i) {
        ll P;
        cin >> P;

        vp points = vp();
        for (int j = 0; j < P; ++j) {
            ll x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }
        area += floor(calculate_polygon_area(points));
    }
    cout << floor(area);
    return 0;
}

/*
1
4
0 0
1 0
1 1
0 1

2
5
98 35
79 90
21 90
2 36
50 0
3
0 0
20 0
0 20

 */