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


ll mulmodn(ll a, ll b, ll n){
    ll res = 0;
    while(b){
        if(b & 1) res= (res+a) %n;
        a = (a*2)%n;
        b >>= 1;
    }
    return res;
}

ll powmodn(ll a, ll q, ll n){
    ll res = 1;
    while(q){
        if (q & 1) res = mulmodn(res,a,n);
        a = mulmodn(a,a,n);
        q >>= 1;
    }
    return res;
}

bool MR(ll n, int k=5){
    if(n==1 || n==4)
        return false;
    if(n==2 || n==3)
        return true;
    ll m = n - 1;
    int r = 0;
    while (m%2 == 0){
        m >>= 1;
        r+=1;
    }
    /* !!! Deterministic version for n<2^64 !!! */
//    int dtrm_set[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
//    for(ll a: dtrm_set){
//        if(a >= n) break;
    /* !!! End of deterministic version !!! */

    /* !!! Probablistic version !!! */
    while(k--){
        ll a = rand() % (n-4) + 2;
        /* !!! end of probablisitic version !!! */
        a = powmodn(a,m,n);
        if(a==1) continue;
        int i = r;
        while(i-- && a != n-1){
            a = mulmodn(a,a,n);
            if(a == 1) return false;
        }
        if(i == -1) return false;
    }
    return true;
}

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

vector<bool> sieve(int n){
    vector<bool> ps(n+1,true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 0; i <= sqrtn; ++i) {
        if(ps[i]){
            for (int j = i*i; j <= n; j+=i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

ll gcd(ll a, ll b){
    if(b==0)
    {
        return a;
    }
    return gcd(b, a%b);

}

ll f(ll a, ll c, ll n){
    return (mulmodn(a,a,n)+c)%n;
}

ll pollard_rho(ll n){
    if(n%2 == 0){
        return 2;
    }
    ll a = rand() % n;
    ll c = rand() % n;
    ll b = a;
    ll p;
    do{
        // a runs once
        a = f(a,c, n);
        // b runs twice as fast.
        b = f(f(b,c,n),c, n);
//        cout << a << " " << b << endl;
        p = gcd( abs(b-a) , n);
        if ( p > 1 && p != n)
            return p;
    } while (a!=b);

    return 0;

}

void Factorization(ll n, map<ll, ll> &fact) {
    // based on lecture
    if (MR(n)) {
        if (fact.find(n) == fact.end())
            fact[n] = 1;
        else
            fact[n]++;
    } else {
        ll p = 0;
        while(p == 0)
            p = pollard_rho(n);

        Factorization(n / p, fact);
        Factorization(p, fact);
    }
}

int main() {
    ll T;
    cin >> T;

    for (ll i = 0; i < T; ++i) {
        ll N;
        cin >> N;
        cout << N << " = ";

        map<ll, ll> factors;
        Factorization(N, factors);
        for (const auto &it: factors) {
            cout << it.first;
            if (2 <= it.second)
                cout << "^" << it.second;

            if (it == *(--factors.end()))
                cout << endl;
            else
                cout << " * ";
        }
    }

    return 0;
}

/*
3
60
36
10007

*/

