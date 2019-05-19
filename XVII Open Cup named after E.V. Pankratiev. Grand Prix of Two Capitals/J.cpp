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
vector<int> adj[100005];
int d1[100005], d2[100005];

int solve(int s, int t) {
    queue<int> q1, q2; 
    vector<int> done = {s, t};
    q1.push(s); q2.push(t);
    d1[s] = d2[t] = 0;
    try {
        while (q1.size() or q2.size()) {
            {
                queue<int> qn;
                while (q1.size()) {
                    int u = q1.front(); q1.pop();
                    for (int v : adj[u]) {
                        if (d1[v] >= 0) continue;
                        d1[v] = d1[u] + 1;
                        done.push_back(v);
                        if (d2[v] >= 0) throw d1[v] + d2[v];
                        qn.push(v);   
                    }
                }
                    q1 = move(qn);

            }
            {
                queue<int> qn;
                while (q2.size()) {
                    int u = q2.front(); q2.pop();
                    for (int v : adj[u]) {
                        if (d2[v] >= 0) continue;
                        d2[v] = d2[u] + 1;
                        done.push_back(v);
                        if (d1[v] >= 0) throw d1[v] + d2[v];
                        qn.push(v);   
                    }
                }
                    q2 = move(qn);
            }
        }
        throw -1;
    } catch(int ans) {
        for (int x : done) d1[x] = d2[x] = -1;
        return ans;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) d1[i] = d2[i] = -1;
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int q; scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d%d", &u, &v);
        printf("%d\n", solve(u, v));
    }
    return 0;
}
