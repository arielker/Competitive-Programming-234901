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
    string test0, test1;
    int k;
    cin >> k >> test0 >> test1;
    ull testSize = test0.size();
    int same = 0;

    for (int i = 0; i < testSize; i++) {
        if(test0[i] == test1[i]){
            same++;
        }
    }

    ull diff = testSize - same;

    if (k < same) {
        cout << k + diff << endl;
        return 0;
    }

    ull he_smarter = k - same;
    ull im_smarter = testSize - he_smarter - k;
    ///intersect + smarter
    cout << im_smarter + k << endl;

    return 0;
}

/*
3
FTFFF
TFTTT

    2

6
TTFTFFTFTF
TTTTFFTTTT

    9

 */