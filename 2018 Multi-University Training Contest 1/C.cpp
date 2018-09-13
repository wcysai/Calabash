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

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int x, y;
    scanf("%d", &n);
    vector<pair<int, int>> p(n * 3);
    rep (i, 3 * n) {
      scanf("%d%d", &x, &y);
      p[i].first = x; p[i].second = i + 1;
    }
    sort(range(p));
    rep (i, 3 * n) {
      printf("%d%c", p[i].second, i%3==2?'\n':' ');
    }
  }
  return 0;
}
