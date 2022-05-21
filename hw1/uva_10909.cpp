///------------------------------------
///  Lucky Numbers
///------------------------------------

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

const int MAX = 2000001;

struct tree {
    int sz = 2;
    vi s_tree;

    void init(int n) {
        while (sz < n) {
            sz *= 2;
        }
        this->s_tree = vi(2 * sz, 0);
    }

    void update(int i, int v) {
        ///insert to 2nd half of the vector and update all ancestors
        i += sz;
        s_tree[i] = v;
        for (i /= 2; i >= 1; i /= 2) {
            this->s_tree[i] = this->s_tree[i * 2] + this->s_tree[i * 2 + 1];
        }
    }

    int sum(int k, int x, int a, int b) {
        ///traverse the binary tree until you reach the 2nd half of the vector
        if (x >= sz) {
            return x - sz;
        }
        return k >= a && k < a + this->s_tree[x * 2]
               ? sum(k, x * 2, a, a + s_tree[x * 2] - 1)
               : sum(k, x * 2 + 1, a + s_tree[x * 2], b);
    }

    int sum(int k) {
        ///find k starting from the first element in tree where the bounds
        ///range from 1 to s_tree[1] (total numbers in the tree)
        return sum(k, 1, 1, s_tree[1]);
    }

    int ttl() {
        /// "tree total luckies"
        return this->s_tree[1];
    }

};

int main() {
    vi lucks(MAX);
    tree tree;
    tree.init(MAX);

    ///insert all odd numbers
    for (int i = 1; i < MAX - 1; i += 2) {
        tree.update(i, 1);
    }

    int sz = tree.ttl(), j = 2;
    for (; j <= sz; j++) {
        ///find j'th serial number according to which every j'th number needs to be deleted
        ///we call that number - k.
        int k = tree.sum(j);
        ///find the last number to be deleted
        int i = sz - sz % k;
        for (; i >= 1; i -= k) {
            ///start deleting backwards all numbers
            int sum = tree.sum(i);
            if (sum == k) {
                ///excluding k itself
                break;
            }
            tree.update(sum, 0);
        }
        sz = tree.ttl();
    }

    for (int i = 1; i <= sz; ++i) {
        lucks[tree.sum(i)] = 1;
    }

    int x = 0;
    while (cin >> x) {
        if (x % 2 || !x) {
            cout << x << " is not the sum of two luckies!" << endl;
        } else {
            for (int i = x / 2; i >= 1; --i) {
                if (lucks[i] && lucks[x - i]) {
                    cout << x << " is the sum of " << i << " and " << x - i
                         << "." << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
