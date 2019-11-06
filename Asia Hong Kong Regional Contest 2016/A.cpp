#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#define Range(x) ((x) + 1), ((x) + n + 1)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int fa[128];
int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
bool unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v; return u != v;
}

int n, m, k;
vector<int> adj[128];
int c[128], cc[128];

int lastc[128];
void print_state() {
    static int cnt = 0;
    assert(cnt++ <= 20000);
    Rep (i, n) printf(i == n ? "%d" : "%d ", c[i]);
    puts("");
    Rep (i, n) if (c[i] != lastc[i]) { 
        assert(any_of(range(adj[i]), [=] (int u) { return c[i] == lastc[u]; }));
    }
    memcpy(lastc, c, sizeof c);
}

void Swap(int u, int v) { 
    assert(count(range(adj[u]), v));
    swap(c[u], c[v]); print_state();
 }
void Borrow(int u, int v) { 
    assert(count(range(adj[u]), v));
    c[u] = c[v]; print_state(); 
}

vector<int> path;

void dfs(int u, int p, int to) {
    path.push_back(u);
    if (u == to) throw 0;
    for (int v : adj[u]) if (v != p) dfs(v, u, to);
    path.pop_back();
}

void find_path(int u, int v) {
    path.clear();
    try { dfs(u, 0, v); } catch (...) {}
    assert(path.size() and path.front() == u and path.back() == v);
}

int find_leaf() {
    Rep (i, n) if (adj[i].size() == 1) return i;
    assert(0);
}

int find_color(int clr) {
    Rep (i, n) if (adj[i].size() and c[i] == clr) return i;
    assert(0);
}

void change_color(int u, int v) { // change a color u to v
    assert(u != v);
    u = find_color(u);
    v = find_color(v);
    find_path(u, v);
    for (int i = 1; i < path.size() - 1; i++) Swap(path[i-1], path[i]);
    Borrow(path.rbegin()[1], path.back());
}

void set_color(int u, int v) { // set vertex u to color v
    if (c[u] == v) return;
    v = find_color(v); 
    find_path(v, u); 
    for (int i = 1; i < path.size(); i++) Swap(path[i-1], path[i]);
}

void remove_vertex(int u) {
    assert(adj[u].size() == 1);
    for (int v : adj[u]) adj[v].erase(find(range(adj[v]), u));
    adj[u].clear();
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    iota(fa + 1, fa + n + 1, 1);
    Rep (i, n) scanf("%d", c + i);
    Rep (i, n) scanf("%d", cc + i);
    memcpy(lastc, c, sizeof c);
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        if (unite(u, v)) { 
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    set<int> ss1(Range(c)), ss2(Range(cc));
    for (int i : ss2) if (!ss1.count(i)) return puts("Impossible"), 0;
    print_state();
    map<int, pair<int, int>> cm;
    Rep (i, n) cm[c[i]].first++, cm[cc[i]].second++;
    vector<int> s1, s2;
    for (auto& pr : cm) {
        int u = pr.first, n1 = pr.second.first, n2 = pr.second.second;
        rep (_, n1 - n2) s1.push_back(u);
        rep (_, n2 - n1) s2.push_back(u);   
    }
    assert(s1.size() == s2.size());
    rep (j, s1.size()) change_color(s1[j], s2[j]);
    rep (_, n - 1) {
        int id = find_leaf();
        set_color(id, cc[id]);
        remove_vertex(id);
    }
    Rep (i, n) assert(c[i] == cc[i]);
    return 0;
}
