#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
vector<int> adj[100005], bridge[100005];
int cut[100005], low[100005], dfn[100005], vis[100005];
bool cycle[100005];

void obtain_answer(int u, int v) {
    printf("%d %d\n", u, v);
    exit(0);
}

void find_bridge(int cur, int father, int dep) {
    vis[cur] = 1; dfn[cur] = low[cur] = dep;
    int children = 0;
    for (int i : adj[cur]) {
        if (i != father && 1 == vis[i])
            if (dfn[i] < low[cur]) low[cur] = dfn[i];
        if (0 == vis[i]) {
            find_bridge(i, cur, dep + 1);
            children++;
            if (low[i] < low[cur]) low[cur] = low[i];
            if ((father == -1 && children > 1) || (father != -1 && low[i] >= dfn[cur]))
                cut[cur] = true;
            if (low[i] > dfn[cur]) {
                bridge[i].push_back(cur);
                bridge[cur].push_back(i);
            }
        }
    }
    vis[cur] = 2;
}

inline bool is_bridge(int u, int v) {
    return find(range(bridge[u]), v) != bridge[u].end();
}

struct UFS {
    vector<int> p;

    explicit UFS(unsigned n) : p(n) {
        rep (i, n) p[i] = i;
    }

    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        p[u] = v;
        return u != v;
    }
};

void find_cycle(int u, int p, int dest) {
    cycle[u] = true;
    if (u == dest) throw 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (is_bridge(u, v)) continue;
        find_cycle(v, u, dest);
    }
    cycle[u] = false;
}

bool is_tentacle(int u, int p) {
    if (adj[u].size() >= 3) return false;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (is_tentacle(v, u) == false) return false;
    }
    return true;
}

bool is_octopus() {
    UFS ufs(n + 1);
    memset(cycle, 0, sizeof cycle);
    Rep (u, n) {
        for (int v : adj[u]) {
            if (u < v) continue;
            if (ufs.unite(u, v) == false) {
                try {
                    find_cycle(u, v, v);
                } catch (...) {
                    /*
                    printf("Cycle: ");
                    Rep (u, n) if (cycle[u]) printf(" %d", u);
                    puts("");
                     */
                    goto cont;
                }
            }
        }
    }
    exit(0);

    cont:;

    Rep (u, n) {
        if (cycle[u]) {
            if (adj[u].size() > 3) return false;
            for (int v : adj[u]) {
                if (!cycle[v] && !is_tentacle(v, u))
                    return false;
            }
        }
    }
    return true;
}

void try_delete_edge(int u, int v) {
    adj[u].erase(find(range(adj[u]), v));
    adj[v].erase(find(range(adj[v]), u));

    if (is_octopus()) {
        _debug("deg4");
        obtain_answer(u, v);
    }

    adj[u].push_back(v);
    adj[v].push_back(u);
}

void test4() {
    vector<pair<int, int>> susp;
    Rep (i, n) if (adj[i].size() == 4) for (int j : adj[i]) susp.emplace_back(i, j);

    for (auto p : susp) {
        int u, v; tie(u, v) = p;
        if (is_bridge(u, v)) continue;
        try_delete_edge(u, v);
    }

    if (susp.size()) assert(0);
}

vector<int> cur_cycle;
void detect_cycle(int u) {
    if (vis[u]) return;
    vis[u] = true;
    cur_cycle.push_back(u);
    for (int v : adj[u]) {
        if (is_bridge(u, v)) continue;
        detect_cycle(v);
    }
}

void try_break_cycle() {
    vector<int> d3;
    for (int u : cur_cycle)
        if (adj[u].size() == 3)
            d3.push_back(u);
    if (d3.size() == 1) {
        int u = d3.front();
        for (int v : adj[u]) {
            if (is_bridge(u, v)) continue;
            _debug("cycle 1");
            obtain_answer(u, v);
        }
    } else if (d3.size() == 2){
        int u = d3.front(), v = d3.back();
        if (find(range(adj[u]), v) != adj[u].end()) {
            _debug("cycle 2");
            obtain_answer(u, v);
        }
    }
}

vector<int> chain;
void detect_chain(int u, int p, int w) {
    if (u == w) return;
    chain.push_back(u);
    for (int v : adj[u]) {
        if (v == p) continue;
        if (is_bridge(u, v)) continue;
        detect_chain(v, u, w);
    }
}

void try_break_chain(int from, int to) {
    vector<int> d3;
    for (int u : chain)
        if (adj[u].size() == 3) d3.push_back(u);
    if (d3.size() == 0) {
        _debug("Chain 0");
        obtain_answer(from, chain.front());
    } else if (d3.size() == 1) {
        int u = d3.front();
        for (int v : adj[u]) {
            if (is_bridge(u, v)) continue;
            _debug("Chain 1");
            obtain_answer(u, v);
        }
    } else if (d3.size() == 2) {
        int u = d3.front(), v = d3.back();
        if (find(range(adj[u]), v) != adj[u].end()) {
            _debug("Chain 3");
            obtain_answer(u, v);
        }
    }
}


void work() {
    vector<int> head;
    Rep (i, n) {
        sort(range(bridge[i]));
        bridge[i].resize(unique(range(bridge[i])) - bridge[i].begin());
        if (adj[i].size() - bridge[i].size() == 3) head.push_back(i);
    }
    if (head.size() == 0) { // two independent cycles
        memset(vis, 0, sizeof vis);
        Rep (i, n) {
            if (adj[i].size() == bridge[i].size()) continue;
            if (vis[i]) continue;
            cur_cycle.clear();
            detect_cycle(i);
            try_break_cycle();
        }
        exit(0);
    } else if (head.size() == 2) { // three bridges;
        int u = head.front(), w = head.back();
        for (int v : adj[u]) {
            if (v == w) obtain_answer(u, w);
            chain.clear();
            detect_chain(v, u, w);
            try_break_chain(u, w);
        }
        exit(0);
    } else {
        assert(0);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    find_bridge(1, -1, 0);
/*
    Rep (i, n) {
        printf("[%d] %d:", adj[i].size() - bridge[i].size(), i);
        for (int v : adj[i]) printf(" %d", v);
        printf(" /");
        for (int v : bridge[i]) printf(" %d", v);
        puts("");
    }
*/
    test4();
    work();
    return 0;
}
/*
7 8
 1 2
 2 3
 3 4
 4 1
 3 5
 5 6
 5 7
 3 6

 */

/*
4 5
 1 2
 2 4
 1 4
 1 3
 3 4
 */
