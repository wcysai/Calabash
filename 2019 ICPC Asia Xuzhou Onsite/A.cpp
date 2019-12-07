#pragma GCC optimize(3)
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

inline LL pref_xor(LL x) {
    switch (x & 3) {
    case 0 : return x;
    case 1 : return 1;
    case 2 : return x + 1;
    case 3 : return 0;
    }
}

inline LL compute(LL l, LL r) {
    return pref_xor(l - 1) ^ pref_xor(r);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        LL l, r, s; scanf("%lld%lld%lld", &l, &r, &s);
        LL ans = -1;
        if (r - l + 1 < 8) {
            for (LL L = l; L <= r; L++) 
                for (LL R = L; R <= r; R++) 
                    if (compute(L, R) <= s) ans = max(ans, R - L + 1);
        } else {
            for (LL L = l; L < l + 4; L++)
                for (LL R = r; R > r - 4; R--)
                    if (compute(L, R) <= s) ans = max(ans, R - L + 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}