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

int rec(const char *a, const char *b, int right) {
    if (*a == '\0') {
        if (right == 0) {
            return 0;
        }
        return -10000000;
    }
    int temp1 = 0, temp2 = 0;
    if (*a == *b) {
        temp1 = 1 + rec(a + 1, b + 1, right - 1);//right
        temp2 = rec(a + 1, b + 1, right);//wrong
    } else {
        temp1 = rec(a + 1, b + 1, right - 1);//right
        temp2 = 1 + rec(a + 1, b + 1, right);//wrong
    }
    if (temp1 > temp2) {
        return temp1;
    }
    return temp2;
}

void exA() {
    string r;
    int right = 0;
    getline(cin, r);
    right = atoi(r.c_str());
    string test_str = "";
    for (int i = 1; i <= right; i++) {
        test_str += "1";
    }
    string first, second;
    getline(cin, first);
    getline(cin, second);
    //printf("%d",rec(first.c_str(),second.c_str(),right));
    for (int i = 1; i <= first.size() - right; i++) {
        test_str += "0";
    }
    std::sort(test_str.begin(), test_str.end());
    do {
        std::cout << test_str << '\n';

    } while (std::next_permutation(test_str.begin(), test_str.end()));
    //printf("%s",test_str.c_str());

}

long long
exB_helper(int fir, int sec, bool prob, long long rec_matrix[66][66][2]) {
    if (rec_matrix[fir][sec][prob] != -1) {
        return rec_matrix[fir][sec][prob];
    }
    if (!prob) {
        rec_matrix[fir][sec][prob] =
                exB_helper(fir - 1, sec, false, rec_matrix) +
                exB_helper(fir - 1, sec, true, rec_matrix);
    } else {
        rec_matrix[fir][sec][prob] =
                exB_helper(fir - 1, sec, false, rec_matrix) +
                exB_helper(fir - 1, sec - 1, true, rec_matrix);
    }
    return rec_matrix[fir][sec][prob];
}

void EX_B() {
    long long rec_matrix[66][66][2];
    for (int i = 0; i <= 65; i++) {
        for (int j = 0; j <= 65; j++) {
            rec_matrix[i][j][0] = -1;
            rec_matrix[i][j][1] = -1;
        }
    }
    for (int fir = 1; fir <= 65; fir++) {
        if (fir == 1) {
            rec_matrix[fir][0][0] = 2;
            rec_matrix[fir][1][0] = 0;
            rec_matrix[fir][0][1] = rec_matrix[fir][1][1] = 1;
            for (int sec = 2; sec <= 65; sec++) {
                rec_matrix[fir][sec][1] = rec_matrix[fir][sec][0] = 0;
            }
        } else {
            rec_matrix[fir][0][1] = rec_matrix[fir - 1][0][0];
            rec_matrix[fir][0][0] =
                    rec_matrix[fir - 1][0][0] + rec_matrix[fir - 1][0][1];
        }
    }
    int num_a, num_b;
    scanf("%d", &num_a);
    scanf("%d", &num_b);
    while (num_a >= 0 || num_b >= 0) {
        printf("%llu\n", exB_helper(num_a, num_b, true, rec_matrix));
        scanf("%d", &num_a);
        scanf("%d", &num_b);
    }
}

int main() {
    EX_B();
    return 0;
}
