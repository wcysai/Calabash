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

int n, k;
int sz[10005], top[10005];

void emit(int x) {
  printf("%d\n", x);
  fflush(stdout);
  char op[5];
  scanf("%s", op);
  if (strcmp(op, "End") == 0) exit(0);
  if (op[0] == '>') {
    rep (i, n) if (sz[i] and top[i] >= x) sz[i]--;
  } else {
    rep (i, n) if (sz[i] and top[i] <= x) sz[i]--;
  }
  rep (i, n) scanf("%d", top + i);
}

int main() {
  scanf("%d%d", &n, &k);
  rep (i, n) {
    scanf("%d", top + i);
    sz[i] = k;
  }
  while (true) {
    vector<pair<int, int>> v;
    LL tot = 0, cur = 0;
    rep (i, n) if (sz[i]) {
      tot += 1 << sz[i];
      v.emplace_back(top[i], 1 << sz[i]);
    }
    sort(range(v));
    for (auto p : v) {
      cur += p.second;
      if (cur > tot / 2) {
        emit(p.first);
        break;
      }
    }
  }
  return 0;
}
