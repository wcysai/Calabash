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
vector<int> a, b, c;
bool h[100005];
pair<LL, int> x[100005], y[100005];

int fa[100005];

int find(int x) {
  if (fa[x] == x) return x;
  return fa[x] = find(fa[x]);
}

void unite(int u, int v) {
  u = find(u); v = find(v);
  fa[u] = v;
}

bool check(LL d) {
  rep (i, n) fa[i] = i;
  rep (i, n) {
    if (x[i].first - x[0].first >= d) unite(x[0].second, x[i].second);
    if (x[n-1].first - x[i].first >= d) unite(x[n-1].second, x[i].second);

    if (y[i].first - y[0].first >= d) unite(y[0].second, y[i].second);
    if (y[n-1].first - y[i].first >= d) unite(y[n-1].second, y[i].second);
  }
  int p = find(0);
  rep (i, n) if (find(i) != p) return true;
  return false;
}

int main() {
  scanf("%d", &n);
  rep (i, n) {
    int xx, yy;
    scanf("%d%d", &xx, &yy);
    x[i] = {xx + yy, i};
    y[i] = {xx - yy, i};
  }
  sort(x, x+n);
  sort(y, y+n);
//  rep (i, n) _debug("%d %d", x[i].first, x[i].second);
//  rep (i, n) _debug("%d %d", y[i].first, y[i].second);
  LL l = 0, r = 5000000005;
  while (l < r) {
    LL mid = l + (r - l) / 2;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }
  assert(l == r);
  cout << l - 1 << endl;
  return 0;
}
