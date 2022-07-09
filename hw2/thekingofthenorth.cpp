#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

typedef long long ll;

// bool
typedef pair<bool, bool> bb;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<bb> vbb;
typedef vector<vbb> vvbb;

// int
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

// double
typedef pair<double, double> dd;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<dd> vdd;
typedef vector<vdd> vvdd;

// ll
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;

// set
typedef set<int> si;
typedef set<ll> sll;
typedef set<vii> svii;
typedef vector<si> vsi;


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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// taken from https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/

// C++ implementation of Dinic's Algorithm
#include<bits/stdc++.h>

using namespace std;

// A structure to represent a edge between
// two vertex
struct Edge {
    ll v; // Vertex v (or "to" vertex)
    // of a directed edge u-v. "From"
    // vertex u can be obtained using
    // index in adjacent array.

    ll flow; // flow of data in edge

    ll capacity; // capacity

    ll rev; // To store index of reverse
    // edge in adjacency list so that
    // we can quickly find it.
};

// Residual Graph
class Graph {
    ll V; // number of vertex
    ll *level; // stores level of a node
    vector<Edge> *adj;
public :
    Graph(ll V) {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new ll[V];
    }

    // add edge to the graph
    void addEdge(ll u, ll v, ll C) {
        // Forward edge : 0 flow and C capacity
        Edge a{v, 0, C, (ll) adj[v].size()};

        // Back edge : 0 flow and 0 capacity
        Edge b{u, 0, 0, (ll) adj[u].size()};

        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    bool BFS(ll s, ll t);

    ll sendFlow(ll s, ll flow, ll t, ll ptr[]);

    ll DinicMaxflow(ll s, ll t);
};

// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool Graph::BFS(ll s, ll t) {
    for (ll i = 0; i < V; i++)
        level[i] = -1;

    level[s] = 0; // Level of source vertex

    // Create a queue, enqueue source vertex
    // and mark source vertex as visited here
    // level[] array works as visited array also.
    list<ll> q;
    q.push_back(s);

    vector<Edge>::iterator i;
    while (!q.empty()) {
        ll u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge &e = *i;
            if (level[e.v] < 0 && e.flow < e.capacity) {
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;

                q.push_back(e.v);
            }
        }
    }

    // IF we can not reach to the sink we
    // return false else true
    return level[t] < 0 ? false : true;
}

// A DFS based function to send flow after BFS has
// figured out that there is a possible flow and
// constructed levels. This function called multiple
// times for a single call of BFS.
// flow : Current flow send by parent function call
// start[] : To keep track of next edge to be explored.
//     start[i] stores count of edges explored
//     from i.
// u : Current vertex
// t : Sink
ll Graph::sendFlow(ll u, ll flow, ll t, ll start[]) {
    // Sink reached
    if (u == t)
        return flow;

    // Traverse all adjacent edges one -by - one.
    for (; start[u] < adj[u].size(); start[u]++) {
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.capacity) {
            // find minimum flow from u to t
            ll curr_flow = min(flow, e.capacity - e.flow);

            ll temp_flow = sendFlow(e.v, curr_flow, t, start);

            // flow is greater than zero
            if (temp_flow > 0) {
                // add flow to current edge
                e.flow += temp_flow;

                // subtract flow from reverse edge
                // of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

// Returns maximum flow in graph
ll Graph::DinicMaxflow(ll s, ll t) {
    // Corner case
    if (s == t)
        return -1;

    ll total = 0; // Initialize result

    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t) == true) {
        // store how many edges are visited
        // from V { 0 to V }
        ll *start = new ll[V + 1]{0};

        // while flow is not zero in graph from S to D
        while (ll flow = sendFlow(s, INT_MAX, t, start))

            // Add path flow to overall flow
            total += flow;
    }

    // return maximum flow
    return total;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int INF = 1e9;

ll R, C;
ll s;

ll get_in_node_id(ll x, ll y) {
    return y + x * C;
}

ll get_out_node_id(ll x, ll y) {
    return y + x * C + (R * C);
}

void initialize(Graph &g){
    // base cases border
    for (ll x = 0; x < R; ++x) {
        g.addEdge(s, get_out_node_id(x, 0), INF);
        g.addEdge(s, get_out_node_id(x, C - 1), INF);
    }
    for (ll y = 0; y < C; ++y) {
        g.addEdge(s, get_out_node_id(0, y), INF);
        g.addEdge(s, get_out_node_id(R - 1, y), INF);
    }

    // inside cases
    for (ll x = 0; x < R; ++x) {
        for (ll y = 0; y < C; ++y) {
            ll bannermen_required; // C
            cin >> bannermen_required;

            // from in vertix to out vertix
            ll u = get_in_node_id(x, y);
            ll v = get_out_node_id(x, y);
            g.addEdge(u, v, bannermen_required);

            // move only sideways
            for (int delta_x = -1; delta_x <= 1; ++delta_x) {
                for (int delta_y = -1; delta_y <= 1; ++delta_y) {
                    ll new_x = x + delta_x;
                    ll new_y = y + delta_y;

                    if (abs(delta_x + delta_y) != 1) continue;
                    if (new_x < 0 || new_x >= R || new_y < 0 || new_y >= C) continue;

                    ll w = get_in_node_id(new_x, new_y);
                    g.addEdge(v, w, bannermen_required);
                }
            }
        }
    }

}

int main() {
    cin >> R >> C;

    s = R * C * 2;
    Graph g(s + 1);

    initialize(g);

    ll r, c;
    cin >> r >> c;
    cout << g.DinicMaxflow(s, get_out_node_id(r, c)) << endl;

    return 0;
}
