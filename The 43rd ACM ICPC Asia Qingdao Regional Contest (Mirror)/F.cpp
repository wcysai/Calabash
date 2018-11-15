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

int n, k, lastans;
int depth, lead, mult;

int ans[1024][1024];
int cur[1024];

void yield() {
    if (cur[1] <= lastans) return;
    lastans++;

    for (int i = 0; i < (1 << depth); i += 2) {
        ans[lastans][cur[i]] = cur[i+1];
        ans[lastans][cur[i+1]] = cur[i];
    }

    int base = (1 << depth);
    while (base < n) {
        for (int i = 0; i < mult; i++)
            ans[lastans][base + i] = ans[lastans][i] + base;
        base += mult;
    }


    // rep (i, 1 << depth) cout << cur[i] << ' '; cout << endl;
}

void recursive_construct(int dep) {
    // cout << __func__ << " :" << dep << endl;
    if (dep == 1) yield();
    else {
        int step = 1 << (dep - 2);
        recursive_construct(dep - 1);
        for (int i = 0; i < (1 << depth); i += (1 << dep))
            rep (cnt, step) swap(cur[i + step + cnt], cur[i + step * 2 + cnt]);
        recursive_construct(dep - 1);
        for (int i = 0; i < (1 << depth); i += (1 << dep))
            rep (cnt, step) swap(cur[i + step + cnt], cur[i + step * 3 + cnt]);
        recursive_construct(dep - 1);
        for (int i = 0; i < (1 << depth); i += (1 << dep))
            rep (cnt, step) swap(cur[i + step + cnt], cur[i + step * 3 + cnt]);
        for (int i = 0; i < (1 << depth); i += (1 << dep))
            rep (cnt, step) swap(cur[i + step + cnt], cur[i + step * 2 + cnt]);

    };
}

bool solver() {
    depth = __builtin_ctz(n);
    mult = 1 << depth;
    lead = n >> depth;
    if (k >= (1 << depth)) return false;
    recursive_construct(depth);
    return true;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        lastans = 0;
        scanf("%d%d", &n, &k);
        rep (i, n) cur[i] = i;
        if (n & 1 || !solver()) {
            puts("Impossible");
        } else {
            Rep (i, k)
                rep (j, n) printf("%d%c", ans[i][j] + 1, j != n - 1 ? ' ' : '\n');
        }
    }
    return 0;
}