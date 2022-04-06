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

int main(){
    int N;
    cin >> N;
    while (N--){
        int a,b;
        cin >> a >> b;
        if(a < b){
            cout << "<" << endl;
        } else if (a > b){
            cout << ">" << endl;
        } else {
            cout << "=" << endl;
        }
    }
    return 0;
}

/*
3
10 20
20 10
10 10

 */