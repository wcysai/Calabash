#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

typedef complex<double> point;
const double PI = acos(-1.0);

char process() {
    string str;
    double a, l;
    cin >> str >> a >> l;
    point init, dist;
    if (str == "BC") {
        init = point(0.0, 0.0);
        dist = polar(1.0, (60.0 - a) / 180.0 * PI);
    } else if (str == "CD") {
        init = point(2.0, 0.0);
        dist = polar(1.0, (180.0 - a) / 180.0 * PI);
    } else if (str == "DB") {
        init = point(1.0, sqrt(3.0));
        _debug("%f", -60.0 - a);
        dist = polar(1.0, (-60.0 - a) / 180.0 * PI);
    } else {
        assert(0);
    }
    _debug("init: %f %f", init.real(), init.imag());
    _debug("vec: %f %f", dist.real(), dist.imag());
    init += dist * l;
    _debug("raw: %f %f", init.real(), init.imag());
    double dy = init.imag() * 2.0 / sqrt(3.0), dx = init.real() - dy / 2.0;
    // double dx = init.real(), dy = init.real() / 2.0 + init.imag() * sqrt(3.0) / 2.0;
    while (dx < 0.0) dx += 2.0;
    while (dx > 2.0) dx -= 2.0;
    while (dy < 0.0) dy += 2.0;
    while (dy > 2.0) dy -= 2.0;
    _debug("trans: %f %f", dx, dy);
    char ch;
    if (dx < 1.0) {
        if (dy < 1.0) { // III
            ch = (dy < 1.0 - dx) ? 'C' : 'A';
        } else {        // II
            ch = (dy < 2.0 - dx) ? 'D' : 'B';
        }
    } else {
        if (dy < 1.0) { // IV
            ch = (dy < 2.0 - dx) ? 'B' : 'D';
        } else {        // I
            ch = (dy < 3.0 - dx) ? 'A' : 'C';
        }
    }
    _debug("%c", ch);
    return ch;
}

int main() {
    puts(process() == process() ? "YES" : "NO");
    return 0;
}
