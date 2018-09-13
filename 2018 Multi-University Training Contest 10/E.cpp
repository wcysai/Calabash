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

int n;
int a[100005], ans[100005];
int cnt[100005];
vector<int> adj[100005];

vector<int> concat(const vector<vector<int>>& vs) {
  vector<int> res;
  for (auto& v : vs) res.insert(res.end(), range(v));
  sort(range(res));
  res.resize(unique(range(res)) - res.begin());
  return res;
}

vector<int> dfs(int u, int p) {
  vector<vector<int>> ch;
  ans[u] = -1;
  ch.emplace_back();
  for (int i = 1; i * i <= a[u]; i++) {
    if (a[u] % i) continue;
    ch.front().push_back(i); 
    if (i * i != a[u]) ch.front().push_back(a[u] / i);
  }
  for (int v : adj[u]) {
    if (v == p) continue;
    ch.push_back(dfs(v, u));
  }
  for (const auto& x : ch) { for (int v : x) cnt[v]++; }
  vector<int> res = concat(ch);
  for (int x : res) {
    if (cnt[x] > 1) ans[u] = x;
    cnt[x] = 0;
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int p; scanf("%d", &p);
    adj[p].push_back(i);
    adj[i].push_back(p);
  }
  Rep (i, n) scanf("%d", a+i);
  dfs(1, 0);
  Rep (i, n) printf("%d\n", ans[i]);
  return 0;
}
