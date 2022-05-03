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
typedef pair<int, int> pii;

int main() {
    auto pie = acos(-1.0);
    int m, n;
    double r, x1, x2, y1, y2;
    cin >> n >> m >> r >> x1 >> y1 >> x2 >> y2;
    auto sol2 = (r * (y1 + y2)) / m;
    auto sol1 = (r * abs(y1 - y2)) / m;
    auto temp = pie;
//    temp *= pie;
    temp *= (abs(x1 - x2) / n);
    temp *= ((r * min(y1, y2)) / m);
    sol1 += temp;
    cout << fixed << setprecision(7) << min(sol1, sol2) << endl;
    return 0;
}

/*
6 5 2.0
1 3 4 2

    1.65663706143592

9 7 3.0
1 5 9 5
    4.28571428571429

10 10 1.0
2 0 6 0
    0

 */