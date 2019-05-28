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

int n, m, s;
int a[128], b[128], c[128], d[128];
int jd[128][2048];
char mat[2048][2048];
int vis[2048];

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

void enter(int u, int t) {
    if (vis[u] >= 0) return;
    vis[u] = t;
    rep (v, n) {
        int id = mat[u][v];
        if (id == '.') continue;
        if (vis[v] >= 0) continue;
        pq.emplace(t + jd[id][t % c[id]], v);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &s);
    rep (i, m) {
        char ch[4]; int id;
        scanf("%s", ch); id = ch[0];
        scanf("%d%d%d%d", a + id, b + id, c + id, d + id);
        rep (t, c[id]) jd[id][t] = (a[id] * t + b[id]) % c[id] + d[id];
        bool flag;
//        cout << "! " << char(id) << endl;
//        rep (i, c[id]) cout << jd[id][i] << ' ' ; cout << endl;
        do {
            flag = false;
            for (int t = c[id] - 1; t >= 0; t--) {
                if (jd[id][t] > jd[id][(t+1)%c[id]] + 1) {
                    jd[id][t] = jd[id][(t+1)%c[id]] + 1;
                    flag = true;
                }
            }
        } while (flag);
//        rep (i, c[id]) cout << jd[id][i] << ' ' ; cout << endl;
    }
    rep (i, n) scanf("%s", mat[i]);
    memset(vis, -1, sizeof vis);
    enter(0, s);
    while (pq.size()) {
        int u, t; tie(t, u) = pq.top(); pq.pop();
        enter(u, t);
    }
    if (vis[n-1] < 0) cout << -1 << endl; else  cout << vis[n - 1] - s << endl;
    return 0;
}
