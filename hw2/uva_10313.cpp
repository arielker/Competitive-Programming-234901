#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;
#define NO_VISIT -1

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
vvll mat_rec(301, vll(301,0));

void coins_opt_preprocess(){
    mat_rec[0][0] = 1;
    for (int total = 0; total <= 300; ++total) {
        for (int coins = 1; coins <= 300; ++coins) {
            if(total == 0){
                mat_rec[0][coins] = 1;//init phase
                continue;
            }
            ll no_last = mat_rec[total][coins - 1];//last good option
            ll yes_last = 0;
            if(total >= coins){//The second option only when the total is bigger, there is another valid option
                yes_last = mat_rec[total - coins][coins];
            }
            mat_rec[total][coins] = no_last + yes_last;//sum of the two options, and their "ancestors" options
        }
    }
}

void line_parsing(string num_line, vll& out){
    int count = 1;
    while (num_line.find(' ')!=string::npos){
        count++;
    }
    out.resize(count);
    //To much time complexity O(2n), string stream is a better option
}
//Avoiding out-of-bounds exception duw to some evil!!!!! tests
void validation(int &N,int& up,int& down){
    if (300 < down){
        down = 300;
    }
    if(down < 1){
        down = 1;
    }
    if (300 < up){
        up = 300;
    }
    if(up < 0){
        up = 0;
    }
    if (300 < N){
        N = 300;
    }
    if(N < 0){
        N = 0;
    }
}

int main() {
    coins_opt_preprocess();// preprocessing and filling the whole option
    string num_line;
    while (getline(cin,num_line)){
        stringstream stream_num(num_line); //O(n)
        int N = NO_VISIT;
        int down = NO_VISIT;
        int up = NO_VISIT;
        stream_num >> N >> down>> up;//line_parsing took too much time
        //Only one way - fixed question
        if(N <= NO_VISIT){ // no line or evil line
            break;
        }
        if(N == 0) { //0 dollars, 1 option of nothing
            printf("1\n");
        } else{//According to the question bounding requirements
            if (up < 0 && down < 0) {
                down = 1;
                up = 300;
            } else {
                if (up < 0) {
                    up = down;
                    down = 1;
                }
            }
            validation(N,up,down);//out of bound avoidance
            printf("%lu\n", mat_rec[N][up]-mat_rec[N][down-1]);
        }
    }

}
/*
6
6
6 3
6 2 5
6 1 6
 */