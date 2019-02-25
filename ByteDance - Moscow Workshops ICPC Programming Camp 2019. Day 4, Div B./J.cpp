#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL; 

const int MAXN = 300005;

typedef pair<LL, int> pii;
struct MDST {
    priority_queue<pii, vector<pii>, greater<pii>> heap[MAXN];
    LL shift[MAXN];
    int fa[MAXN], vis[MAXN];

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    
    void unite(int x, int y) {
        x = find(x); y = find(y); fa[y] = x; if (x == y) return;
        if (heap[x].size() < heap[y].size()) { 
            swap(heap[x], heap[y]); 
            swap(shift[x], shift[y]); 
        }
        while (heap[y].size()) {
            auto p = heap[y].top(); heap[y].pop();
            heap[x].emplace(p.first - shift[y] + shift[x], p.second);
        }
    }
    
    void add_edge(int u, int v, LL w) { heap[v].emplace(w, u); }
    
    LL run(int n, int rt) {
        LL ans = 0;
        iota(fa, fa + n + 1, 0);
        Rep (i, n) if (find(i) != find(rt)) {
            int u = find(i);
            stack<int, vector<int>> s;
            while (find(u) != find(rt)) {
                if (vis[u]) while (s.top() != u) { 
                    vis[s.top()] = 0; unite(u, s.top()); s.pop(); 
                } else { vis[u] = 1; s.push(u); }
                while (heap[u].size()) {
                    ans += heap[u].top().first - shift[u];
                    shift[u] = heap[u].top().first;
                    if (find(heap[u].top().second) != u) break;
                    heap[u].pop();
                }
                if (heap[u].empty()) return LLONG_MIN;
                u = find(heap[u].top().second);
            } 
            while (s.size()) { vis[s.top()] = 0; unite(rt, s.top()); s.pop(); }
        }
        return ans;
    }
} mdst;

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        mdst.add_edge(u, v, w);
    }
    LL ans = mdst.run(n, 1);
    if (ans == LLONG_MIN) printf("NO\n"); else printf("YES\n%lld\n", ans);
    return 0;
}
