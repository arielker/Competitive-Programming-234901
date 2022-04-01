#include <iostream>
#include <set>

using namespace std;

int main () {
    int N = 0;
    set<int> palindromes;

    /// generate all 6-digit palindromic numbers:
    for (int i = 100; i < 1000; i++) {
        int j = (i % 10) * 100 + (i / 10 % 10) * 10 + (i / 100);
        palindromes.insert(i * 1000 + j);
    }

    cin >> N;
    while (N--) {
        int x;
        cin >> x;
        auto y = palindromes.lower_bound(x);
        int dist = *y - x;
        if (dist == 0) {
            cout << x << endl;
        }
        else {
            auto prev = palindromes.lower_bound(x);
            --prev;
            int dist2 = abs(*prev - x);
            cout << (dist < dist2 ? *y : *prev) << endl;
        }
    }
}
