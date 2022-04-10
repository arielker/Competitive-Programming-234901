///------------------------------------
///  Duathlon
///------------------------------------

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
#include "iomanip"

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

constexpr double EPS = 1e-8;
constexpr int MAX_CONTESTANTS = 20;

int n; ///contestants (< 20)
double t; ///total road race distance
pdd speeds[MAX_CONTESTANTS];

double getTime(pdd speed, pdd length) {
    return (length.first / speed.first) + (length.second / speed.second);
}

double getDiff(double l) {
    pdd currentLength(l, t - l);
    double cheaterTime = getTime(speeds[n - 1], currentLength);

    vector<double> times;
    times.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        times.emplace_back(getTime(speeds[i], currentLength));
    }

    return (cheaterTime - *min_element(times.begin(), times.end())) * 3600.00;
}

///first is running speed (r) and then cycling speed (k)

int main() {
    cout << fixed << setprecision(2);

    while (cin >> t) {
//        cout << "t = " << t << endl;
        cin >> n;
//        cout << "n = " << n << endl;
        for (int i = 0; i < n; i++) {
            cin >> speeds[i].first >> speeds[i].second;
//            cout << speeds[i].first << " " << speeds[i].second << endl;
        }

        ///ternary search
        double l = 0.0;
        double r = t;

        while (fabs(r - l) > EPS) {
            double ml = (r + r + l) / 3.0;
            double mr = (r + l + l) / 3.0;

            getDiff(mr) < getDiff(ml) ? (r = ml) : (l = mr);
        }

        double b = -getDiff(l); ///not really sure why minus is needed
        if (b < 0) {
            cout << "The cheater cannot win." << endl;
        } else {
            cout << "The cheater can win by "
                 << (int) round(b)
                 << " seconds with r = " << l << "km and k = " << t - l
                 << "km." << endl;
        }
    }

    return 0;
}

/*
100
3
10.0 40.0
20.0 30.0
15.0 35.0

100
3
10.0 40.0
20.0 30.0
15.0 25.0

*/