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

const int MAXN = 100005;
int n, m;
vector<int> adj[MAXN];
map<int, int> wt[MAXN];

int dfn[MAXN], low[MAXN], idx = 0;
vector<int> bccin[MAXN];
vector<vector<pair<int, int>>> bcc;
stack<pair<int, int>> st;

LL tot;

void dfs(int u, int p = 0) {
    dfn[u] = low[u] = ++idx;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            st.emplace(u,v);
            dfs(v,u);
            low[u] = min(low[u],low[v]);
            if (low[v] >= dfn[u]){
                bccin[u].push_back(bcc.size());
                vector<pair<int,int>> cur;
                do {
                    cur.push_back(st.top());
                    st.pop();
                } while (cur.back() != make_pair(u,v));
                reverse(range(cur));

                for (auto& p : cur) tot += wt[p.first][p.second];
                if (cur.size() == 1) tot += wt[cur[0].first][cur[0].second];

                bcc.push_back(move(cur));
            }
        } else if (dfn[v] < dfn[u] and v != p){
            st.emplace(u, v);
            low[u] = min(low[u], dfn[v]);
        }
    }
}

LL dp[MAXN];

void update(LL &x, LL y) { x = max(x, y); }

void work_vertex(int u);

void work_block(int id) {
    vector<int> vs;
    for (auto p : bcc[id]) vs.push_back(p.first);
    if (vs.size() == 1) {
        int u, v; tie(u, v) = bcc[id].front();
        work_vertex(v);
        update(dp[u], dp[v] + wt[u][v]);
    } else {
        int u = vs.front();
        vector<LL> d1(vs.size()), d2(vs.size());
        for (int i = 1; i < vs.size(); i++) {
            work_vertex(vs[i]);
            d1[i] = wt[vs[i]][vs[i-1]];
            d2[i] = wt[vs[i]][vs[(i+1)%vs.size()]];
        }
        for (int i = 1; i < vs.size(); i++) d1[i] += d1[i-1];
        for (int i = vs.size() - 1; i; i--) d2[i-1] += d2[i];
        for (int i = 1; i < vs.size(); i++) {
            int v = vs[i];
            update(dp[u], dp[v] - min(d1[i], d2[i]));
        }
    }
}

void work_vertex(int u) {
    for (int id : bccin[u]) work_block(id);
}

int main() {
    scanf("%d%d", &n, &m);
    rep (_, m) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        wt[u][v] = wt[v][u] = w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    work_vertex(1);
    cout << tot - dp[1] << endl;
    return 0;
}
