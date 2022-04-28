#include <iostream>
#include <vector>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<string> string_tokenizer(const string &sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<ll> int_tokenizer(const string &sentence) {
    vector<ll> words;
    stringstream ss(sentence);
    ll word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}


typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

void Dijkstra(const vvii &g, int s, vi &dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top();
        q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u])
            continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next: g[u]) {
            int v = next.first, w = next.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    string sentence;

    while (true) {
        getline(cin, sentence);
        vector<ll> params = int_tokenizer(sentence);
        ll n = params[0];
        ll m = params[1];
        ll q = params[2];
        ll s = params[3];

        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }

        vvii g = vvii(n);
        for (ll i = 0; i < m; ++i) {
            getline(cin, sentence);
            vector<ll> edge = int_tokenizer(sentence);

            g[edge[0]].push_back(ii(edge[1], edge[2]));
//            g[edge[1]].push_back(ii(edge[0], edge[2]));
        }

        vi d = vi(n);
        Dijkstra(g, s, d);

        for (ll i = 0; i < q; ++i) {
            getline(cin, sentence);
            ll query = stoi(sentence);
            if (d[query] == INF) {
                cout << "Impossible" << endl;
            } else {
                cout << d[query] << endl;
            };
        };

        cout << endl;
    }

    return 0;
}

/*
4 3 4 0
0 1 2
1 2 2
3 0 2
0
1
2
3
2 1 1 0
0 1 100
1
0 0 0 0

 */
