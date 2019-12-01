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

int n;
int in[260], out[260], done[260];
int repr[8], open[260];
vector<pair<int, int>> edges;

void active_node(int u) {
    done[u] = true;
    if (!repr[out[u]]) {
        repr[out[u]] = true;
    }
}

bool try_connect(int u) {
    if (repr[in[u]]) {
        edges.emplace_back(repr[in[u]], u);
        return true;
    }
    rep (i, 7) rep (j, 7) if (repr[i] and repr[j] and (i|j) == in[u]) {
        edges.emplace_back(repr[i], u);
        edges.emplace_back(repr[j], u);
        return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    Rep (i, n) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        in[i] = u | v << 1 | w << 2;
    }
    Rep (i, n) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        out[i] = u | v << 1 | w << 2;
        out[i] &= in[i];
    }
    repr[7] = 1; done[1] = true;
    while (true) {
        int flag = false;
        Rep (i, n) if (!done[i] and try_connect(i)) {
            done[i] = true;
            if (!repr[out[i]]) {
                open[i] = true;
                repr[out[i]] = i;
            } else {
                repr[in[i]] = i;
            }
            flag = true;
        }
        if (flag == false) break;
    }
    Rep (i, n) if (in[i] and !done[i]) return puts("Impossible"), 0;
    puts("Possible");
    Rep (i, n) printf("%d ", open[i]);
    puts("");
    printf("%d\n", int(edges.size()));
    sort(range(edges)); edges.erase(unique(range(edges)), edges.end());
    for (auto pr : edges) {
        int u, v; tie(u, v) = pr;
        printf("%d %d\n", u, v);
    }
    return 0;
}
