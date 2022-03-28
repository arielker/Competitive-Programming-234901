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
typedef pair<int, int> pii;

using namespace std;

int main() {
    ull W = 0;
    while (cin >> W) {
        ull N = 0;
        cin >> N;
        ll area = 0;
        for (int i = 0; i < N; i++) {
            ull w = 0, l = 0;
            cin >> w >> l;
            area += w * l;
        }
        cout << area / W << endl;
    }
    return 0;
}
