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
int fa[100005];
// dp[u][0]: must not select root; dp[u][1]: may select root
int dp[100005][2], match[100005];
vector<int> ch[100005], root;
#define free seusrgh
vector<int> free, fr;

void get_free(int u, int s) {
    if (s == 0) { // can't match
        for (int v : ch[u]) get_free(v, 1);
    } else {
        if (match[u]) get_free(match[u], 0); else fr.push_back(u);
        for (int v : ch[u]) if (v != match[u]) get_free(v, 1);
    }
}

void work(int u) {
    for (int v : ch[u]) {
        work(v);
        dp[u][0] += dp[v][1];
        dp[u][1] += dp[v][1];
    }
    for (int v : ch[u]) if (dp[v][1] == dp[v][0]) {
        dp[u][1]++;
        match[u] = v;
        return;
    }
}

int main() {
//#ifdef ONLINE_JUDGE
    freopen("hidden.in", "r", stdin);
    freopen("hidden.out", "w", stdout);
//#endif
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", fa + i);
        if (fa[i]) ch[fa[i]].push_back(i);
    }
    Rep (i, n) if (fa[i] == 0) root.push_back(i), work(i);
    vector<pair<int, vector<int>>> to_match;
    int ans = 0;
    for (int u : root) {
        if (u == 1 or dp[u][0] < dp[u][1]) {
            ans += dp[u][1];
            get_free(u, 1);
            fa[u] = 1;
            free.insert(free.end(), range(fr)); fr.clear();
        } else {
            ans += dp[u][0];
            get_free(u, 0);
            to_match.emplace_back(u, move(fr));
        }
    }
    sort(range(to_match), [] (const pair<int, vector<int>>& p1,
        const pair<int, vector<int>>& p2) { return p1.second.size() > p2.second.size(); });
    for (const auto& pr : to_match) {
        int u; vector<int> new_free; tie(u, new_free) = pr;
        if (free.size()) {
            fa[u] = free.back();
            free.pop_back();
            ans++;
        } else {
            fa[u] = 1;
            free.push_back(u);
        }
        free.insert(free.end(), range(new_free));
    }
    printf("%d\n", ans);
    for (int i = 2; i <= n; i++) printf("%d ", fa[i]);
    puts("");
    return 0;
}
