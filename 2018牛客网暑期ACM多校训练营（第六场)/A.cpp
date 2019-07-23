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
 
typedef pair<int, vector<int>> piv;
piv s[1 << 15];
 
void compete(piv& l, piv& r) {
  if (l.second.back() < r.second.back()) swap(l, r);
  l.second.erase(lower_bound(range(l.second), r.second.back()));
}
 
int main() {
  int T; scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d", &n);
    rep (i, 1 << n) s[i].second.assign(n, 0);
    rep (i, 1 << n) {
      s[i].first = i;
      rep (j, n)
        scanf("%d", &(s[i].second[j]));
    }
    rep (i, 1 << n) sort(range(s[i].second));
    for (int ss = 1; ss < (1 << n); ss <<= 1) {
      for (int i = 0; i < (1 << n); i += ss << 1 ) {
//        _debug("i=%d, ss=%d", i, ss);
//      _debug("%d v. %d", i, i+ss);
        compete(s[i], s[i+ss]);
      }
    }
    printf("Case #%d: %d\n", t, s[0].first+1);
  }
  return 0;
}
