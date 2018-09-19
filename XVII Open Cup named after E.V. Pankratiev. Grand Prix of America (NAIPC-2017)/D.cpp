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

int n, va[200005];
vector<int> adj[200005];

void pmp(map<int, int>& mp) {
    for (auto p : mp) fprintf(stderr, "<%d, %d> ", p.first, p.second); fprintf(stderr, "\n");
}

multiset<int> dfs(int u, int p) {
    _debug("%d %d", u, p);
    if (p && adj[u].size() == 1) {
        multiset<int> ms;
        ms.insert(va[u]);
        return ms;
    }

    int maxsz = 0, maxid = 0;
    vector<multiset<int>> result;
    for (int v : adj[u]) {
        if (v == p) continue;
        result.push_back(dfs(v, u));
        if (result.back().size() > maxsz) {
            maxsz = result.back().size();
            maxid = result.size() - 1;
        }
    }

    auto& ms = result[maxid];
    for (int i = 0; i < result.size(); i++) {
        if (i == maxid) continue;
        for (int p : result[i]) {
            ms.insert(p);
        }
    }

    auto x = ms.lower_bound(va[u]);
    if (x != ms.end()) ms.erase(x);
    ms.insert(va[u]);

    return move(ms);
}

int main() {
    scanf("%d", &n);
    Rep (i, n) {
        int p;
        scanf("%d%d", va + i, &p);
        if (p) {
            adj[p].push_back(i);
            adj[i].push_back(p);
        }
    }
    printf("%d\n", (int)dfs(1, 0).size());
    return 0;
}

/*
 5
 4 0
 3 1
 2 2
 1 3
 0 4
 */
