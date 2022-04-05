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

constexpr int MAX_n = 102;

int match[MAX_n][MAX_n];
int C1[MAX_n] = {0}, C2[MAX_n] = {0};
int index1, index2;
vector<pii> E;
int n, m;

int toPair(const int A[], int i, int ind) {
    int j, c = 0;
    for (j = 0; j < ind; j++) {
        if (match[A[j]][i] == 1) {
            c++;
        }
    }
    return c;
}

void clear() {
    for (auto &i: E) {
        match[i.first][i.second] = 0;
        match[i.second][i.first] = 0;
    }
    E.clear();
}

void calc() {
    int i = 0, p = 0, c1 = 0, c2 = 0;
    index1 = 1, index2 = 0;
    C1[0] = 1;
//    if (n <= 1) {
//        cout << "0" << endl;
//        return;
//    }
    for (i = 2; i <= n; ++i) {
        c1 = toPair(C1, i, index1);
        c2 = toPair(C2, i, index2);
        if (c1 < c2) {
            C1[index1] = i;
            index1++;
            p += c1;
        } else {
            C2[index2] = i;
            index2++;
            p += c2;
        }
    }
    cout << index1 << endl;
    cout << C1[0];
    for (i = 1; i < index1; i++) {
        cout << " " << C1[i];
    }
    cout << endl;
}

int main() {
    int N, c = 1;
    cin >> N;
    while (N--) {
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            match[u][v] = match[v][u] = 1;
            E.emplace_back(make_pair(u,v));
        }
        cout << "Case #" << c++ << ": ";
        calc();
        clear();
    }
    return 0;
}

/*
2
4 3
1 2
2 3
3 4
4 6
1 2
1 3
1 4
2 3
2 4
3 4

 */