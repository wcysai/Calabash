#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;

int m, n;
int ans = 0;
int fa[100005];
int id[100005];

void init() {
  Rep (i, m) fa[i] = i;
}

int find(int x) {
  if (fa[x] == x) return x;
  return fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
  u = find(u); v = find(v);
  fa[u] = v;
  return u != v;
}

int main() {
  cin >> m >> n;
  init();
  for (int i=1; i<=m; i++) {
    int num; cin >> num;
    while (num--) {
      int pos; cin >> pos;
      if (id[pos]) ans += unite(i, id[pos]);
      else id[pos] = i;
    }
  }
  cout << ans << endl;
  return 0;
}
