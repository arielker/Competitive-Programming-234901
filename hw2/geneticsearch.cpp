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
#define EPS 1e-9

string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;

// KMP Init
void KMP_init() {
    int m = KMP_pat.length();
    lps.resize(m + 1, 0);
    lps[0] = -1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++;
        j++;
//        cout << i << endl;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is already initialized with KMP_init
int KMP_search() {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0, count = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++;
        j++;
        if (j == m) { // Pattern found
//            cout << "The pattern is found at index " << i - j << endl;
            j = lps[j];
            count++;
        }
    }
    return count;
}


int main() {
    const vector<char> dna = {'A', 'G', 'C', 'T'};
    while (cin >> KMP_pat) {
        if ('0' == KMP_pat[0]) {
            break;
        }
        cin >> KMP_str;
        KMP_init();
        int t1 = KMP_search(), t2 = 0, t3 = 0;
        set<string> type2s, type3s;
        for (int i = 0; i < KMP_pat.size(); ++i) {
            string s = KMP_pat.substr(0, i) + KMP_pat.substr(i + 1);
            type2s.insert(s);
        }
        for (const auto &item: dna) {
            type3s.insert(KMP_pat + item);
            for (int i = 0; i < KMP_pat.size(); ++i) {
                string s = KMP_pat.substr(0, i) + item + KMP_pat.substr(i);
                type3s.insert(s);
            }
        }
        for (const auto &item: type2s) {
            KMP_pat = item;
            KMP_init();
            t2 += KMP_search();
        }
        for (const auto &item: type3s) {
            KMP_pat = item;
            KMP_init();
            t3 += KMP_search();
        }
        cout << t1 << " " << t2 << " " << t3 << endl;
    }
    return 0;
}
/*
AGCT AGCTAGCT
AAA AAAAAAAAAA
AGC TTTTGT
0

    2 4 2
    8 9 7
    0 0 0
 */