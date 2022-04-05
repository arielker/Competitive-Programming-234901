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

constexpr int MAX_N = 100001;

int main() {
    int t = 0, n = 0, test = 0;
    cin >> t;
    while (t--) {
        cin >> n;
        vi a(MAX_N,0);
        int input;
        for (int i = 1; i <= n; i++) {
            cin >> input;
            a[i] = input;
        }
        int k = 0;
        for (int i = 1; i <= n; i++) {
            if (k < a[i] - a[i - 1]) {
                k = a[i] - a[i - 1];
            }
        }
        int ans = k;
        for (int i = 1; i <= n; i++) {
            if (a[i] - a[i - 1] != k) {
                if (k < a[i] - a[i - 1]) {
                    ans++;
                    break;
                }
            } else {
                k--;
            }
        }
        ++test;
        cout << "Case " << test << ": " << ans << endl;
    }
    return 0;
}