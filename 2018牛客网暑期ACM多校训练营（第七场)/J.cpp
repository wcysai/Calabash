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
 
int n, m;
unsigned char g[1024][1024];
int rbeg[1024][1024], cbeg[1024][1024];
int occur[256];
 
LL tot = 0;
 
int main() {
  scanf("%d%d", &n, &m);
  rep (i, n) scanf("%s", g[i]);
  rep (i, n) {
    int last = 0;
    memset(occur, -1, sizeof occur);
    rep (j, m) {
      rbeg[i][j] = last = max(last, occur[g[i][j]] + 1);
      occur[g[i][j]] = j;
    }
  }
  /*
  rep (i, n) {
    rep (j, m) printf("%d\t", rbeg[i][j]); puts("");
  }
  */
  rep (j, m) {
    int last = 0;
    memset(occur, -1, sizeof occur);
    rep (i, n) {
      cbeg[i][j] = last = max(last, occur[g[i][j]] + 1);
      occur[g[i][j]] = i;
    }
  }
/*
  rep (i, n) {
    rep (j, m) printf("%d\t", cbeg[i][j]); puts("");
  }
*/
  rep (c, m) {
    rep (rr, n) {
      int lptr = rbeg[rr][c];
      static int maxcbeg[1024];
      maxcbeg[c] = cbeg[rr][c];
      for (int cc = c - 1; cc >= lptr; cc--)
        maxcbeg[cc] = max(maxcbeg[cc+1], cbeg[rr][cc]);
//      for (int i = 0; i <= c; i++) printf("%d\t", maxcbeg[i]); puts("");
      for (int rl = rr; rl >= 0 && rl > rr - 52; rl--) {
        lptr = max(lptr, rbeg[rl][c]);
        while (maxcbeg[lptr] > rl && lptr <= c) lptr++;
//        _debug("c=%d, rl=%d, rr=%d, lptr=%d, delta=%d", c, rl, rr, lptr,
//            c+1-lptr);
        if (lptr <= c) tot += c + 1 - lptr;
      }
    }
  }
  cout << tot << endl;
  return 0;
}
