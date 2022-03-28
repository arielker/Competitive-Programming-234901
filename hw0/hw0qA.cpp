#include <iostream>

using namespace std;

int main() {
    int W = 0;
    cin >> W;
    int N = 0;
    cin >> N;
    int area = 0;
    for (int i = 0; i < N; i++) {
        int w = 0, l = 0;
        cin >> w >> l;
        area += w * l;
    }
    cout << area / W << endl;
    return 0;
}
