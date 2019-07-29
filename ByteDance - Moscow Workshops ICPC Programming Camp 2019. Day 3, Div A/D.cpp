#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debuf(...) ((void) 0)
#endif
typedef long long LL;

struct Hungarian {
    int nx, ny;
    vector<int> mx, my;
    vector<vector<int>> e;
    vector<bool> mark;

    void init(int nx, int ny) {
        this->nx = nx;
        this->ny = ny;
        mx.resize(nx); my.resize(ny);
        e.clear(); e.resize(nx);
        mark.resize(nx);
    }

    void add(int a, int b) {
        e[a].push_back(b);
    }

    bool augment(int i) {
        if (!mark[i]) {
            mark[i] = true;
            for (int j : e[i]) {
                if (my[j] == -1 || augment(my[j])) {
                    mx[i] = j; my[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

    int match() {
        int ret = 0;
        fill(range(mx), -1);
        fill(range(my), -1);
        rep (i, nx) {
            fill(range(mark), false);
            if (augment(i)) ret++;
        }
        return ret;
    }
} hung;

int n, m;
set<int> adj[100005];

void yield(int x, int y) {
    adj[x].erase(y);
    adj[y].erase(x);
    hung.add(x, y);
    m--;
}

void decompose() {
    while (m) {
        int cur = 0;
        while (adj[cur].empty()) cur++;
        while (adj[cur].size()) {
            int nxt = *adj[cur].begin();
            yield(cur, nxt);
            cur = nxt;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    if (m == 0) {
        puts("Impossible");
        return 0;
    }
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    hung.init(n, n);
    decompose();
    hung.match();
    printf("%d\n", n);
    rep (i, n) printf("%d %d\n", i + 1, hung.mx[i] + 1);
    return 0;
}
