#include <iostream>

using namespace std;

#define MAX_FOR_H 1000001

int BIT[MAX_FOR_H] = {0}, n;

void update(int x, int val) {
    for (; x <= n; x += x & -x) {
        BIT[x] += val;
    }
}

int query(int x) {
    int sum = 0;
    for (; x > 0; x -= x & -x) {
        sum += BIT[x];
    }
    return sum;
}

int main() {
    int K = 0;
    cin >> n >> K;
    while (K--) {
        char c;
        cin >> c;
        if (c == 'F') {
            int num = 0;
            cin >> num;
            update(num, (query(num) - query(num - 1) == 1) ? -1 : 1);
        } else {
            int start = 0, end = 0;
            cin >> start >> end;
            cout << query(end) - query(start - 1) << endl;
        }
    }
    return 0;
}