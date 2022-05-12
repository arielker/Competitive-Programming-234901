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
typedef map<string, int> msi;

const ll MOD = 1000000007;

bool startsWith(const string &a, const string &b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

ll recFun(string &w, map<char, map<string, int>> &dict, int position, ull n,
          map<ll, ll> &memory) {
    if (position >= n) {
        return 1;
    }
    if (memory.count(position) <= 0) {
        ll ss = 0;
        for (const auto &p: dict[w[position]]) {
            string part = p.first;
            int mean = p.second;
            string fromWhich = w.substr(position);
            if (startsWith(part, fromWhich)) {
                ss = (ss + mean * recFun(w, dict, position + part.size(), n, memory)) % MOD;
            }
        }
        memory[position] = ss;
    }
    return memory[position];
}


int main() {
    int n;
    string family;
    cin >> n >> family;
    map<char, map<string, int>> dict;
    for (int i = 0; i < n; ++i) {
        string string1;
        int x;
        cin >> string1 >> x;
        dict[string1[0]][string1] = x;
    }
    map<ll, ll> memory;
    cout << recFun(family, dict, 0, family.size(), memory) << endl;
    return 0;
}

/*
5 heimark
hei 2
mark 2
heim 1
ark 2
heima 1

    6
 */