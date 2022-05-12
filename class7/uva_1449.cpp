#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define EPS 1e-9

typedef vector<int> vi;

string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;

// KMP Init
void KMP_init(){
    int m = KMP_pat.length();
    lps.resize(m+1,0);
    lps[0]=-1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
//        cout << i << endl;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
ll KMP_search() {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0;
    int count = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
//            cout << "The pattern is found at index " << i-j << endl;
            j = lps[j];
            count ++;
        }
    }
    return count;
}

void dominating_patterns(vector<pair<string, ll>> patterns, string lookup){
    ll max_number = -1;
    KMP_str = lookup;
    for (auto & pattern : patterns) {
        KMP_pat = pattern.first;
        KMP_init();
        pattern.second = KMP_search();
        max_number = pattern.second > max_number ? pattern.second : max_number;
    }

    cout << max_number << endl;
    for (auto pattern : patterns) {
        if (pattern.second == max_number)
            cout << pattern.first << endl;
    }
}

int main() {
    ll N;
    cin >> N;

    while(N != 0) {
        vector<pair<string, ll>> patterns = vector<pair<string, ll>>();
        for (ll i = 0; i < N; ++i) {
            string x;
            cin >> x;
            patterns.push_back(pair<string, ll>(x, 0));
        }
        string lookup;
        cin >> lookup;

        dominating_patterns(patterns, lookup);
        cin >> N;
    }

    return 0;
}

/*

2
aba
bab
ababababac
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha
0

 */