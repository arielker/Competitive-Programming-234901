#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
    int T = 0, N = 0, temp = 0;
    cin >> T;
    while (T--) {

        cin >> N;
        priority_queue<ll, vector<ll>, greater<>> heap;
        while (N--) {
            cin >> temp;
            heap.push(temp);
        }

        ll sum = 0, a, b;
        while (heap.size() > 1) {

            a = heap.top();
            heap.pop();

            b = heap.top();
            heap.pop();

            sum += a + b;
            heap.push(a + b);
        }
        cout << sum << endl;
    }
    return 0;
}