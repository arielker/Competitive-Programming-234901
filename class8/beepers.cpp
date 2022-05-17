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
const int INF = 1e9;


int x_size, y_size;
int start_x, start_y;
int beepers;
int testcases;

int main() {
    cin >> testcases;
    while (testcases--) {
        cin >> x_size >> y_size >> start_x >> start_y >> beepers;
        vii beeps;
        for (int i = 0; i < beepers; ++i) {
            int a, b;
            cin >> a >> b;
            beeps.emplace_back(a, b);
        }
        sort(beeps.begin(), beeps.end());
        int curr_min = INF;

        ///ugly brute force LMFAO LET'S GOOOOOOOOOO!!!!!!!
         do {
            int steps = 0;
            int curr_x = start_x, curr_y = start_y;
            for (const auto &p: beeps) {
                steps += abs(curr_x - p.first) + abs(curr_y - p.second);
                curr_x = p.first;
                curr_y = p.second;
            }
            steps += (abs(start_x - curr_x) + abs(start_y - curr_y));
            if (curr_min > steps) {
                curr_min = steps;
            }
        } while (next_permutation(beeps.begin(), beeps.end()));
        cout << curr_min << endl;
    }
    return 0;
}

/*
1
10 10
1 1
4
2 3
5 5
9 4
6 5

    24
*/