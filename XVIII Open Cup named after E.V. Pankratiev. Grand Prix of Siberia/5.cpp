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
int fa[100005];
bool e[100005];
vector<int> ex;

pair<int, bool> find(int x) {
    if (fa[x] == x) return {x, 0}; 
    pair<int, bool> edge = find(fa[x]);
    tie(fa[x], e[x]) = make_pair(edge.first, edge.second ^ e[x]);
    return {fa[x], e[x]};
}

bool unite(int u, int v, bool edge) {
    pair<int, bool> e1 = find(u), e2 = find(v);
    if (e1.first == e2.first) {
        if (e1.second ^ e2.second ^ edge) {
            puts("inconsistent");
            exit(0);
        }
        return true;
    }
    fa[e2.first] = e1.first;
    e[e2.first] = edge ^ e1.second ^ e2.second;
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    iota(fa, fa + n + 1, 0);
    Rep (i, m) {
        char cmd[12]; int u, v;
        scanf("%s", cmd);
        if (strcmp(cmd, "hor") == 0) {
            scanf("%d", &u);
            if (unite(0, u, 0)) ex.push_back(i);
        } else if (strcmp(cmd, "vert") == 0) {
            scanf("%d", &u);
            if (unite(0, u, 1)) ex.push_back(i);
        } else if (strcmp(cmd, "par") == 0) {
            scanf("%d%d", &u, &v);
            if (unite(u, v, 0)) ex.push_back(i);
        } else if (strcmp(cmd, "perp") == 0) {
            scanf("%d%d", &u, &v);
            if (unite(u, v, 1)) ex.push_back(i);
        } else assert(0);
    } 
    puts("consistent");
    printf("%d\n", (int)ex.size());
    for (int x : ex) printf("%d ", x);
    return 0;
}
