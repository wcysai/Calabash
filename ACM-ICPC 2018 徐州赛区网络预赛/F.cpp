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
map<ULL, pair<int, int>> occ;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    occ.clear();
    scanf("%d", &n);
    int ans = 0;
    rep (i, n) {
      int m; scanf("%d", &m);
      rep (j, m) {
        int x, y; scanf("%d%d", &x, &y);
        LL fea = ULL(x) << 32 | ULL(y);
        auto it = occ.find(fea);
        if (it == occ.end()) {
          occ[fea] = {i, 1};
          ans = max(ans, 1);
        } else {
          if (it->second.first == i) continue;
          if (it->second.first == i-1) {
            it->second.first = i;
            it->second.second++;
            ans = max(ans, it->second.second);
          } else {
            it->second = {i, 1};
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
