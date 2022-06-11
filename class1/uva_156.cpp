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
    string s1, ss;
    map<string, vector<string>> d;
    vector<string> res;
    cin >> s1;
    while ("#" != s1) {
        ss = "";
        for (const auto &i: s1) {
            ss += tolower(i);
        }
        sort(ss.begin(), ss.end());
        vector<string> v;
        v.emplace_back(s1);
        if (d.find(ss) == d.end()) {
            d.insert({ss, v});
        } else {
            d[ss].emplace_back(s1);
        }
        cin >> s1;
    }
    for (const auto &item: d) {
        if (item.second.size() == 1) {
            res.emplace_back(item.second[0]);
        }
    }
    std::sort(res.begin(), res.end());
    for (const auto &item: res) {
        cout << item << endl;
    }
    return 0;
}
