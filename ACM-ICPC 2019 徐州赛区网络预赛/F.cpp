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

namespace fio {
    char buf[1 << 25], *ptr = buf;
    void init() { fread(buf, 1, sizeof buf, stdin); }
    unsigned readint() {
        unsigned ret = 0;
        while (!isdigit(*ptr)) ptr++;
        while (isdigit(*ptr)) ret = ret * 10 + (*ptr - '0'), ptr++;
        return ret;
    }
}

int n;
LL w[1 << 20];
int fa[1 << 20], dep[1 << 20], hc[1 << 20];
int qid[1 << 20], qsz[1 << 20];
LL ans[8192];
vector<int> adj[1 << 20];
 // remove child, dis, query
vector<pair<int, int>> tags[1 << 20];

void dfs(int u, int p) {
    fa[u] = p;
    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
        dep[u] = max(dep[u], dep[v] + 1);
        if (hc[u] == 0 or dep[hc[u]] < dep[v]) hc[u] = v;
    }
    if (hc[u] == 0) {
        qid[u] = u;
        qsz[u] = 1;
    } else {
        qid[u] = qid[hc[u]];
        qsz[qid[u]]++;
    }
}

struct Deque {
    LL *l, *r;
    Deque() : l(nullptr), r(nullptr) {};
    Deque(int sz) {
        LL* arr = new LL[sz + 2];
        l = r = arr + sz + 2;
    }
    void push_front(LL x) { *(--l) = x; }
    size_t size() { return r - l; }
    LL& operator [] (size_t id) { return l[id]; }
    LL& front() { return *l; }
    LL operator && (int k) {
        if (k < 0) return 0;
        LL tot = front();
        if (size() <= k + 1) return tot;
        return tot - l[k+1];
    }
};


/*
 * extract sum no more than k
 */
 /*
LL operator && (const Deque &q, int k) {
    LL tot = q.front();
    if (q.size() <= k + 1) return tot;
    return tot - q[k + 1];
}
*/
/*
 * deque<LL>[k] means sum of weights of child with dis >= k
 */
Deque work(int u, int p) {
    Deque x;
    if (hc[u]) {
        x = work(hc[u], u);
    } else {
        x = Deque(qsz[u]);
        x.push_front(0);
    }
    x[0] += w[u];
    auto it = tags[u].begin();
    for (int v : adj[u]) if (v != p and v != hc[u]) {
        Deque xx = work(v, u);
        rep (i, xx.size()) x[i] += xx[i];
    }
    for (auto p : tags[u]) {
        int k, q; tie(k, q) = p;
        if (q > 0) ans[q] += x && k; else ans[-q] -= x && k;
    }
    x.push_front(x.front()); // extend
    return move(x);
}

int main() {
    using fio::readint;
    fio::init();
    n = readint();
    Rep (i, n) w[i] = readint(); //scanf("%lld", w + i);
    for (int i = 1; i < n; i++) {
        int u = readint(), v = readint();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    int q = readint();
    Rep (i, q) {
        int v = readint(), u = 0, k = readint();
        while (v and k >= 0) {
            tags[v].emplace_back(k, i);
            if (u) tags[u].emplace_back(k-1, -i);
            k--;
            u = v; v = fa[u];
        }
    }
    work(1, 0);
    Rep (i, q) printf("%lld\n", ans[i]);
    return 0;
}
