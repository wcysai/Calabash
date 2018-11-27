#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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

typedef tree<pair<int, int>, null_type, less<>, rb_tree_tag, 
        tree_order_statistics_node_update> rkt;

int n;
vector<int> adj[51200];
int sz[51200], sum;

void getsz(int u, int p) {
  sz[u] = 1; sum ++;
  for (int v : adj[u]) {
    if (v == p) continue;
    getsz(v, u);
    sz[u] += sz[v];
  }
}

int getcent(int u, int p) {
  for (int v : adj[u]) {
    if (v == p) continue;
    if (sz[v] > sum / 2) return getcent(v, u);
  }
  return u;
}

rkt cnt1[102400], cnt2[102400];

int nextid = 0;

struct tag {
  int maxv, minv, len;

  tag() = default;
  tag(int x) : maxv(x), minv(x), len(0) {}

  friend tag operator | (tag lhs, tag rhs) {
    tag ret;
    ret.maxv = max(lhs.maxv, rhs.maxv);
    ret.minv = min(lhs.minv, rhs.minv);
    ret.len = lhs.len + rhs.len + 1;
    return ret;
  }
  
  int count() {
    int i1 = maxv - len - minv, i2 = maxv - len;
    int ans = 0;
    if (i1 >= 0) ans += cnt1[i1].order_of_key({-minv, INT_MIN}); 
    if (i2 >= 0) ans += cnt2[i2].order_of_key({minv, INT_MAX});
    return ans;
  }

  void enter() {
    cnt1[len].insert({-minv, ++nextid});
    cnt2[len + minv].insert({minv, ++nextid});
  }

  void leave() {
    cnt1[len].clear();
    cnt2[len + minv].clear();
  }

  bool operator < (const tag& rhs) const { return maxv < rhs.maxv; }
};


LL compute(vector<tag>& tags) {
  sort(range(tags));
  _debug("COMPUTE");
  for (auto t : tags) 
    _debug("minv=%d, maxv=%d, len=%d", t.minv, t.maxv, t.len);
  LL ans = 0;
  for (tag t : tags) {
    ans += t.count();
    t.enter();
  }
  for (tag t : tags) t.leave();
  return ans;
}

LL ans;

vector<tag> curtag, tottag;

void work(int u, int p, tag t) {
  t = t | tag(u);
  curtag.push_back(t);
  tottag.push_back(t);
  for (int v : adj[u]) 
    if (v != p) work(v, u, t);
}

void decompose(int u) {
  sum = 0; getsz(u, 0);
  u = getcent(u, 0);
  
  tottag.clear();
  for (int v : adj[u]) {
    curtag.clear();
    work(v, u, tag(u));
    ans -= compute(curtag);
  }
  tottag.push_back(tag(u));
  ans += compute(tottag);

  for (int v : adj[u]) {
    adj[v].erase(find(range(adj[v]), u));
    decompose(v);
    adj[v].push_back(u);
  }
}

int main() {
  scanf("%d", &n);
  rep (_, n - 1) {
    int u, v; scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  decompose(1);
  cout << ans + n << endl;
  return 0;
}
