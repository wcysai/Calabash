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
const int n = 10000;
vector<int> adj[10005];

int N, M;
char grid[12][12];
bool part[10005];	// left true / right false
int encode[10][10][10][10];
int mx[MAXN], my[MAXN];
bool flag[10005];

bool valid(int i, int j, int k, int l) {
    if (i < 0 or j < 0 or k < 0 or l < 0) return false;
    if (i >= N or j >= M or k >= N or l >= M) return false;
    if (i == k and j == l) return false;
    if (grid[i][j] == '#' or grid[k][l] == '#') return false;
    return true;
}

void build_graph() {
    for (auto& vec : adj) vec.clear();
    rep (i, N) scanf("%s", grid[i]);
    rep (i, N) rep (j, M) rep (k, N) rep (l, M) if (valid(i, j, k, l)) {
        int u = encode[i][j][k][l];
        static const int
            di[8] = { 1, -1,  0,  0,  0,  0,  0,  0},
            dj[8] = { 0,  0,  1, -1,  0,  0,  0,  0},
            dk[8] = { 0,  0,  0,  0,  1, -1,  0,  0},
            dl[8] = { 0,  0,  0,  0,  0,  0,  1, -1};
        rep (d, 8) {
            int ii = i + di[d], jj = j + dj[d], kk = k + dk[d], ll = l + dl[d];
            if (!valid(ii, jj, kk, ll)) continue;
            int v = encode[ii][jj][kk][ll];
            adj[u].push_back(v); adj[v].push_back(u);
        }
    }
}

void augment_left(int u) {
    if (flag[u]) return;
    flag[u] = true;
    for (int v : adj[u]) {
        assert(my[v]);
        augment_left(my[v]);
    }
}

void augment_right(int u) {
    if (flag[u]) return;
    flag[u] = true;
    for (int v : adj[u]) {
        assert(mx[v]);
        augment_right(mx[v]);
    }
}

void bipartite_matching();

int main() {
    rep (ii, 10) rep (jj, 10) rep (kk, 10) rep (ll, 10) {
        if (ii == kk and jj == ll) {
            encode[ii][jj][kk][ll] = -1;
            continue;
        }
        int i = ii, j = jj, k = kk, l = ll;
        if (make_pair(i, j) > make_pair(k, l)) swap(i, k), swap(j, l);
        encode[ii][jj][kk][ll] = i * 1000 + j * 100 + k * 10 + l + 1;
        part[encode[ii][jj][kk][ll]] = (i ^ j ^ k ^ l) & 1;
    }
    int q;
    while (scanf("%d%d%d", &N, &M, &q) == 3) {
        build_graph();
        bipartite_matching();
        memset(flag, false, sizeof flag);
        rep (i, n) {
            if (part[i] and !mx[i]) augment_left(i);
            if (!part[i] and !my[i]) augment_right(i);
        }
        while (q--) {
            int i, j, k, l; scanf("%d%d%d%d", &i, &j, &k, &l);
            i--; j--; k--; l--;
            int u = encode[i][j][k][l];
            puts(!flag[u] ? "ghh wins." : "gfh wins.");
        }
    }
    return 0;
}


namespace hopcroft_karp {


const int n1 = n, n2 = n;
vector<int> G[MAXN];
queue<int> que;
int dx[MAXN],dy[MAXN];
bool vis[MAXN];

bool find(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1)
        {
            vis[G[u][i]]=true;
            if(!my[G[u][i]]||find(my[G[u][i]]))
            {
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}

int matching()
{
    memset(mx,0,sizeof(mx));
    memset(my,0,sizeof(my));
    int ans=0;
    while(true)
    {
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=1;i<=n1;i++)
            if(!mx[i]) que.push(i);
        while(!que.empty())
        {
            int u=que.front();
            que.pop();
            for(int i=0;i<G[u].size();i++)
                if(!dy[G[u][i]])
                {
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]])
                    {
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n1;i++)
            if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}

}

void bipartite_matching() {
    using namespace hopcroft_karp;
    Rep (i, n) G[i].clear();
    Rep (i, n) if (part[i]) G[i] = adj[i];
    matching();
}
