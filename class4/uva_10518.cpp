#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <string>
#include "vector"
#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <bitset>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;


void Calc_fibNum(vector<int> base_nums[], int b) {
    base_nums[b].push_back(1);
    base_nums[b].push_back(1);
    do {
        int first = *(base_nums[b].end() - 1);
        int sec = *(base_nums[b].end() - 2);
        base_nums[b].push_back((first + sec + 1) % b); //according to class solution
    } while (*(base_nums[b].end() - 1) != 1 || *(base_nums[b].end() - 2) != 1);
    base_nums[b].pop_back();
    base_nums[b].pop_back();

}

void ex_2_last_comp() {
    vector<int> base_nums[10100];//bigger than the requested size- but comfort to check
    int test_num = 1;
    long long n = 0, b = 0;
    scanf("%llu%llu", &n, &b);
    while (n != 0 || b != 0) {
        if (base_nums[b].empty()) {
            Calc_fibNum(base_nums, b);
        }
        printf("Case %d: %llu %llu %d\n", test_num, n, b, base_nums[b][n % base_nums[b].size()]);
        test_num++;
        scanf("%llu%llu", &n, &b);
    }
}

int main() {
    ex_2_last_comp();
    return 0;
}
