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

using namespace std;

bool compare(char a, char b) {
    char first = tolower(a);
    char second = tolower(b);
    return first != second ? first < second : a < b;
}

int main(){
    ll num = 0;
    cin >> num;
    string w;
    vector<string> permutations;
    while (num){
        if(!(cin >> w)){
            break;
        }
        sort(w.begin(), w.end(), compare);
        cout << w << endl;
        while (next_permutation(w.begin(), w.end(), compare)){
            cout << w << endl;
        }
        num--;
    }
    return 0;
}