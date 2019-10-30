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
vector<int> adj[4096];

ULL ha(int u, int p) {
    ULL ret = 27934269357;
    for (int v : adj[u]) if (v != p) ret += ha(v, u) * 233;
    return ret ^ ((ret >> 27) + 19260817);
}

int getsz(int u, int p) {
    int ret = 1;
    for (int v : adj[u]) if (v != p) ret += getsz(v, u);
    return ret;
}

vector<ULL> hv;

void dfsha(int u, int p) {
    hv.push_back(ha(u, 0));
    for (int v : adj[u]) if (v != p) dfsha(v, u);
}

bool check(int u) {
    for (int v : adj[u]) 
        adj[v].erase(find(range(adj[v]), u));
     
    vector<ULL> vs;
    for (int v : adj[u]) {
        hv.clear();
        dfsha(v, 0);
        sort(range(hv));
        if (vs.empty()) vs = hv;
        else if (vs != hv) return false;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    rep (i, n - 1) {
        int u, v ; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() <= 1) continue;
        int sz = -1;
        for (int v : adj[i]) {
            int csz = getsz(v, i);
            if (sz < 0) sz = csz;
            if (sz != csz) goto cont;
        }
        if (check(i)) cout << adj[i].size() << endl;
        else cout << -1 << endl;
        return 0;
    cont:;
    }
    cout << -1 << endl;
    return 0;
}
