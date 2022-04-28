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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <list>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// typedef vector<int> vi;
typedef pair<int, int> pii;



// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>


typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;


// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: is g a DAG (return value), a topological ordering of g (order).
// comment: order is valid only if g is a DAG.
// time: O(V+E).
bool topological_sort(const vvi &g, vi &order) {
    // compute indegree of all nodes
    vi indegree(g.size(), 0);
    for (int v = 0; v < g.size(); v++) for (int u: g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v = 0; v < g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i = 0; i < order.size(); i++)
        for (int u: g[order[i]]) {
            indegree[u]--;
            if (indegree[u] == 0) order.push_back(u);
        }
    return order.size() == g.size();
}


int char_to_int(char c) {
    return c - 'A';
}

char int_to_char(int n) {
    return n + 'A';
}

int main() {
    int hist[26] = {0};
    set<pair<char, char>> before_set;
    vector<string> dict;
    string next;
    while (cin >> next) {
        if (next == "#") break;
        dict.push_back(next);
    }

    for (auto &s: dict) {
        for (size_t i = 0; i < s.size(); i++) hist[char_to_int(s[i])] = 1;
    }


    vvi g(26, vector<int>());
    for (size_t i = 0; i < dict.size(); i++) {
        string &curr_str = dict[i];
        // cout << "curr_str: " << curr_str << endl;
        for (size_t size = 0; size < curr_str.size(); size++) {
            string curr_sub_str = curr_str.substr(0, size);
            for (size_t j = i + 1; j < dict.size(); j++) {
                // if (j == i) continue;
                string &check_str = dict[j];
                if (check_str.size() == size) continue;
                string check_sub_str = check_str.substr(0, size);
                if (check_sub_str != curr_sub_str) continue;
                if (curr_str[size] == check_str[size]) continue;
                // cout << "strings:" << endl;
                // cout << curr_sub_str << " " << check_sub_str << endl;
                // cout << "before:" << endl;
                // cout << curr_str[size] << " " << check_str[size] << endl;
                before_set.insert({curr_str[size], check_str[size]});
            }
        }
    }
    for (auto &t: before_set) {
        // v -> u
        int v = char_to_int(t.first);
        int u = char_to_int(t.second);
        g[v].push_back(u);
    }

    vi order;
    topological_sort(g, order);

    for (auto &i: order) {
        if (hist[i] == 1) cout << int_to_char(i);
        // cout << int_to_char(i);
    }
    cout << endl;

    return 0;
}