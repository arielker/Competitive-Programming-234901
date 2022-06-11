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
    for (string l0; getline(cin, l0);) {
        string line;
        for (const auto &item: l0) {
            if (isalpha(item)) {
                line += toupper(item);
            }
        }
        if ("DONE" == line) {
            break;
        }
        int n = line.size();
        bool poly = true;
        for (int i = 0; i < n / 2; ++i) {
            if (line[i] != line[n - i]) {
                poly = false;
                break;
            }
        }
        cout << (poly ? "You won't be eaten!" : "Uh oh..") << endl;
    }
    return 0;
}
