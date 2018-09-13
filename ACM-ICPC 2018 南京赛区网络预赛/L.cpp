#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

const LL INF = LLONG_MAX / 2;
const int MAXV = 1200005;

namespace fio {
  char buf[32000000], *ptr = buf;

  void init() {
    fread(buf, 1, sizeof buf, stdin);
  } 

  int read() {
    int ret = 0;
    while (!isdigit(*ptr)) ptr++;
    while (isdigit(*ptr)) {
      ret = ret * 10 + *ptr - '0';
      ptr++;
    }
    return ret;
  }
}

struct edge{
  int u, v;
  LL w;
};

int n, m, k;

namespace graph {
  int V;
  vector<edge> adj[MAXV];
  LL d[MAXV];
 
  void init(int v) {
    V = v;
    rep (i, V + 1) {
      adj[i].clear();
    }
  }

  void add_edge(int u, int v, int w){
    edge e;
    e.u = u; e.v = v; e.w = w;
    adj[u].push_back(e);
  }
  
  bool done[MAXV];

    void dijkstra(int src){
        typedef pair<int, LL> pii;
        priority_queue<pii, vector<pii>, greater<pii> > q;

        fill(d, d + V + 1, INF);
        d[src] = 0;
        fill(done, done + V + 1, false);
        q.push(make_pair(0, src));
        while (!q.empty()){
            int u = q.top().second; q.pop();
            if (done[u]) continue;
            done[u] = true;
            if (u / (k+1) == n-1) throw LL(d[u]);
            rep (i, adj[u].size()){
                edge e = adj[u][i];
                if (d[e.v] > d[u] + e.w){
                    d[e.v] = d[u] + e.w;
                    q.push(make_pair(d[e.v], e.v));
                }
            }
        }
    }
};

inline int enc(int x, int id) {
  return (k + 1) * (x - 1) + id;
}

int main() {
  using namespace fio;
  init();
  int T = read(); // scanf("%d", &T);
  while (T--) {
    n = read(); m = read(); k = read();
    graph::init(n * (k + 1));
    rep (i, m) {
      int u = read(), v = read(), w = read(); 
      rep (i, k + 1) {
        graph::add_edge(enc(u, i), enc(v, i), w);
        if (i) graph::add_edge(enc(u, i-1), enc(v, i), 0);
      }
    } 
    try {
    graph::dijkstra(enc(1, 0));
    } catch (LL ans) {
      cout << ans << endl;
      continue;
    }
    LL ans = LLONG_MAX;
    rep (i, k+1) {
      int id = enc(n, i);
      ans = min(ans, graph::d[id]);
    }
    cout << ans << endl;
  }
  return 0;
}
