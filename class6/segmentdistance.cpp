#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<string> string_tokenizer(const string &sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<ll> int_tokenizer(const string &sentence) {
    vector<ll> words;
    stringstream ss(sentence);
    ll word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}


double EPS = 0.00000001;

class point {
public:
    double x;
    double y;

    point(double x, double y) : x(x), y(y) {}

    point() = default;
};

class line {
public:
    double x1;
    double y1;
    double x2;
    double y2;

    line(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2),
                                                       y2(y2) {}
};


double dot(point c1, point c2) {
    return (c1.x * c2.x + c1.y * c2.y);
}

double calc_distance(line line1, line line2) {
    point p1 = point(line1.x2 - line1.x1, line1.y2 - line1.y1);
    point p2 = point(line2.x2 - line2.x1, line2.y2 - line2.y1);
    point p12 = point(line1.x1 - line2.x1, line1.y1 - line2.y1);

    double a = dot(p1, p1);
    double b = dot(p1, p2);
    double c = dot(p2, p2);
    double d = dot(p1, p12);
    double e = dot(p2, p12);
    double delta = a * c - b * b;

    double N1, D1 = delta, N2, D2 = delta;

    if (delta < EPS) {
        N2 = e;
        D2 = c;
        N1 = 0.0;
        D1 = 1.0;
    } else {
        N2 = (a * e - b * d);
        N1 = (b * e - c * d);
        if (N1 < 0.0) {
            N2 = e;
            D2 = c;
            N1 = 0.0;
        } else if (N1 > D1) {
            D2 = c;
            N1 = D1;
            N2 = e + b;
        }
    }

    if (N2 < 0.0) {
        if (-d < 0.0)
            N1 = 0.0;
        else if (-d > a)
            N1 = D1;
        else {
            D1 = a;
            N1 = -d;
        }
        N2 = 0.0;
    } else if (N2 > D2) {
        if ((-d + b) < 0.0)
            N1 = 0;
        else if ((-d + b) > a)
            N1 = D1;
        else {
            D1 = a;
            N1 = (-d + b);
        }
        N2 = D2;
    }

    double sc, tc;
    if (abs(N1) < EPS) sc = 0.0;
    else sc = N1 / D1;
    if (abs(N2) < EPS) tc = 0.0;
    else tc = N2 / D2;

    point dP = point();
    dP.x = p12.x + (sc * p1.x) - (tc * p2.x);
    dP.y = p12.y + (sc * p1.y) - (tc * p2.y);

    return sqrt(dot(dP, dP));
}

int main() {
    ll N;
    cin >> N;

    for (ll i = 0; i < N; ++i) {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        line l1 = line(x1, y1, x2, y2);
        line l2 = line(x3, y3, x4, y4);

        printf("%.2lf\n", calc_distance(l1, l2));
    }
    return 0;
}
