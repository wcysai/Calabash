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

int L;
LL a[16];
LL m[256][256];

LL query(int x, int y) {
  int xn = x / L, yn = y / L;
  x %= L; y %= L;
  return m[x][y] + xn * m[L][y] 
    + yn * m[x][L] + 1ll * xn * yn * m[L][L];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &L);
    memset(a, 0, sizeof a);
    rep (i, L) {
      int x; scanf("%d", &x);
      a[i] = x;
    }
    int cursor = 0;
    memset(m, 0, sizeof m);
    rep (i, L*L*2+1) {
      for (int j = 0; j <= i; j++) {
        m[j+1][i-j+1] = a[cursor];
        cursor = (cursor + 1) % L;
      }
    }
    L *= L;
    /*   
    Rep (i, L*3) {
      Rep (j, L*3) printf("%lld\t", m[i][j]);
      puts("");
    }
    */
    Rep (i, L) Rep (j, L) m[i][j] += m[i][j-1];
    Rep (i, L) Rep (j, L) m[i][j] += m[i-1][j];
    /*
    Rep (i, L) {
      Rep (j, L) printf("%lld\t", m[i][j]);
      puts("");
    }
    */
    int q; scanf("%d", &q);
    while (q--) {
      int x0, y0, x1, y1;
      scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
      x1++; y1++;
      LL ans = query(x1, y1) - query(x1, y0) - query(x0, y1) + query(x0, y0);
      printf("%lld\n", ans);
    }
  }  
  
  return 0;
}
