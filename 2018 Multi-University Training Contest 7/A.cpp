#include <bits/stdc++.h>
const int SZ = 400005;
using namespace std;
int head[SZ],to[SZ],nxt[SZ],belong[SZ],dist[SZ],parent[SZ],edge_count;
int N,M;
bool used[SZ];
struct Node{
    int n,d;
    Node(int _n=0,int _d=0):n(_n),d(_d) {}
    bool operator<(const Node& h) const {return d>h.d;}
};
priority_queue<Node> q;
void clear() {
    memset(head,-1,sizeof(head));
    edge_count = 0;
}
void add(int u,int v,int w) {
    to[edge_count] = v;
    nxt[edge_count] = head[u];
    belong[edge_count] = w;
    head[u] = edge_count++;
}
void dij() {
    memset(dist,0x3f,sizeof(dist));
    dist[1] = 0;
    while (!q.empty()) q.pop();
    q.emplace(1,0);
    memset(parent,-1,sizeof(parent));
    parent[1] = 0;
    memset(used,0,sizeof(used));
    while (!q.empty()) {
        Node top = q.top();
        q.pop();
        int u = top.n;
        if (used[u]) continue;
        if (u == N) return;
        used[u] = true;
        for (int ed=head[u];~ed;ed=nxt[ed]) {
            int v = to[ed];
            if (used[v]) continue;
            int new_dist = (parent[u]==belong[ed] ? dist[u] : dist[u]+1);
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                parent[v] = belong[ed];
                q.emplace(v,dist[v]);
            }
        }
    }
}
namespace Quick_in {
    const int LEN = (1 << 21) + 1;
    char ibuf[LEN], *iH, *iT;
    int f, c;
#define gc() (iH==iT?(iT=(iH=ibuf)+fread(ibuf,1,LEN,stdin),(iH==iT?EOF:*iH++)):*iH++)
    template<class T>
    inline void sc(T &x) {
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
        for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
        x *= f;
    }
    template<class T>
    inline bool read(T &x) {
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) {
            if (c == -1)return 0;
            if (c == '-') f = -1;
        }
        for (x = c - 48;; x = x * 10 + (c & 15)) { if (!isdigit(c = gc()))break; }
        x *= f;
        return 1;
    }
    template<typename A, typename B>
    inline void sc(A &x, B &y) { sc(x), sc(y); };
    template<typename A, typename B>
    inline bool read(A &x, B &y) { return read(x) && read(y); };
}
using namespace Quick_in;
void solve(){
    clear();
    while (M--) {
        int a,b,w;
        sc(a,b);
        sc(w);
        add(a,b,w);
        add(b,a,w);
    }
    dij();
    if (dist[N] >= 2e5+5) printf("-1\n");
    else printf("%d\n",dist[N]);
}
int main() {
    while (read(N,M)) {
        solve();
    }
    return 0;
}
