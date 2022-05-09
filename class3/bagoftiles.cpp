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

constexpr int MAXSUM = 300005;
constexpr int MAXELEMENTS = 35;
constexpr int MAXN = 35;

int x, g, m, n, t, sum, curr, win, lose;
pair<int, int> p;
int leftSize, rightSize;
int tiles[MAXELEMENTS];
int factorial[MAXELEMENTS];
int leftt[MAXN][MAXSUM];
int rightt[MAXN][MAXSUM];


int getFactorial(int n, int k) {

    memset(factorial, 0, sizeof(factorial));
    factorial[0] = 1; // Zero factorial = 1

    for (int i = 1; i <= n; i++) {
        for (int j = min(i, k); j > 0; j--) {
            factorial[j] = factorial[j] + factorial[j -
                                                    1]; // Calculate current factorial based on the previous pascal triangle row
        }
    }
    return factorial[k];
}

// Function that counts the number of partial sums of subarray
void countSubArray(int tiles[], int n, int m, int sub[][MAXSUM], int offset) {

    int maxSize = (1 << m);

    for (int i = 0; i < maxSize; i++) {
        sum = 0;
        curr = 0;
        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) { // If still have elements to take
                sum += tiles[j + offset];
                curr++;
            }
        }
        sub[curr][sum]++; // Add to the count of getting partial sum sum with curr number of elements
    }
}

// Implementation of subset sum algorithm using meet in the middle technique
pii countCombinations(int tiles[], int t, int n, int m) {

    if ((n == 0 && t == 0) || m == 0) {
        return make_pair(1, 0);
    } else if (n == 0 && t > 0) {
        return make_pair(0, 1);
    }

    // Calculate partial sums of left and right subarray
    memset(leftt, 0, sizeof(leftt));
    memset(rightt, 0, sizeof(rightt));
    countSubArray(tiles, n, m / 2, leftt, 0);
    countSubArray(tiles, n, (m - m / 2), rightt, m / 2);


    // Calculate number of partial sums that lead to k-subset sum = t
    win = 0;
    lose = 0;
    for (int i = 1; i < n; i++) {

        // sort(right[n - i].begin(), right[n - i].end()); // Sort right subarray containing n - i sized subset sums

        for (int j = 1;
             j <= t; j++) { // For each partial sum in left subarray of size i
            curr = leftt[i][j]; // Current number of partial sums equals to i
            win += curr *
                   rightt[n - i][t - j]; // Match with total sum = t and total
        }
    }

    win += leftt[n][t] + rightt[n][t];

    return make_pair(win, lose);
}

int main() {

    cin >> g;
    x = 0;

    while (g-- > 0) {
        x++;

        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> tiles[i];
        }
        cin >> n >> t;

        p = countCombinations(tiles, t, n, m);

        cout << "Game " << x << " -- " << p.first << " : "
             << getFactorial(m, n) - p.first << endl;
    }
}

/*
5
2
1 2
2 3
2
2 3
2 3
5
1 2 3 4 5
2 5
10
1 2 2 2 2 2 2 2 2 2
3 6
10
1 2 2 2 2 2 2 2 2 2
0 0

 */