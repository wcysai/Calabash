#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//wzorcowka oparta na binsearchu po pochodnej

#include <iostream>
#include <algorithm>
using namespace std;

typedef long double LD;

int n;
const int N = 5000;
const int M = 1000;
LD w[N + 7];

LD potega(LD x, int k) {
    LD res = 1.0;
    while(k > 0) {
        if(k & 1) res *= x;
        x *= x;
        k /= 2;
    }
    return res;
}

LD znajdzp(LD x) { // (1-p)^(n - 1) = x
    LD p = 0.0;
    LD k = 1.0;
    for(int i = 0; i < 60 && p < k; ++i) {
        LD s = (p + k) * 0.5;
        if(potega(1.0 - s, n - 1) < x) k = s;
        else p = s;
    }
    return 0.5 * (p + k);
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> w[i];
    sort(w + 1, w + n + 1, greater <LD> ());

    LD p = 0.0;
    LD k = (double) M;

    for(int i = 0; i < 60 && p < k; ++i) {
        LD s = (p + k) * 0.5;
        LD sum = 0.0;
        for(int i = 1; i <= n; ++i) sum += znajdzp(s / w[i]);
        if(sum < 1.0) k = s;
        else p = s;
    }

    LD s = (p + k) * 0.5;
    LD wynik = 0.0;

    for(int i = 1; i <= n; ++i) {
        LD p = znajdzp(s / w[i]);
        wynik += w[i] * (1.0 - potega(1.0 - p, n));
    }

    wynik /= (double) n;
    cout.precision(15);
    cout << fixed;
    cout << wynik << endl;
    return 0;
}
