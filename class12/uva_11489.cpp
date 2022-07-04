#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

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



int main() {
    int testcases = 0;
    scanf("%d",&testcases);
    for (int j = 1; j <= testcases; ++j) {
        printf("Case %d: ",j);
        int sum = 0,check_sum=0;
        string num_input;
        cin >> num_input;
        vi digits_types_hist(3,0);
        for (const auto &i: num_input) {
            int d = i - '0';
            digits_types_hist[i%3]++;
        }
        check_sum+= 2*digits_types_hist[2];
        check_sum+= digits_types_hist[1];

        if(check_sum % 3 == 0){
            if(digits_types_hist[0] % 2 == 0){
                printf("T\n");
            } else{
                printf("S\n");
            }
            continue;
        }
        if(check_sum % 3 == 1){
            if(digits_types_hist[1] == 0){
                printf("T\n");
            } else{
                if(digits_types_hist[0] % 2 == 0){
                    printf("S\n");
                } else{
                    printf("T\n");
                }
            }
            continue;
        }
        if(check_sum % 3 == 2){
            if(digits_types_hist[2] == 0){
                printf("T\n");
            } else{
                if(digits_types_hist[0] % 2 == 0){
                    printf("S\n");
                } else{
                    printf("T\n");
                }
            }
            continue;
        }
    }
}
/*
3
4
33
771

 */