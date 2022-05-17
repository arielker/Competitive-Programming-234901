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
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

int main() {
    string s;
    while (cin >> s) {
        if (1 == s.size()) {
            cout << "25" << endl;
            continue;
        }
        int length = s.size();
        vi lis(length, 1);
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < i; ++j) {
                if (s[i] > s[j]){
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
        }
        cout << 26 - *max_element(lis.begin(), lis.end()) << endl;
    }
    return 0;
}