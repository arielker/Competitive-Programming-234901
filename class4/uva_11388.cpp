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

    int main() {
        ll t;
        cin >> t;
        for (ll i = 0; i < t; i++) {
            ll g, l;
            cin >> g >> l;
            if (l % g == 0)
                cout << g << " " << l << endl;
            else
                cout << "-1" << endl;
        }
        return 0;
    }