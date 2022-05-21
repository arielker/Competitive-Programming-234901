#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;
#define EPS 1e-6

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

vector<bool> bfs(const vvi &g, int s) {
    queue<int> q;
    q.push(s);
    vector<bool> visible(g.size(), false);
    visible[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: g[u])
            if (!visible[v]) {
                visible[v] = true;
                q.push(v);
            }
    }
    return visible;
}

double calc_dist(pair<double, double> a, pair<double, double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second));
}

bool can(double dist, ll N, double X, double Y,
         vector<pair<double, double>> people) {
    vvi graph(N + 4, vector<int>());

    ll D = N;
    ll U = N + 1;
    ll L = N + 2;
    ll R = N + 3;

    // create the graph
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // check if the two cycles intersect
            if (calc_dist(people[i], people[j]) <= dist * 2) {
                graph[j].push_back(i);
                graph[i].push_back(j);
            }
        }

        // add sides
        if (people[i].first - dist <= 0) {
            graph[L].push_back(i);
            graph[i].push_back(L);
        }
        if (people[i].first + dist >= X) {
            graph[R].push_back(i);
            graph[i].push_back(R);
        }
        if (people[i].second - dist <= 0) {
            graph[D].push_back(i);
            graph[i].push_back(D);
        }
        if (people[i].second + dist >= Y) {
            graph[U].push_back(i);
            graph[i].push_back(U);
        }
    }

    // check for wall that interfere
    vector<bool> visible = bfs(graph, U);
    if (visible[D] || visible[R])
        return true;
    else {
        visible = bfs(graph, L);
        if (visible[D] || visible[R])
            return true;
    }

    return false;
}

int main() {
    double X, Y;
    cin >> X >> Y;

    ll N;
    cin >> N;

    vector<pair<double, double>> people = vector<pair<double, double>>();
    for (ll i = 0; i < N; ++i) {
        double x_i, y_i;
        cin >> x_i >> y_i;
        people.push_back(pair<double, double>(x_i, y_i));
    }

    double lo = 0.0, hi =
            calc_dist(pair<double, double>(0, 0), pair<double, double>(X, Y)) +
            1, mid = 0.0, ans = 0.0;
    while (fabs(hi - lo) > EPS) {
        mid = (lo + hi) / 2.0;
        if (can(mid, N, X, Y, people)) {
            hi = mid;
            ans = hi;
        } else lo = mid;
    }
    printf("%.6lf\n", ans);

    return 0;
}
