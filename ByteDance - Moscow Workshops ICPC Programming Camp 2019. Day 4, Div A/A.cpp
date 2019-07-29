#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

namespace LCT {
    const int MAXN = 100005;
    int fa[MAXN], ch[MAXN][2];
    bool rev[MAXN];

    bool isroot(int x) {
        return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
    }

    void reverse(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }

    void push(int x) {
        if (rev[x]) {
            if (ch[x][0]) reverse(ch[x][0]);
            if (ch[x][1]) reverse(ch[x][1]);
            rev[x] = 0;
        }
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], k = ch[y][1] == x, w = ch[x][!k];
        if (isroot(y)) ch[z][ch[z][1] == y] = x;
        ch[x][!k] = y; ch[y][k] = w;
        if (w) fa[w] = y;
        fa[y] = x; fa[x] = z;
    }

    void pushall(int x) {
        if (isroot(x)) pushall(fa[x]);
        push(x);
    }

    void splay(int x) {
        int y = x, z = 0;
        pushall(y);
        while (isroot(x)) {
            y = fa[x]; z = fa[y];
            if (isroot(y)) 
                rotate((ch[y][0] == x) ^ (ch[z][0] == y) ? x : y);
            rotate(x);
        }
    }

    void access(int x) {
        int z = x;
        for (int y = 0; x; x = fa[y = x]) {
            splay(x);
            ch[x][1] = y;
        }
        splay(z);
    }

    void chroot(int x) {
        access(x);
        reverse(x);
    }

    void split(int x, int y) {
        chroot(x);
        access(y);
    }

    int Root(int x) {
        access(x);
        while (ch[x][0]) {
            push(x);
            x = ch[x][0];
        }
        splay(x);
        return x;
    }

    void Link(int u, int v) {
        chroot(u); 
        fa[u] = v;
    }
    
    void Cut(int u, int v) {
        split(u, v);
        fa[u] = ch[v][0] = 0;
    }

    int LCA(int x, int y) {
        chroot(1);
        access(x);
        splay(y);
        int rt = fa[y];
        while (rt) {
            y = rt;
            splay(y);
            rt = fa[y];
        }
        return y;
    }
}

int n;
int pa[100006];

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &pa[i]);
        LCT::Link(i, pa[i]);
    }
    int q; scanf("%d", &q);
    while (q--) {
        char op[5]; scanf("%s", op);
        int u, v; scanf("%d%d", &u, &v);
        if (op[0] == 'Q') {
            printf("%d\n", LCT::LCA(u, v));
        } else {
            LCT::Cut(u, pa[u]);
            LCT::Link(u, v);
            pa[u] = v;

        }
    }   
    return 0;
}
