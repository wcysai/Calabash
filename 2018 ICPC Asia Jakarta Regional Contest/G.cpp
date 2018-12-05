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
bool done[512][512];
int deg[512];
vector<pair<short, short>> heap[1024];

int ptr, rem;

void pedge(int u, int v);

void yedge(int u, int v) {
    if (done[u][v]) return;
    done[u][v] = true;
    deg[u]++; deg[v]++;
    rem--;
    rep (i, n) {
        pedge(i, u);
        pedge(i, v);
    }
}

void pedge(int u, int v) {
    if (u == v) return;
    if (u > v) swap(u, v);
    if (deg[u] + deg[v] >= ptr) {
        yedge(u, v);
    } else {
        heap[deg[u] + deg[v]].emplace_back(u, v);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        u--; v--;
        done[u][v] = true;
        deg[u]++; deg[v]++;
    }
    rem = n * (n - 1) / 2 - m;
    rep (i, n)
        rep (j, i)
            if (!done[j][i]) heap[deg[i] + deg[j]].emplace_back(j, i);
    ptr = n + n;
    while (rem) {
        while (heap[ptr].empty()) ptr--;
        int u, v; tie(u, v) = heap[ptr].back(); heap[ptr].pop_back();
        yedge(u, v);
    }
    cout << ptr << endl;
    return 0;
}
