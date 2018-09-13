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
#define For(i, b, e) for (int i = b; i < e; i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned un;

un xlat(char ch) {
  if (isdigit(ch)) return 1 << (ch - '0');
  return 1 << (10 + ch - 'A');
}

int ans;
un mat[16][16];
un rmask[16], cmask[16];

inline void lrot(int r, int c) {
  r <<= 2; c <<= 2; 
  un res[4][4];
  rep (i, 4) rep (j, 4) res[i][j] = mat[r+3-j][c+i];
  rep (i, 4) rep (j, 4) mat[r+i][c+j] = res[i][j];
}

inline bool verify(int r, int c) {
//  _debug("%d %d", r, c);
  r <<= 2; c <<= 2;
  For (i, r, r+4) {
    For (j, c, c+4) {
      if (rmask[i] & mat[i][j]) return false;
      if (cmask[j] & mat[i][j]) return false;
    }
  }
  return true;
}

inline void commit(int r, int c) {
  r <<= 2; c <<= 2;
  For (i, r, r+4) {
    For (j, c, c+4) {
      rmask[i] |= mat[i][j];
      cmask[j] |= mat[i][j];
    }
  }
}

void rec(int r, int c, int used) {
  if (used >= ans) return;
  if (r == 4) {
    ans = min(ans, used);
    return ;
  } 
  if (c == 4) {
    rec(r+1, 0, used);
    return ;
  }
  un trmask[16], tcmask[16];
  if (verify(r, c)) {
    _debug("no-op [%d, %d]", r, c);
    memcpy(trmask, rmask, sizeof rmask);
    memcpy(tcmask, cmask, sizeof cmask);
    commit(r, c);
    rec(r, c+1, used);
    memcpy(rmask, trmask, sizeof rmask);
    memcpy(cmask, tcmask, sizeof cmask);
  }
  lrot(r, c); 
  if (verify(r, c)) {
    _debug("lrot [%d, %d]", r, c);
    memcpy(trmask, rmask, sizeof rmask);
    memcpy(tcmask, cmask, sizeof cmask);
    commit(r, c);
    rec(r, c+1, used+1);
    memcpy(rmask, trmask, sizeof rmask);
    memcpy(cmask, tcmask, sizeof cmask);
  } 
  lrot(r, c); 
  if (verify(r, c)) {
    _debug("crot [%d, %d]", r, c);
    memcpy(trmask, rmask, sizeof rmask);
    memcpy(tcmask, cmask, sizeof cmask);
    commit(r, c);
    rec(r, c+1, used+2);
    memcpy(rmask, trmask, sizeof rmask);
    memcpy(cmask, tcmask, sizeof cmask);
  } 
  lrot(r, c); 
  if (verify(r, c)) {
    _debug("rrot [%d, %d]", r, c);
    memcpy(trmask, rmask, sizeof rmask);
    memcpy(tcmask, cmask, sizeof cmask);
    commit(r, c);
    rec(r, c+1, used+3);
    memcpy(rmask, trmask, sizeof rmask);
    memcpy(cmask, tcmask, sizeof cmask);
  } 
  lrot(r, c); 
  return;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    rep (i, 16) {
      char str[32]; scanf("%s", str);
      rep (j, 16) mat[i][j] = xlat(str[j]);
    }
    /*
    lrot(1, 2);
    rep (i, 4) {
      rep (j, 4) printf("%x", __builtin_ctz(mat[4+i][8+j]));
      cout << endl;
    }
    
    return 0;
    */
    ans = INT_MAX;
    memset(rmask, 0, sizeof rmask);
    memset(cmask, 0, sizeof cmask);
    rec(0, 0, 0);
    printf("%d\n", ans);
  }
  return 0;
}
