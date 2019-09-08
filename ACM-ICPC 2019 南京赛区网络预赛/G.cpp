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

int x[4][2];

LL C4(LL x) {
    __int128_t s = x;
    s *= (x - 1);
    s *= (x - 2);
    s *= (x - 3);
    s /= 24;
    return s;
}

LL subsolve(LL a) {
    if (a < 3) return 0; 
    return C4(a+1); 
}

// a + b + c <= d, (a, b, c, d > 0)
LL work(LL a, LL b, LL c, LL d) {
    return subsolve(d) - subsolve(d - a) - subsolve(d - b) - subsolve(d - c) + 
        subsolve(d - a - b) + subsolve(d - a - c) + subsolve(d - b - c) - subsolve(d - a - b - c);
}

LL calc(LL a, LL b, LL c, LL d) {
    LL ans = a * b * c * d;
    ans -= work(a, b, c, d) + work(b, c, d, a) + work(c, d, a, b) + work(d, a, b, c);
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        rep (i, 4) {
            rep (j ,2) scanf("%d", &x[i][j]);
            x[i][0]--;
        }
        LL ans = 
            + calc(x[0][0], x[1][0], x[2][0], x[3][0])
            - calc(x[0][0], x[1][0], x[2][0], x[3][1])
            - calc(x[0][0], x[1][0], x[2][1], x[3][0])
            + calc(x[0][0], x[1][0], x[2][1], x[3][1])

            - calc(x[0][0], x[1][1], x[2][0], x[3][0])
            + calc(x[0][0], x[1][1], x[2][0], x[3][1])
            + calc(x[0][0], x[1][1], x[2][1], x[3][0])
            - calc(x[0][0], x[1][1], x[2][1], x[3][1])

            - calc(x[0][1], x[1][0], x[2][0], x[3][0])
            + calc(x[0][1], x[1][0], x[2][0], x[3][1])
            + calc(x[0][1], x[1][0], x[2][1], x[3][0])
            - calc(x[0][1], x[1][0], x[2][1], x[3][1])
            
            + calc(x[0][1], x[1][1], x[2][0], x[3][0])
            - calc(x[0][1], x[1][1], x[2][0], x[3][1])
            - calc(x[0][1], x[1][1], x[2][1], x[3][0])
            + calc(x[0][1], x[1][1], x[2][1], x[3][1]);
        cout << ans << endl;
    }
    return 0;

}
