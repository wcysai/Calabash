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

int n, m;
char name[1 << 20][12];
vector<int> ch[1 << 20];
int fa[1 << 20], lccnt[1 << 20];
LL len[1 << 20], lrt[1 << 20];
LL dp[1 << 20], l;
int cur, ans[1 << 20], state[1 << 20];

priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<>> pq;

void update_state(int u) {
    _debug("%d starting long ...", u);
    state[u] = 1; cur++;
    dp[u] = LLONG_MAX;
    for (int v : ch[u]) dp[u] = min(dp[u], dp[v]);
    dp[u] += len[u];
    _debug("%d starting long, dp = %lld", u, dp[u]);
    pq.emplace(dp[u], u);
}

void finish_long(int u) {
    _debug("%d finishing long ...", u);
    assert(state[u] == 1);
    state[u] = 2; cur--;
    if (fa[u] and --lccnt[fa[u]] == 0)
        update_state(fa[u]);
}

void dfs(int u, LL clen) {
    clen += len[u]; lrt[u] = clen;
    for (int v : ch[u]) dfs(v, clen); 
}

int main() {
    vector<int> rlist;
    scanf("%d%d", &n, &m); 
    Rep (i, n) {
        scanf("%s%d%lld", name[i], fa + i, len + i); if (fa[i]) fa[i] += n;
        if (fa[i]) ch[fa[i]].push_back(i); else rlist.push_back(i);
        state[i] = 1; dp[i] = len[i];
        pq.emplace(len[i], i);
    }
    for (int i = n + 1; i <= n + m; i++) {
        scanf("%d%lld", fa + i, len + i); if (fa[i]) fa[i] += n;
        if (fa[i]) ch[fa[i]].push_back(i); else rlist.push_back(i);
    }
    for (int i = n + 1; i <= n + m; i++) lccnt[i] = ch[i].size();
    for (int rt : rlist) dfs(rt, 0);
    cur = n;
    vector<pair<LL, int>> q;
    Rep (i, n) {
        _debug("q %d: l=%lld", i, lrt[i]);
        q.emplace_back(lrt[i], i);
    }
    sort(range(q), greater<>());
    while (pq.size() and q.size()) {
        while (pq.size() and pq.top().first <= q.back().first) {
           int u = pq.top().second; l = pq.top().first; pq.pop();
           _debug("l = %lld", l);
           finish_long(u);
        } 
        while (pq.size() and q.size() and pq.top().first > q.back().first) {
            int u = q.back().second;
            _debug("ans[%d]=%d", u, cur);
            ans[u] = cur;
            q.pop_back();
        }
    }
    while (q.size()) {
        ans[q.back().second] = cur;
        q.pop_back();
    }
    Rep (i, n) printf("%s %d\n", name[i], ans[i] + 1);
    return 0;
}
