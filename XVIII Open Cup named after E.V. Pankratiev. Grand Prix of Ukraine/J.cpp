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

int n, m;
unsigned s;

unsigned getNext() {
    s = s xor (s << 13);
    s = s xor (s >> 17);
    s = s xor (s << 5);
    return s;
}

int eid[10000005];
LL min_cost[10000005];
unsigned res[10000005 / 32];

void generate() {
    int u, v; LL w;
    for (int i = 0; i < m; i++) {
        u = getNext() % n;
        v = getNext() % n;
        w = getNext() / 4;
        w = w * getNext();
        if (u == v) continue;
        if (w < min_cost[u]) {
            min_cost[u] = w;
            eid[u] = i;
        }
        if (w < min_cost[v]) {
            min_cost[v] = w;
            eid[v] = i;
        }
    }
}

void setbit(int x) {
    res[x / 32] |= (1u << (x & 31));
}

int main() {
    cin >> n >> m >> s;
    rep (i, n) {
        eid[i] = -1;
        min_cost[i] = LLONG_MAX;
    }
    generate();
    rep (i, n) if (eid[i] >= 0) setbit(eid[i]);
    for (int i = 0; i < (m + 31) / 32; i++) printf("%u ", res[i]);
    return 0;
}

// 10000000 10000000 37
// 4 7 47
