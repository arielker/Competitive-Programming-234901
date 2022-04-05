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

void print(int a, int b, int c, int d){
    cout << "Cube = " << a << ", Triple = (" << b << "," << c << "," << d << ")" << endl;
}

int main(){
    for (int a = 6; a <= 200; ++a) {
        int a_t = a*a*a;
        for (int b = 2; b < 200; ++b) {
            int b_t = b*b*b;
            for (int c = b; c < 200; ++c) {
                int c_t = c*c*c;
                for (int d = c; d < 200; ++d) {
                    int d_t = d*d*d;
                    if (d_t + c_t + b_t == a_t){
                        print(a,b,c,d);
                    }
                }
            }
        }
    }
    return 0;
}