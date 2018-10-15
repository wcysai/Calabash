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

int n, k, m;
set<int> notok[100005];
set<int> member[100005];
int fa[100005];

int init() {
    Rep (i, n) {
        fa[i] = i;
        member[i].insert(i);
    }
}

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

vector<int> ans;

bool unite(int u, int v) {
    _debug("%d %d", u, v);
    u = find(u), v = find(v);
    if (u == v) return true;
    if (member[u].size() < member[v].size()) swap(u, v);

    for (set<int>::iterator it = member[v].begin(); it != member[v].end(); it++)
        if (notok[u].find(*it) != notok[u].end())
            return false;

    for (set<int>::iterator it = member[v].begin(); it != member[v].end(); it++)
        member[u].insert(*it);

    if (notok[u].size() < notok[v].size())
        notok[u].swap(notok[v]);

    for (set<int>::iterator it = notok[v].begin(); it != notok[v].end(); it++)
        notok[u].insert(*it);

    fa[v] = u;
    return true;
}

int main(){
    scanf("%d%d%d", &n, &k, &m);
    init();
    rep (i, k) {
        int u, v; scanf("%d%d", &u, &v);
        notok[u].insert(v);
        notok[v].insert(u);
    }
    Rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        if (unite(u, v)) ans.push_back(i);
    }
    printf("%d\n", int(ans.size()));
    for (vector<int>::iterator it = ans.begin(); it != ans.end(); it++)
        printf("%d ", *it);
    return 0;
}

/*
3 1 3
 1 2
 1 2
 2 3
 1 3

 5 2 6
 1 2
 2 3
 1 3
 2 4
 3 4
 1 4
 4 5
 1 5

 */
