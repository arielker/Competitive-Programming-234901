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
    int n;
    cin >> n;
    vi numbers(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    return 0;
}

/*
1
1

    0

3
4 7 8

    3

5
2 3 4 5 8

    5

10
1 2 3 4 5 6 7 8 9 10

    12
 */