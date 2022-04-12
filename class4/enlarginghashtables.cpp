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

bool isPrime(ll n){
    if(n<2)
        return false;
    ll sqrtn = sqrt(n);
    for (ll i = 2; i <= sqrtn; ++i) {
        if(n%i == 0){
            return false;
        }
    }
    return true;
}

int getNext(ll x){
    while (!isPrime(x)){
        x += 2;
    }
    return x;
}

int main() {
    ll x;
    while (cin >> x) {
        if(0 == x){
            return 0;
        }
        if(isPrime(x)){
            cout << getNext(1 + (x << 1)) << endl;
        } else {
            cout << getNext(1 + (x << 1)) << " (" << x << " is not prime)" <<endl;
        }
    }
    return 0;
}