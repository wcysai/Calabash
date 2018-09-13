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

int a[3], b[3];

auto canon(int a[3]) -> pair<pair<int, int>, pair<int, int>> {
  rep (i, 3) if (a[i] >= INT_MAX / 2) a[i] = INT_MAX;
  return minmax(make_pair(a[1], a[2]), make_pair(a[0], INT_MAX));
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int la, lb; scanf("%d%d", &la, &lb);
    rep (i, 3) a[i] = b[i] = INT_MAX / 2;
    rep (i, la) scanf("%d", a+i);
    rep (i, lb) scanf("%d", b+i);
    a[0] += 2; a[1]++;
    b[0] += 2; b[1]++;
    if (a[1] > a[2]) swap(a[1], a[2]);
    if (b[1] > b[2]) swap(b[1], b[2]);
    auto canon1 = canon(a), canon2 = canon(b);
//    _debug("1:[%d, %d] 2:[%d, %d]", canon1.first, canon1.second, canon2.first,
//        canon2.second);
    if (canon1 < canon2) {
      puts("1");
    } else if (canon1 > canon2) {
      puts("-1");
    } else puts("0");
  }
  return 0;
}
