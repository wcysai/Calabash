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

int n;
vector<int> adj[1000006];
int sz[1000005];

bool judge(int k) {
  int cnt = 0;
  if (n%k) return false;
  Rep (i, n) if (sz[i] % (n/k) == 0) cnt++;
  return cnt == k;
}

int dfs(int u, int p) {
  int siz = 1;
  for (int v : adj[u]) {
    if (v == p) continue;
    siz += dfs(v, u);
  }
  sz[u] = siz;
  return siz;
}

int main() {
  // cin >> n;
  scanf("%d", &n);
  for (int i=1; i<n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  for (int i=2; i<=n; i++) {
    if (judge(i)) cout << i-1 << ' ';
  }
  return 0;
}
