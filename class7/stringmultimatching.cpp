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
// Assuming lps is allready initialized with KMP_init
void KMP_search() {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++;
        j++;
        if (j == m) { // Pattern found
            cout << i - j << " ";
            j = lps[j];
        }
    }
    cout << endl;
}

void string_multimatching(vector<string> patterns, string lookup) {
//    KMP_str = lookup;
    for (auto &pattern: patterns) {
//        KMP_pat = pattern;
//        KMP_init();
//        KMP_search();

        ll pos = 0;
        do {
            pos = lookup.find(pattern, pos);
            if (pos == -1) {
                break;
            } else {
                cout << pos++ << " ";
            }
        } while (true);
        cout << endl;
    }
}

int main() {
    string sentence;
    getline(cin, sentence);
    while (!sentence.empty()) {
        ll N = stoi(sentence);
        vector<string> patterns = vector<string>();
        for (ll i = 0; i < N; ++i) {
            string x;
            getline(cin, x);
            patterns.push_back(x);
        }
        string lookup;
        getline(cin, lookup);

        string_multimatching(patterns, lookup);

        getline(cin, sentence);
    }

    return 0;
}

/*
2
p
pup
Popup
2
You
peek a boo
you speek a bootiful language
4
anas
ana
an
a
bananananaspaj

 */