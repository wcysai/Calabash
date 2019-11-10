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

namespace worker {

vector<int> adj[100005];
vector<int> cyc, path;
bool vis[100005], vis2[100005], incyc[100005];

void find_path(int u, int t) {
    if (vis[u]) return;
    vis[u] = true; cyc.push_back(u);
    if (u == t) throw 0;
    for (int v : adj[u]) find_path(v, t);
    cyc.pop_back();
}

void find_any_path(int u) {
    if (vis2[u]) return;
    vis2[u] = true; path.push_back(u);
    if (incyc[u]) throw u;
    for (int v : adj[u]) find_any_path(v);
    path.pop_back();
}

void _remove_edge(int u, int v) {
    auto it = find(range(adj[u]), v);
    if (it != adj[u].end()) adj[u].erase(it);
}

void remove_edge(int u, int v) {
    _remove_edge(u, v);
    _remove_edge(v, u);
}

void clear(int n) {
    cyc.clear(); path.clear();
    Rep (i, n) {
        adj[i].clear();
        vis[i] = vis2[i] = incyc[i] = false;
    }
}

void output(vector<int>::iterator it1, vector<int>::iterator it2) {
    printf("%d", int(it2 - it1));
    while (it1 < it2) printf(" %d", *it1), it1++;
    printf("\n");
}

void work(vector<int> vs, vector<pair<int, int>> es) {
    for (auto p : es) {
        int u, v; tie(u, v) = p;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int u, v; tie(u, v) = es.front();
    remove_edge(u, v);
    try { find_path(u, v); } catch(...) {}
//    for (int x : cyc) printf("%d ", x); puts("!");
    for (int i = 1; i < cyc.size(); i++) remove_edge(cyc[i-1], cyc[i]);
    for (int x : cyc) incyc[x] = true;
    for (int u : cyc) if (adj[u].size()) {
        incyc[u] = false;
        try {
            find_any_path(u);
            assert(0);
        } catch (int v) {
//            for (int x : path) printf("%d ", x); puts("!");
            printf("%d %d\n", u, v);
            output(range(path));
            rotate(cyc.begin(), find(range(cyc), u), cyc.end());
            cyc.push_back(u);
            auto it = find(range(cyc), v);
            output(cyc.begin(), it + 1);
            reverse(it, cyc.end());
            output(it, cyc.end());
            return ;
        }
    }
    assert(0);
}

}

//

const int MAXN = 100005;
int n;
vector<int> adj[100005];
int dfn[MAXN], low[MAXN], idx;

stack<pair<int, int>> st;

void dfs(int u, int p = 0) {
    dfn[u] = low[u] = ++idx;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            st.emplace(u, v);
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                vector<pair<int, int>> cur;
                do {
                    cur.push_back(st.top());
                    st.pop();
                } while (cur.back() != make_pair(u, v));
                vector<int> vs;
                for (auto p : cur) {
                    vs.push_back(p.first);
                    vs.push_back(p.second);
                }
                sort(range(vs));
                vs.erase(unique(range(vs)), vs.end());
//                _debug("!");
//                for (int x : vs) cout << x << ' '; cout << endl;
  //              for (auto pr : cur) printf("(%d,%d) ", pr.first, pr.second);
    //            puts("");
                if (cur.size() > vs.size()) {
                    worker::work(move(vs), move(cur));
                    throw 0;
                }
            }
        } else if (dfn[v] < dfn[u] and v != p) {
            st.emplace(u, v);
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void clear(int n) {
    idx = 0; st = decltype(st)();
    Rep (i, n) {
        adj[i].clear();
        dfn[i] = low[i] = 0;
    }
}

int main() {
//#ifdef ONLINE_JUDGE
    freopen("grand.in", "r", stdin);
    freopen("grand.out", "w", stdout);
//#endif
    int T; scanf("%d", &T);
    while (T--) {
        int m;
        scanf("%d%d", &n, &m);
        clear(n); worker::clear(n);
        rep (_, m) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        try {
            for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i);
            puts("-1");
        } catch (...) {}
    }
    return 0;
}
