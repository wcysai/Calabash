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

const LL mod1 = 1000000007, mod2 = mod1 - 1;

char str[100005];

LL powmod(LL b, LL e, LL m) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", str);
        LL x = 0;
        for (int i = 0; str[i]; i++) {
            x = x * 10 + str[i] - '0';
            x %= mod2;
        }
        printf("%d\n", (int)powmod(2, x + mod2 - 1, mod1));
    }
    return 0;
}
