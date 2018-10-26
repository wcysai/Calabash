#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 0; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprint(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;

int n, k;
int tot;
int p[1000005];

int ptr, chosen;

bool ok() {
    return chosen * k >= ptr;
}

bool check(int d) {
    ptr = chosen = 0;
    while (chosen < n + n and ptr < tot - 1) {
        if (p[ptr + 1] - p[ptr] <= d) {
            chosen += 2;
            ptr += 2;
        } else {
            ptr++;
        }
        if (!ok()) return false;
    }
    return chosen == n + n;
}

int main() {
    scanf("%d%d", &n, &k); tot = n * k * 2;
    rep (i, tot) scanf("%d", p + i);
    sort(p, p + tot);
    int l = 0, r = 1'000'000'007;
    while (r > l) {
        int mid = (l + r) / 2;
        if (!check(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf("%d\n", l);
    return 0;
}
