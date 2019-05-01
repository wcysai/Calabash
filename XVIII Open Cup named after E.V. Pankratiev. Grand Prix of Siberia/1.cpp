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

int x11, y11, x12, y12;
int x21, y21, x22, y22;

bool rectinrect(int x11, int y11, int x12, int y12,
        int x21, int y21, int x22, int y22) {
    return x11 >= x21 and y11 >= y21 and x12 <= x22 and y12 <= y22;
}

bool disjoint() {
    return x11 > x22 || x12 < x21 || y11 > y22 || y12 < y21;
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> x11 >> y11 >> x12 >> y12;
        cin >> x21 >> y21 >> x22 >> y22;
        if (rectinrect(x11, y11, x12, y12, x21, y21, x22, y22)) {
            puts("A in B");
        } else if (rectinrect(x21, y21, x22, y22, x11, y11, x12, y12)) {
            puts("B in A");
        } else if (disjoint()) {
            puts("Separate");
        } else {
            puts("Intersect");
        }
    }
    return 0;
}
