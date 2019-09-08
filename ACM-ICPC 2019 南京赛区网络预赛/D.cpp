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
vector<int> adj[100005];
int ind[100005];
double p[100005], ed[100005], ec[100005];

void update(int u, int v, double d) {
    double prob = d / (d + 1);
    p[v] += p[u] / d;
    ed[v] += (ed[u] + p[u] / prob) / d;
    ec[v] += (ec[u] + ed[u] * (d + 1) / d + (d + 1) * (d + 1) / d / d * p[u]) / d;
}

int main() {
    int T; scanf("%d", &T);
    rep (_, T) {
        scanf("%d%d", &n, &m);
        Rep (i, n) {
            adj[i].clear();
            ind[i] = 0;
            p[i] = ed[i] = ec[i] = 0;
        }
        rep (i, m) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            ind[v]++;
        }
        vector<int> qs = {1};
        p[1] = 1;
        while (qs.size()) {
            int u = qs.back(); qs.pop_back();
            for (int v : adj[u]) {
                update(u, v, adj[u].size());
                if (--ind[v] == 0) qs.push_back(v);
            }
        }
//        Rep (i, n) _debug("%d: %f, %f, %f", i, p[i], ed[i], ec[i]);
        printf("%.2f\n", ec[n]);
    }
    return 0;
}
