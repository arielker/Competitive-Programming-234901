#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;
int cache2[33][1000][1000]; // I tried to use vector (we are on cpp after all), but I think the clearing would take some extra time
#define NO_VISIT -1 // cache principle, option not calculated yet

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
typedef vector<vvi> vvvi;
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

int candies_for_all(vi cand, int s_cand, int n, int w_fir, int w_sec){
    if(n == 0){ // All candies were divided
        int third = s_cand - (w_fir + w_sec); // could be inffered from the other weights, good for complexity
        int max = std::max(std::max(w_fir,w_sec),third);
        int min = std::min(std::min(w_fir,w_sec),third);
        return max-min;//calc min max diff
    }
    if(cache2[n][w_fir][w_sec] != NO_VISIT){//cache classic usage- avoid redundant calls
        return cache2[n][w_fir][w_sec];
    }
    int opt1,opt2,opt3;

    opt1 = candies_for_all(cand,s_cand,n-1, cand[n]+w_fir,w_sec);//kid1 get one
    opt2 = candies_for_all(cand,s_cand,n-1, w_fir, cand[n]+w_sec);//kid2 get one
    opt3 = candies_for_all(cand,s_cand,n-1, w_fir,w_sec);//kid3 get one
    cache2[n][w_fir][w_sec] = std::min(std::min(opt1,opt2),opt3);//minimum diff from the minimums
    return cache2[n][w_fir][w_sec]; // the best local division is taken
}

int main() {
    vi candies(33,0);// Candies weights container

    //high complexity
    //vvvi cache(33,vvi(1000,vi(1000,0)));
    //memset(&cache,-2,sizeof(cache));

    //crashes on some computers
    //int cache2[33][1000][1000];
    //memset(cache2,-1,sizeof(cache2));
    int test_num = 0;
    int num_cand = 0, sum_cand = 0;
    scanf("%d",&test_num);
    for (int i = 0; i < test_num; ++i) {
        sum_cand = 0;
        num_cand = 0;
        scanf("%d",&num_cand); // candies actual number (not the given maximum)
        for (int j = 1; j <= num_cand; ++j) {
            scanf("%d",&candies[j]);
            sum_cand+=candies[j];//sum the total weight (in order to infer eventually the third kid weight)
        }
        memset(cache2,-1,sizeof(cache2));//clear caching between tests (The most important rule in this course! :))
        printf("Case %d: %d\n",i+1, candies_for_all(candies,sum_cand,num_cand,0,0));
    }


}
/*
4
3
2 2 2
2
3 4
6
13 9 7 7 1 7
8
3 3 3 3 3 3 5 5
 */