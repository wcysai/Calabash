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

int ask(int id) {
    printf("? %d\n", id);
    fflush(stdout);
    int ret; scanf("%d", &ret);
    return ret;
}

int n, m, cnt;
int fa[100005];
double prob[100005];
int qn[100005];
set<pair<int, int>> qcomp[100005];
set<pair<double, int>> qtot;

int find(int x) { return fa[x] < 0 ? x : fa[x] = find(fa[x]); }

void update_component(int cid) {
    qtot.erase(make_pair(prob[cid], cid));
    prob[cid] = double(n - qcomp[cid].begin()->first) / (n + fa[cid]);
    qtot.emplace(prob[cid], cid);
}

bool unite(int u, int v) {
    u = find(u); v = find(v); if (u == v) return false;
    if (++cnt == n) throw 0;
    if (-fa[u] < -fa[v]) swap(u, v);
    fa[u] += fa[v]; fa[v] = u;
    for (auto pr : qcomp[v]) qcomp[u].insert(pr);
    qcomp[v].clear(); qtot.erase(make_pair(prob[v], v));
    update_component(u);
    return true;
}

void update_vertex(int vid, int newvalue) {
    int cid = find(vid);
    qcomp[cid].erase(make_pair(qn[vid], vid));
    qn[vid] = newvalue;
    qcomp[cid].emplace(qn[vid], vid);
    update_component(find(vid));
}

int main() {
    int T; scanf("%d", &T);
    while (T--) try {
        fflush(stdout);
        scanf("%d%d", &n, &m); cnt = 1;
        fill(fa + 1, fa + n + 1, -1);
        fill(qn + 1, qn + n + 1, 1);
        qtot.clear();
        Rep (i, n) {
            qcomp[i].clear();
            qcomp[i].emplace(qn[i], i);
            prob[i] = double(n - qn[i]) / (n + fa[i]);
            qtot.emplace(prob[i], i);
        }
        rep (_, n + n) {
            int cid = qtot.begin()->second;
            int vid = qcomp[cid].begin()->second;
//            _debug("c=%d, v=%d, q=%d, p=%f", cid, vid, qn[vid], 1.0 / prob[cid]);
            int id = ask(vid);
            if (id < 0) {
                update_vertex(vid, n);
            } else {
                update_vertex(vid, qn[vid]+1);
                update_vertex(id, qn[id]+1);
                unite(vid, id);
            }
        }
        puts("-");
    } catch (...) {
        puts("+");
    }
    return 0;
}
