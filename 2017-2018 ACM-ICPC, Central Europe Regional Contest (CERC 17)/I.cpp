#include <bits/stdc++.h>
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
#define mset(x, y) memset(x, y, sizeof x)
#define mcpy(x, y) memcpy(x, y, sizeof x)
using namespace std;

typedef long long LL;
typedef pair <int, int> pii;

inline int Read()
{
    int x = 0, f = 1, c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (;  isdigit(c); c = getchar())
        x = x * 10 + c - '0';
    return x * f;
}

const int MAXN = 500005;

int n, m, ql, qr, cnt, tot, tim, top, seg_rot, d[MAXN], p[MAXN], q[MAXN], dfn[MAXN], low[MAXN], scc[MAXN], lch[MAXN], rch[MAXN], sta[MAXN], adj_min[MAXN], adj_max[MAXN], seg_min[MAXN], seg_max[MAXN];
vector <int> adj[MAXN], adv[MAXN];

inline void Modify(int x, int l, int r, int p, int u, int v)
{
    seg_min[x] = min(seg_min[x], u), seg_max[x] = max(seg_max[x], v);
    if (l == r)
        return ;
    int mid = l + r >> 1;
    return p <= mid ? Modify(x << 1, l, mid, p, u, v) : Modify(x << 1 | 1, mid + 1, r, p, u, v);
}

inline pii Query(int x, int l, int r, int ql, int qr)
{
    if (l == ql && r == qr)
        return mp(seg_min[x], seg_max[x]);
    int mid = l + r >> 1;
    if (qr <= mid)
        return Query(x << 1, l, mid, ql, qr);
    if (ql > mid)
        return Query(x << 1 | 1, mid + 1, r, ql, qr);
    pii L = Query(x << 1, l, mid, ql, mid), R = Query(x << 1 | 1, mid + 1, r, mid + 1, qr);
    return mp(min(L.xx, R.xx), max(L.yy, R.yy));
}

inline void Build(int &x, int l, int r)
{
    x = ++ tot;
    if (l == r)
        return (void)(adj[x].pb(l));
    int mid = l + r >> 1;
    Build(lch[x], l, mid), Build(rch[x], mid + 1, r), adj[x].pb(lch[x]), adj[x].pb(rch[x]);
}

inline void Addedge(int x, int l, int r, int ql, int qr, int p)
{
    if (l == ql && r == qr)
        return (void)(adj[p].pb(x));
    int mid = l + r >> 1;
    if (qr <= mid)
        Addedge(lch[x], l, mid, ql, qr, p);
    else if (ql > mid)
        Addedge(rch[x], mid + 1, r, ql, qr, p);
    else
        Addedge(lch[x], l, mid, ql, mid, p), Addedge(rch[x], mid + 1, r, mid + 1, qr, p);
}

inline void DFS(int x)
{
    dfn[x] = low[x] = ++ tim, sta[++ top] = x;
    for (auto y : adj[x])
        if (!dfn[y])
            DFS(y), low[x] = min(low[x], low[y]);
        else if (!scc[y])
            low[x] = min(low[x], dfn[y]);
    if (dfn[x] == low[x])
    {
        cnt ++, adj_min[cnt] = n, adj_max[cnt] = 0;
        for (int k = 0; k ^ x; )
        {
            scc[k = sta[top --]] = cnt;
            if (k < n)
                adj_min[cnt] = min(adj_min[cnt], k), adj_max[cnt] = max(adj_max[cnt], k);
        }
    }
}

inline void ReBuild()
{
    for (int i = 1; i <= tot; i ++)
        for (auto j : adj[i])
            if (scc[i] ^ scc[j])
                adv[scc[i]].pb(scc[j]), d[scc[j]] ++;
    for (int i = 1; i <= cnt; i ++)
        if (!d[i])
            q[++ qr] = i;
    while (ql < qr)
    {
        int x = q[++ ql];
        for (auto y : adv[x])
            if (!-- d[y])
                q[++ qr] = y;
    }
    for (int i = qr; i; i --)
    {
        int x = q[i];
        for (auto y : adv[x])
            adj_min[x] = min(adj_min[x], adj_min[y]), adj_max[x] = max(adj_max[x], adj_max[y]);
    }
}

int main()
{
#ifdef wxh010910
    freopen("data.in", "r", stdin);
#endif
    n = Read(), tot = n - 1;
    mset(seg_min, 0x3f), mset(seg_max, 0);
    for (int i = 1; i <= n; i ++)
        p[i] = Read(), Modify(1, 1, n, p[i], i, i);
    if (n == 1)
    {
        m = Read();
        while (m --)
            puts("1 1");
        return 0;
    }
    Build(seg_rot, 1, n - 1);
    for (int i = 1; i < n; i ++)
    {
        int l = p[i], r = p[i + 1];
        if (l > r)
            swap(l, r);
        pii ret = Query(1, 1, n, l, r);
        Addedge(seg_rot, 1, n - 1, ret.xx, ret.yy - 1, i);
    }
    for (int i = 1; i <= tot; i ++)
        if (!dfn[i])
            DFS(i);
    ReBuild();
    mset(seg_min, 0x3f), mset(seg_max, 0);
    for (int i = 1; i < n; i ++)
        Modify(1, 1, n - 1, i, adj_min[scc[i]], adj_max[scc[i]]);
    m = Read();
    while (m --)
    {
        int l = Read(), r = Read();
        if (l == r)
            printf("%d %d\n", l, r);
        else
        {
            pii ret = Query(1, 1, n - 1, l, r - 1);
            printf("%d %d\n", ret.xx, ret.yy + 1);
        }
    }
    return 0;
}
