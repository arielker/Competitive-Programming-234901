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

constexpr int SIZE = 26;

char i2c(int index) {
    return 'a' + index;
}

char c2i(char c) {
    return c - 'a';
}

class Trie {
public:
    Trie **ptrs;
    int *counters;

    Trie() : ptrs(new Trie *[SIZE]), counters(new int[SIZE]) {
        for (int i = 0; i < SIZE; ++i) {
            ptrs[i] = nullptr;
            counters[i] = 0;
        }
    }

    virtual ~Trie() {
        Trie &t = *this;
        for (int i = 0; i < SIZE; ++i) {
            if (t.ptrs[i]) {
                delete t.ptrs[i];
            }
        }
        delete[] t.ptrs;
        delete[] t.counters;
    }

    void insert(string &s) {
        Trie *curr_trie = this;
        for (const auto &item: s) {
            int i = c2i(item);
            if (curr_trie->counters[i] == 0) {
                curr_trie->ptrs[i] = new Trie();
            }
            curr_trie->counters[i]++;
            curr_trie = curr_trie->ptrs[i];
        }
    }

    int getNumberOfOnes() const {
        int count = 0;
        for (int i = 0; i < SIZE; ++i) {
            if (counters[i] == 1) {
                count++;
            }
        }
        return count;
    }
};

int walk(Trie &trie) {
    int count = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (trie.counters[i] == 1) {
            count++;
        } else if (trie.counters[i] > 1) {
            count += (trie.counters[i] + walk(*trie.ptrs[i]));
        }
    }
    return count;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Trie trie;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            trie.insert(s);
        }
        cout << walk(trie) << endl;
    }
    return 0;
}
/*
1
3
aaaaa
bbb
abababab
    --- 5
 */