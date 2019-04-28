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

int n, m, s, t;
vector<pair<int, int>> out[200005], in[200005];
int d[200005], rcnt[200005];
bool done[200005];

inline int sadd(int x, int y) {
    int res;
    if (__builtin_add_overflow(x, y, &res)) res = INT_MAX;
    return res;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    fill(range(d), INT_MAX);
    rep (i, m) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        out[2*u].emplace_back(2 * v + 1, w);
        out[2*u+1].emplace_back(2 * v, w);
        rcnt[2*u+1]++; rcnt[2*u]++;
        in[2*v].emplace_back(2*u+1, w);
        in[2*v+1].emplace_back(2*u, w);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    d[2*t] = d[2*t+1] = 0;
    q.emplace(0, 2*t); q.emplace(0, 2*t+1);
    while (q.size()) {
        int u = q.top().second;
        q.pop();
        if (done[u]) continue; done[u] = true;
        if (u & 1) {
            d[u] = 0;
            for (auto e : out[u]) {
                int v, w; tie(v, w) = e;
                d[u] = max(d[u], sadd(d[v], w));
            }
            for (auto e : in[u]) {
                int v, w; tie(v, w) = e;
                d[v] = min(d[v], sadd(d[u], w));
                q.emplace(d[v], v);
            }
        } else {
            for (auto e : in[u]) {
                int v, w; tie(v, w) = e;
                if (--rcnt[v] == 0)
                    q.emplace(0, v);
                
            }
        }
    }
    if (d[2*s+1] == INT_MAX) {
        puts("infinity");
    } else {
        printf("%d\n", d[2*s+1]);
    }
    return 0;
}
