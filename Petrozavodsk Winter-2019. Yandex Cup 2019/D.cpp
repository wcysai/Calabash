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

const int MAXN = 10005;
int cat[MAXN];
ULL val[MAXN];

struct PartitionMatroid {
    bool used[128] = {0};
    
    void insert(int x) { used[cat[x]] = true; }
    bool test(int x) const { return !used[cat[x]]; }
};

struct LinearMatroid {
    static const int MAXD = 62;
    ULL b[MAXD] = {};
    
    bool test(int x) const {
        LL v = val[x];
        for (int j = MAXD - 1; j >= 0; j--) {
            if (!(v & (1ull << j))) continue;
            if (b[j]) v ^= b[j]; else return true;
        }
        return false;
    }

    void insert(int x) {
        LL v = val[x];
        for (int j = MAXD - 1; j >= 0; j--) {
            if (!(v & (1ull << j))) continue;
            if (b[j]) v ^= b[j];
            else {
                for (int k = 0; k < j; k++) 
                    if (v & (1ull << k)) v ^= b[k];
                for (int k = j + 1; k < MAXD; k++) 
                    if (b[k] & (1ull << j)) b[k] ^= v;
                b[j] = v;
                return;
            }
        }
    }
};

template <typename MT1, typename MT2>
struct MatroidIntersection {
    int n;
    bool in[MAXN] = {}, t[MAXN], vis[MAXN];
    int pre[MAXN];
    vector<int> adj[MAXN];
    queue<int> q;

    MatroidIntersection(int n) : n(n) { }
    
    vector<int> getcur() {
        vector<int> ret;
        rep (i, n) if (in[i]) ret.push_back(i);
        return ret;
    }
    
    void enqueue(int x, int p) { 
        if (vis[x]) return; 
        vis[x] = true; pre[x] = p; q.push(x); 
        if (t[x]) throw x;
    };

    vector<int> run() {
        while (true) {
            vector<int> cur = getcur();
            fill(vis, vis + n, 0);
            rep (i, n) adj[i].clear();
            MT2 mt2;
            for (int i : cur) mt2.insert(i);
            rep (i, n) t[i] = mt2.test(i);
            vector<MT1> mt1s(cur.size());
            vector<MT2> mt2s(cur.size());
            rep (i, cur.size()) rep (j, cur.size()) if (i != j) {
                mt1s[i].insert(cur[j]);
                mt2s[i].insert(cur[j]);
            }
            rep (i, n) if (!in[i]) rep (j, cur.size()) {
                if (mt1s[j].test(i)) adj[cur[j]].push_back(i);
                if (mt2s[j].test(i)) adj[i].push_back(cur[j]);
            }
            q = {};
            try {
                MT1 mt1;
                for (int i : cur) mt1.insert(i);
                rep (i, n) if (mt1.test(i)) enqueue(i, -1);
                while (q.size()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) enqueue(v, u);
                }
            } catch (int v) {
                while (v >= 0) { in[v] ^= 1; v = pre[v]; }
                continue;
            }
            break;
        };
        return getcur();
    }
};

int n, m, nn;
ULL cs[MAXN];

int main() {
    scanf("%d", &n);
    rep (i, n) {
        scanf("%llu", val + nn);
        cat[nn] = i;
        nn++;
    }
    scanf("%d", &m);
    rep (i, m) {
        int sz; scanf("%d", &sz);
        rep (j, sz) {
            cat[nn] = i + n;
            scanf("%llu", val + nn);
            nn++;
        }
    }
    MatroidIntersection<PartitionMatroid, LinearMatroid> matint(nn);
    vector<int> res = matint.run();
    if (res.size() < n + m) {
        puts("-1");
    } else {
        for (int x : res) cs[cat[x]] = val[x];
        rep (i, m) printf("%llu\n", cs[i + n]);
    }
    return 0;
}
